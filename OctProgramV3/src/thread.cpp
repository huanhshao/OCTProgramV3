#include "stdafx.h"
#include "thread.h"
#include "MulThrdHds.h"

const int kGaussHalf=3;
const int kGaussLength = 2*kGaussHalf+1;
const double kGaussSigma=1;
unsigned __stdcall ACQDATA(void* lpParam){
	AcqParam* acq_param=reinterpret_cast<AcqParam*>(lpParam);
    OCTProgram::AlazarInfo* alazar = acq_param->alazar;
    OpenCLGLClass* cgl = acq_param->clgl;
	OCTProgram::AdvInfo* adv=acq_param->adv;
	vector<int> calib_param;
	vector<double> gauss_factor;
	DWORD time_out = 1000;       //maximum waiting time 1 second
    while (WaitForSingleObject(acq_param->end_thread, 0) != WAIT_OBJECT_0){
		if (WaitForSingleObject(acq_param->begin_acquisition, time_out)!=WAIT_OBJECT_0)
			continue;        
        WaitForSingleObject(_HMutex, INFINITE);
        SetEvent(acq_param->acquisition_running);
        ReleaseMutex(_HMutex);
		bool success = true;
        //////////////////Prepare Begin//////////////////////////////
        //calibration param
		vector<double> calib_data;
		success=alazar->ReadCalibrationData(calib_data);
        if (success){
            GetCalibParams(calib_data,
				alazar->calib_start_index,alazar->calib_end_index,
				calib_param);
			cgl->WriteCalibIndex(calib_param);
        }
        //DC_drift param
        vector<float> dc_drift_data;
        success=alazar->ReadDriftData(calib_param,dc_drift_data);
        if (success){
            cgl->WriteDriftData(dc_drift_data);
        }
        //check state
        if (WaitForSingleObject(acq_param->begin_acquisition, 0) != WAIT_OBJECT_0){
			WaitForSingleObject(_HMutex, INFINITE);
			ResetEvent(acq_param->acquisition_running);
			ReleaseMutex(_HMutex);
            continue;
        }
        ///////////////////////Acqusition Begin///////////////////////////
		RETURN_CODE return_code;
        //success=alazar->BeforeAsyncAcqusition(CHANNEL_A,-1);
		success=alazar->BeforeAsyncAcqusition(CHANNEL_A|CHANNEL_B,-1);
		success|=adv->PrepareStartWave();
		if (success){
            return_code = AlazarStartCapture(alazar->boardHandle);
			success = adv->StartWaveOut();
			success |= alazar->ParseError(return_code);
        }
        // Wait for each buffer to be filled, process the buffer, and re-post it to the board.
        DWORD timeout_ms = 5000;
        U32 bufferIndex = 0;
		U8* pBuffer=nullptr;
        FILE* fpData = fopen("../../../data.bin", "wb");
        while (WaitForSingleObject(acq_param->begin_acquisition, 0) == WAIT_OBJECT_0 && success){
            bufferIndex = bufferIndex % alazar->BUFFER_COUNT;
            pBuffer = alazar->bufferArray[bufferIndex];
            return_code = AlazarWaitAsyncBufferComplete(alazar->boardHandle, pBuffer, timeout_ms);
            success = alazar->ParseError(return_code);
            if (success){
				if (WaitForSingleObject(acq_param->save_buffer,0)==WAIT_OBJECT_0){
					cout<<"Write buffers!!"<<endl;
					U8* pRecord = pBuffer;
					for (int channel = 0; (channel < alazar->channelCount) && (success == true); channel++){
					    for (U32 record = 0; (record < alazar->recordsPerBuffer) && (success == true); record++){
					        size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), alazar->bytesPerRecord, fpData);
					        if (bytesWritten != alazar->bytesPerRecord) success = false;
					        pRecord += alazar->samplesPerRecord;
					    }
					}
				}
				if (WaitForSingleObject(_HEmptyGPUMem, 0) == WAIT_OBJECT_0){
                    cgl->SendDataToGPU(pBuffer);
                    WaitForSingleObject(_HMutex, INFINITE);
                    cgl->EmptyToFull();
                    ReleaseSemaphore(_HFullGPUMem, 1, NULL);
                    ReleaseMutex(_HMutex);
                }
                bufferIndex++;
            }
            if (success){
                return_code = AlazarPostAsyncBuffer(alazar->boardHandle, pBuffer, alazar->bytesPerBuffer);
                success = alazar->ParseError(return_code);
            }
        }
        // Abort the acquisition
		success = adv->StopWaveOut();
        return_code = AlazarAbortAsyncRead(alazar->boardHandle);
        success &= alazar->ParseError(return_code);
        if (fpData != NULL){
            fclose(fpData);
        }
		if (!success){
			WaitForSingleObject(_HMutex, INFINITE);
			ResetEvent(acq_param->begin_acquisition);
			ReleaseMutex(_HMutex);
		}
		WaitForSingleObject(_HMutex, INFINITE);
		ResetEvent(acq_param->acquisition_running);
		ReleaseMutex(_HMutex);
    }
    ResetEvent(acq_param->acquisition_running);
    _endthreadex(0);
    return 0;
}
unsigned __stdcall PROCESSDATA(void* lpParam){
	ProcessParam* process_param=reinterpret_cast<ProcessParam*>(lpParam);
    OpenCLGLClass* cgl = process_param->clgl;
    DWORD time_out = 1000;       //maximum waiting time 1 second
    cgl->SetGLContext(1);       //set rc to shared
    while (WaitForSingleObject(process_param->end_thread, 0) != WAIT_OBJECT_0){
        if (WaitForSingleObject(_HFullGPUMem, time_out) == WAIT_OBJECT_0){
            cgl->CalFFT();
            WaitForSingleObject(_HMutex, INFINITE);
            cgl->FullToEmpty();
            cgl->SwapTexBuffer();
            ReleaseSemaphore(_HEmptyGPUMem, 1, NULL);
            ReleaseMutex(_HMutex);
        }
    }
    cgl->SetGLContext(0);       //set rc to null
    _endthreadex(0);
    return 0;
}
void GetGaussianKernel(int n, double sigma, std::vector<double> &res){
	assert(n > 0);
	if (sigma <= 0) {
		sigma = static_cast<double>(n)/6;  // 3*sigma = n/2
	}
	std::vector<double> coefficients(n);
	double s = 0;
	double mid = static_cast<double>(n - 1) / 2.;
	for (int i = 0; i < n; i++) {
		double coefficient = exp(-sqr(i-mid)/(2*sqr(sigma)));
		s += coefficient;
		coefficients[i] = coefficient;
	}
	double inv_s = 1./s;
	for (int i = 0; i < n; i++) {
		coefficients[i] *= inv_s;
	}
	res.swap(coefficients);
}
void GetCalibParams(vector<double>& calib_data,int stt,int edd,vector<int>& calib_param){
	double calib_mean=0;
	for (vector<double>::size_type i = 0; i!=calib_data.size(); i++){
		calib_mean+=calib_data[i];
	}
	calib_mean/=calib_data.size();
	std::vector<double> tmp(calib_data.size(),0);
	int start_id=stt+kGaussHalf;
	int end_id=edd-kGaussHalf;
	vector<double> gauss_factor;
	GetGaussianKernel(kGaussLength,kGaussSigma,gauss_factor);
	for (int i = start_id; i<end_id; i++){
		double d = 0;
		for (int j = -kGaussHalf; j<=kGaussHalf; j++){
			d += calib_data[i+j] * gauss_factor[j+kGaussHalf];
		}
		tmp[i] = d-calib_mean;
	}
	calib_data.swap(tmp);
	int k = 0;
	calib_param.clear();
	for (int i = start_id; i<end_id; i++){
		if (std::abs(calib_data[i]) > 2 && (calib_data[i] - calib_data[i - 1])*(calib_data[i] - calib_data[i + 1])>0){
			if (k<2 || calib_param[k - 1] - calib_param[k - 2]>100 || i - calib_param[k - 1]>(calib_param[k - 1] - calib_param[k - 2]) / 2){
				calib_param.push_back(i);
			}
		}
	}
	cout<<"Calib Param Raw Size: "<<calib_param.size()<<endl;
	int tmp_start_fuck_id=0;
	int start_fuck_id=0;
	int end_fuck_id=0;
	int fuck_length=0;
	std::vector<int> tmp_fuck;
	tmp_fuck.clear();
	if (calib_param.size()!=0){
		for (int i=0;i<calib_param.size()-1;i++){
			if (calib_param[i+1]-calib_param[i]>100){
				if (fuck_length<calib_param[i]-calib_param[tmp_start_fuck_id]){
					fuck_length=calib_param[i]-calib_param[tmp_start_fuck_id];
					start_fuck_id=tmp_start_fuck_id;
					end_fuck_id=i+1;
					tmp_start_fuck_id=end_fuck_id;
				}
			}
		}
		if (fuck_length<calib_param.back()-calib_param[tmp_start_fuck_id]){
			fuck_length=calib_param.back()-calib_param[tmp_start_fuck_id];
			start_fuck_id=tmp_start_fuck_id;
			end_fuck_id=calib_param.size();
			tmp_start_fuck_id=end_fuck_id;
		}
		tmp_fuck.insert(tmp_fuck.end(),calib_param.begin()+start_fuck_id,calib_param.begin()+end_fuck_id);
	}
	if (tmp_fuck.size()>0){
		cout<<"Calib End, Total Calib Point "<<tmp_fuck.size()<<" From "<<
			tmp_fuck.front()<<" To "<<tmp_fuck.back()<<endl;
	}
	if (tmp_fuck.size()>1024){
		tmp_fuck.resize(1024);
	}
	else{
		for (int i=tmp_fuck.size();i<1024;i++){
			tmp_fuck.push_back(-1);
		}
	}
	calib_param.swap(tmp_fuck);
	assert(calib_param.size()==1024);
	for (int i=0;i<calib_param.size();i++){
		if (calib_param[i]>0) calib_param[i]+=46;
	}
}
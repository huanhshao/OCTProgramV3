#include "stdafx.h"
#include "thread.h"
#include "MulThrdHds.h"

const int kGaussHalf=3;
const int kGaussLength = 2*kGaussHalf+1;
const double kGaussSigma=1;
//const double gauss_factor[41] = {
//	0.0003,    0.0007,    0.0015,    0.0031,
//	0.0060,    0.0111,    0.0198,    0.0340,
//	0.0561,    0.0889,    0.1353,    0.1979,
//	0.2780,    0.3753,    0.4868,    0.6065,
//	0.7261,    0.8353,    0.9231,    0.9802,
//	1.0000,    0.9802,    0.9231,    0.8353,
//	0.7261,    0.6065,    0.4868,    0.3753,
//	0.2780,    0.1979,    0.1353,    0.0889,
//	0.0561,    0.0340,    0.0198,    0.0111,
//	0.0060,    0.0031,    0.0015,    0.0007,
//	0.0003
//};
template<typename T>
inline T sqr(const T &x) {
	return x*x;
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
unsigned __stdcall ACQDATA(void* lpParam){
	AcqParam* acq_param=reinterpret_cast<AcqParam*>(lpParam);
    OCTProgram::AlazarInfo* alazar = acq_param->alazar;
    OpenCLGLClass* cgl = acq_param->clgl;
	OCTProgram::AdvInfo* adv=acq_param->adv;
	vector<int> calib_param;
	vector<double> gauss_factor;
	GetGaussianKernel(kGaussLength,kGaussSigma,gauss_factor);
    bool success = true;
	DWORD time_out = 1000;       //maximum waiting time 1 second
    while (WaitForSingleObject(acq_param->end_thread, 0) != WAIT_OBJECT_0){
		if (WaitForSingleObject(acq_param->begin_acquisition, time_out)!=WAIT_OBJECT_0)
			continue;        
        WaitForSingleObject(_HMutex, INFINITE);
        SetEvent(acq_param->acquisition_running);
        ReleaseMutex(_HMutex);
        success = true;
        //////////////////Calibration Begin//////////////////////////////
        alazar->SetChannalMask(2);				//CHANNAL_B = 2
        FILE* fpData = fopen("../../../Calibs.dat", "wb");
        char* strpro = "Cal Data Created By OCTProgram V2.1. Ascan Size:";
        fwrite(strpro, sizeof(BYTE), 49, fpData);
        strpro = new char[4];
        strpro[0] = alazar->bytesPerRecord / 256;
        strpro[1] = alazar->bytesPerRecord % 256;       //maximum: 65535
        strpro[2] = 0;
        strpro[3] = 10;
        fwrite(strpro, sizeof(BYTE), 4, fpData);
        delete[] strpro;                                //total head length 53
        //acquisition begin
        RETURN_CODE retCode;
        if (success){
            retCode = AlazarSetRecordSize(
                alazar->boardHandle,
                alazar->preTriggerSamples,
                alazar->postTriggerSamples
                );
            if (retCode != ApiSuccess) success = false;
        }
        if (success){
            retCode = AlazarBeforeAsyncRead(
                alazar->boardHandle,
                alazar->inputChannel,
                -(long)alazar->preTriggerSamples,
                alazar->samplesPerRecord,
                alazar->recordsPerBuffer,
                alazar->recordsPerBuffer,
                ADMA_EXTERNAL_STARTCAPTURE | ADMA_NPT
                );
            if (retCode != ApiSuccess) success = false;
        }
        U32 bufferIndex = 0;
        U8* pBuffer = alazar->bufferArray[bufferIndex];
        DWORD timeout_ms = 5000;
        //Only use one buffer
        retCode = AlazarPostAsyncBuffer(alazar->boardHandle, pBuffer, alazar->bytesPerBuffer);
        if (retCode != ApiSuccess) success = false;
        if (success){
            retCode = AlazarStartCapture(alazar->boardHandle);
            if (retCode != ApiSuccess) success = false;
        }
        if (success){
            retCode = AlazarWaitAsyncBufferComplete(alazar->boardHandle, pBuffer, timeout_ms);
            if (retCode != ApiSuccess) success = false;
            retCode = AlazarAbortAsyncRead(alazar->boardHandle);
            if (retCode != ApiSuccess) success = false;
        }
        if (success){
            vector<double> calib_data(alazar->bytesPerRecord);
            double average_length = alazar->calib_record_num;
			double calib_mean=0;
            for (vector<double>::size_type i = 0; i!=calib_data.size(); i++){
                calib_data[i] = 0;
                for (int j = 0; j<average_length; j++){
                    calib_data[i] += static_cast<double>(pBuffer[j*alazar->bytesPerRecord + i])/average_length;
                }
				calib_mean+=calib_data[i];
            }
			calib_mean/=calib_data.size();
            std::vector<double> tmp(calib_data.size(),0);
			int start_id=kGaussHalf+alazar->calib_start_index;
			int end_id=alazar->calib_end_index-kGaussHalf;
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
			if (calib_param.size()!=1024){
				cout<<"error calib size!!"<<endl;
				exit(0);
			}
            //save calib data for other use
            U8* pRecord = pBuffer;
            for (U32 record = 0; (record < alazar->recordsPerBuffer) && (success == TRUE); record++){
                size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), alazar->bytesPerRecord, fpData);
                if (bytesWritten != alazar->bytesPerRecord){
                    success = false;
                }
                pRecord += alazar->samplesPerRecord;
            }
			ofstream ofs("calib_params.txt",ios::out);
			for (int i=0;i<calib_param.size();i++){
				ofs<<calib_param[i]<<' ';
			}
			ofs.close();
        }
        fclose(fpData);
		assert(calib_param.size()==1024);
		cgl->WriteCalibIndex(calib_param);
        if (WaitForSingleObject(acq_param->begin_acquisition, 0) != WAIT_OBJECT_0){
			WaitForSingleObject(_HMutex, INFINITE);
			ResetEvent(acq_param->acquisition_running);
			ReleaseMutex(_HMutex);
            continue;
        }
        ///////////////////////Acq Begin///////////////////////////
        alazar->SetChannalMask(1);			//CHANNAL_A = 1
		//alazar->SetChannalMask(3);				//CHANNAL_A | B = 3
        fpData = fopen("../../../data.bin", "wb");
        strpro = "OCT Data Created By OCTProgram V2.1. Image Size:";
        fwrite(strpro, sizeof(BYTE), 49, fpData);
		int acq_time = 0;
		strpro = new char[4];
        strpro[0] = alazar->bytesPerRecord / 256;
        strpro[1] = alazar->bytesPerRecord % 256;
        strpro[2] = alazar->recordsPerBuffer / 256;
        strpro[3] = alazar->recordsPerBuffer % 256;     //maximum: 65535*65535
        fwrite(strpro, sizeof(BYTE), 4, fpData);
        delete[] strpro;                                //total head length 53
        int savedBuffer = 0;
        if (success){
            retCode = AlazarSetRecordSize(
                alazar->boardHandle,
                alazar->preTriggerSamples,
                alazar->postTriggerSamples
                );
            if (retCode != ApiSuccess) {
				alazar->ParseError(retCode);
				success = false;
			}
        }
        if (success){
			U32 admaFlags = ADMA_EXTERNAL_STARTCAPTURE | ADMA_NPT;
            retCode = AlazarBeforeAsyncRead(
                alazar->boardHandle,
                alazar->inputChannel,
                -(long)alazar->preTriggerSamples,
                alazar->samplesPerRecord,
                alazar->recordsPerBuffer,
                0x7fffffff,
                admaFlags
                );
			if (retCode != ApiSuccess) {
				alazar->ParseError(retCode);
				success = false;
			}
        }
        for (bufferIndex = 0; (bufferIndex < alazar->BUFFER_COUNT) && (success == true); bufferIndex++){
            pBuffer = alazar->bufferArray[bufferIndex];
            retCode = AlazarPostAsyncBuffer(alazar->boardHandle, pBuffer, alazar->bytesPerBuffer);
			if (retCode != ApiSuccess) {
				alazar->ParseError(retCode);
				success = false;
			}
        }
        if (success){
			bool scs= adv->StartWaveOut();
            retCode = AlazarStartCapture(alazar->boardHandle);
			if (retCode != ApiSuccess) {
				alazar->ParseError(retCode);
				success = false;
			}
        }
        // Wait for each buffer to be filled, process the buffer, and re-post it to the board.
        timeout_ms = 5000;	//Timeout Long Enough
        bufferIndex = 0;
        while (WaitForSingleObject(acq_param->begin_acquisition, 0) == WAIT_OBJECT_0&&success){
            bufferIndex = bufferIndex % alazar->BUFFER_COUNT;
            pBuffer = alazar->bufferArray[bufferIndex];
            retCode = AlazarWaitAsyncBufferComplete(alazar->boardHandle, pBuffer, timeout_ms);
			if (retCode != ApiSuccess) {
				alazar->ParseError(retCode);
				success = false;
			}
            if (success){
				//if (acq_time%100==0&&acq_time<1001){
				
				if (acq_time==0){
					U8* pRecord = pBuffer;
					for (int channel = 0; (channel < alazar->channelCount) && (success == true); channel++){
					    for (U32 record = 0; (record < alazar->recordsPerBuffer) && (success == true); record++){
					        size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), alazar->bytesPerRecord, fpData);
					        if (bytesWritten != alazar->bytesPerRecord) success = false;
					        pRecord += alazar->samplesPerRecord;
					        savedBuffer++;
					    }
					}
				}
				acq_time++;
				if (WaitForSingleObject(_HEmptyGPUMem, 0) == WAIT_OBJECT_0){
                    cgl->SendDataToGPU(pBuffer);
                    WaitForSingleObject(_HMutex, INFINITE);
                    cgl->EmptyToFull();
                    ReleaseSemaphore(_HFullGPUMem, 1, NULL);
                    ReleaseMutex(_HMutex);
                }
                bufferIndex++;
            }
            if (success)
            {
                retCode = AlazarPostAsyncBuffer(alazar->boardHandle, pBuffer, alazar->bytesPerBuffer);
				if (retCode != ApiSuccess) {
					alazar->ParseError(retCode);
					success = false;
				}
            }
        }
        // Abort the acquisition
		bool scs=adv->StopWaveOut();
        retCode = AlazarAbortAsyncRead(alazar->boardHandle);
        if (retCode != ApiSuccess||scs!=true) success = false;
        if (fpData != NULL){
            strpro = new char[4];
            strpro[0] = savedBuffer / 16777215;
            strpro[1] = savedBuffer / 65536 - strpro[0] * 256;
            strpro[2] = (savedBuffer % 65536) / 256;
            strpro[3] = savedBuffer % 256;
            fwrite(strpro, sizeof(BYTE), 4, fpData);
            delete[] strpro;
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
    //WaitForSingleObject(_HMutex, INFINITE);
    ResetEvent(acq_param->acquisition_running);
    //ReleaseMutex(_HMutex);
    _endthreadex(0);
    return 0;
}

unsigned __stdcall PROCESSDATA(void* lpParam)
{
	ProcessParam* process_param=reinterpret_cast<ProcessParam*>(lpParam);
    OpenCLGLClass* cgl = process_param->clgl;
    DWORD time_out = 1000;       //maximum waiting time 1 second
    cgl->SetGLContext(1);       //set rc to shared
    while (WaitForSingleObject(process_param->end_thread, 0) != WAIT_OBJECT_0){
        if (WaitForSingleObject(_HFullGPUMem, time_out) == WAIT_OBJECT_0)
        {
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
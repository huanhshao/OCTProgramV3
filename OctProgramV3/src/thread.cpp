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
unsigned __stdcall ACQDATA(void* lpParam)
{
	AcqParam* acq_param=reinterpret_cast<AcqParam*>(lpParam);
    OCTProgram::AlazarInfo* alazar = acq_param->alazar;
    OpenCLGLClass* cgl = acq_param->clgl;
	OCTProgram::AdvInfo* adv=acq_param->adv;
	std::vector<int> calib_param;
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
            //double average_length = 10;
            double average_length = alazar->recordsPerBuffer;
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
			int start_id=kGaussHalf;
			int end_id=calib_data.size()-kGaussHalf;
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
        if (WaitForSingleObject(acq_param->begin_acquisition, 0) != WAIT_OBJECT_0){
			WaitForSingleObject(_HMutex, INFINITE);
			ResetEvent(acq_param->acquisition_running);
			ReleaseMutex(_HMutex);
            continue;
        }
        ///////////////////////Acq Begin///////////////////////////
        alazar->SetChannalMask(1);			//CHANNAL_A = 1
        fpData = fopen("../../../data.bin", "wb");
        strpro = "OCT Data Created By OCTProgram V2.1. Image Size:";
        fwrite(strpro, sizeof(BYTE), 49, fpData);
		bool first_acq = true;
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
            if (retCode != ApiSuccess) success = false;
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
            if (retCode != ApiSuccess) success = false;
        }
        for (bufferIndex = 0; (bufferIndex < alazar->BUFFER_COUNT) && (success == true); bufferIndex++){
            pBuffer = alazar->bufferArray[bufferIndex];
            retCode = AlazarPostAsyncBuffer(alazar->boardHandle, pBuffer, alazar->bytesPerBuffer);
            if (retCode != ApiSuccess) success = false;
        }
        if (success){
			DWORD dwErrCde = adv->StartWaveOut();
            retCode = AlazarStartCapture(alazar->boardHandle);
            if (retCode != ApiSuccess || dwErrCde!= SUCCESS) success = false;
        }
        // Wait for each buffer to be filled, process the buffer, and re-post it to the board.
        timeout_ms = 5000;	//Timeout Long Enough
        bufferIndex = 0;
        float* tbuffer = new float[1024 * alazar->recordsPerBuffer];
		clock_t timeee=clock();
        while (WaitForSingleObject(acq_param->begin_acquisition, 0) == WAIT_OBJECT_0&&success){
			cout<<bufferIndex<<endl;
			if (bufferIndex==2) break;
            bufferIndex = bufferIndex % alazar->BUFFER_COUNT;
            pBuffer = alazar->bufferArray[bufferIndex];
            retCode = AlazarWaitAsyncBufferComplete(alazar->boardHandle, pBuffer, timeout_ms);
            if (retCode != ApiSuccess) success = false;
            if (success){
				if (first_acq){
					U8* pRecord = pBuffer;
					for (int channel = 0; (channel < alazar->channelCount) && (success == true); channel++){
					    for (U32 record = 0; (record < alazar->recordsPerBuffer) && (success == true); record++){
					        size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), alazar->bytesPerRecord, fpData);
					        if (bytesWritten != alazar->bytesPerRecord) success = false;
					        pRecord += alazar->samplesPerRecord;
					        savedBuffer++;
					    }
					}
					first_acq=false;
				}
				for (int j = 0; j<1024; j++){
					int line_id=calib_param[j];
					if (line_id<0){
						for (int i = 0; i<alazar->recordsPerBuffer; i++)
							tbuffer[i*1024+j]=0;
						continue;
					}
					float avg=0;
					for (int i = 0; i<alazar->recordsPerBuffer; i++)
						avg+=pBuffer[i*alazar->bytesPerRecord + line_id];
					avg/=alazar->recordsPerBuffer;
					for (int i = 0; i<alazar->recordsPerBuffer; i++){
						tbuffer[i*1024+j]=pBuffer[i*alazar->bytesPerRecord+line_id]-127;
                        //tbuffer[i*1024+j]=pBuffer[i*alazar->bytesPerRecord+line_id]-avg;
					}
                }
                if (WaitForSingleObject(_HEmptyGPUMem, 0) == WAIT_OBJECT_0)
                {
                    cgl->SendDataToGPU(tbuffer, 1024 * alazar->recordsPerBuffer);
                    WaitForSingleObject(_HMutex, INFINITE);
                    cgl->EmptyToFull();
                    ReleaseSemaphore(_HFullGPUMem, 1, NULL);
                    ReleaseMutex(_HMutex);
                }
                //Saving Mode Not Allowed Now!!
                //WaitForSingleObject(_HMutex, INFINITE);
                //if (alazar->acqMode == 1)
                //{
                //    ReleaseMutex(_HMutex);
                //    U8* pRecord = pBuffer;
                //    for (int channel = 0; (channel < alazar->channelCount) && (success == true); channel++)
                //    {
                //        for (U32 record = 0; (record < alazar->recordsPerBuffer) && (success == true); record++)
                //        {
                //            size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), alazar->bytesPerRecord, fpData);
                //            if (bytesWritten != alazar->bytesPerRecord) success = false;
                //            pRecord += alazar->samplesPerRecord;
                //            savedBuffer++;
                //        }
                //    }
                //}
                //else
                //{
                //    ReleaseMutex(_HMutex);
                //}
                bufferIndex++;
            }
            if (success)
            {
                retCode = AlazarPostAsyncBuffer(alazar->boardHandle, pBuffer, alazar->bytesPerBuffer);
                if (retCode != ApiSuccess) success = false;
            }
        }
        // Abort the acquisition
        delete[] tbuffer;
        tbuffer = nullptr;
		DWORD dwErrCde=adv->StopWaveOut();
        retCode = AlazarAbortAsyncRead(alazar->boardHandle);
        if (retCode != ApiSuccess||dwErrCde!=SUCCESS) success = false;
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
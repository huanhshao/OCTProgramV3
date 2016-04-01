#include "stdafx.h"
#include "thread.h"
#include "MulThrdHds.h"

const int kGaussHalf=3;
const int kGaussLength = 2*kGaussHalf+1;
const double kGaussSigma=1;
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
	DWORD time_out = 1000;       //maximum waiting time: 1 second
    while (WaitForSingleObject(acq_param->end_thread, 0) != WAIT_OBJECT_0){
		if (WaitForSingleObject(acq_param->begin_acquisition, time_out)!=WAIT_OBJECT_0)
			continue;        
        WaitForSingleObject(_HMutex, INFINITE);
        SetEvent(acq_param->acquisition_running);
        ReleaseMutex(_HMutex);
        success = true;
		RETURN_CODE retCode=ApiSuccess;
		U8* pBuffer=nullptr;
		int bufferIndex=0;
        ///////////////////////Acq Begin///////////////////////////
        alazar->SetChannalMask(2);			//CHANNAL_A = 1
		//alazar->SetChannalMask(3);				//CHANNAL_A | B = 3
        FILE* fpData = fopen("../../../data.bin", "wb");
        char* strpro = "OCT Data Created By OCTProgram V2.1. Image Size:";
        fwrite(strpro, sizeof(BYTE), 49, fpData);
		int acq_time = 0;
		strpro = new char[4];
        strpro[0] = (alazar->bytesPerRecord / 256)%256;
        strpro[1] = alazar->bytesPerRecord % 256;
        strpro[2] = (alazar->recordsPerBuffer / 256)%256;
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
			bool scs= adv->StartWaveOut();
            retCode = AlazarStartCapture(alazar->boardHandle);
            if (retCode != ApiSuccess || scs!= true) success = false;
        }
        // Wait for each buffer to be filled, process the buffer, and re-post it to the board.
        DWORD timeout_ms = 5000;	//Timeout Long Enough
        bufferIndex = 0;
        float* tbuffer = new float[1024 * alazar->recordsPerBuffer];
		int buffersCompleted=0;
        while (WaitForSingleObject(acq_param->begin_acquisition, 0) == WAIT_OBJECT_0&&success){
            bufferIndex = bufferIndex % alazar->BUFFER_COUNT;
            pBuffer = alazar->bufferArray[bufferIndex];
            retCode = AlazarWaitAsyncBufferComplete(alazar->boardHandle, pBuffer, timeout_ms);
            if (retCode != ApiSuccess){
				success = false;
				cout<<"error:"<<AlazarErrorToText(retCode)<<endl;
			}
			printf("Completed %d buffers,bufferIndex %u\r", buffersCompleted++,bufferIndex);
            if (success){
				//if (acq_time==0){
				//	U8* pRecord = pBuffer;
				//	for (int channel = 0; (channel < alazar->channelCount) && (success == true); channel++){
				//	    for (U32 record = 0; (record < alazar->recordsPerBuffer) && (success == true); record++){
				//	        size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), alazar->bytesPerRecord, fpData);
				//	        if (bytesWritten != alazar->bytesPerRecord) success = false;
				//	        pRecord += alazar->samplesPerRecord;
				//	        savedBuffer++;
				//	    }
				//	}
				//}
				//for (int j = 0; j<1024; j++){
				//	for (unsigned int i = 0; i<alazar->recordsPerBuffer; i++){
				//		if (j>alazar->bytesPerRecord){
				//			tbuffer[i*1024+j]=0;
				//		}
				//		else{
				//			tbuffer[i*1024+j]=static_cast<float>(pBuffer[i*alazar->bytesPerRecord+j]-127);
				//	
				//		}
				//	}
				//}
                //if (WaitForSingleObject(_HEmptyGPUMem, 0) == WAIT_OBJECT_0){
                //    cgl->SendDataToGPU(tbuffer, 1024 * alazar->recordsPerBuffer);
                //    WaitForSingleObject(_HMutex, INFINITE);
                //    cgl->EmptyToFull();
                //    ReleaseSemaphore(_HFullGPUMem, 1, NULL);
                //    ReleaseMutex(_HMutex);
                //}
                bufferIndex++;
            }
            if (success)
            {
                retCode = AlazarPostAsyncBuffer(alazar->boardHandle, pBuffer, alazar->bytesPerBuffer);
                if (retCode != ApiSuccess){
					success = false;
					cout<<"error:"<<AlazarErrorToText(retCode)<<endl;
				}
            }
        }
        // Abort the acquisition
        delete[] tbuffer;
        tbuffer = nullptr;
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
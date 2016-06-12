#include "stdafx.h"
#include "AlazarInfo.h"

namespace OCTProgram{
	AlazarInfo::AlazarInfo(){
		boardHandle=NULL;
		bufferArray=NULL;
		triggerDelaySamples=0;
		triggerTimeoutClocks=0;
		acqStop=true;
		if (!ConfigureBoard("resources/config/default_initial.ini")){
		cout<<"init alazar failed!"<<endl;
		assert(false);
		}
	}
	AlazarInfo::~AlazarInfo(){
		DeleteBuffer();
	}
	void AlazarInfo::DeleteBuffer(){
		if (bufferArray){
			for (U32 bufferIndex = 0; bufferIndex < BUFFER_COUNT; bufferIndex++){
				if (bufferArray[bufferIndex] != NULL){
#ifdef _WIN32
					VirtualFree(bufferArray[bufferIndex], 0, MEM_RELEASE);
#else
					free(bufferArray[bufferIndex]);
#endif
					bufferArray[bufferIndex] = NULL;
				}
			}
			delete[] bufferArray;
			bufferArray=NULL;
		}
	}
	bool AlazarInfo::ConfigureBoard(char* cfgParaDir){
		DeleteBuffer();
		if (!GetCfgParam(cfgParaDir))
			return false;
		bool success=true;
		bufferArray = new U8*[BUFFER_COUNT];
		boardHandle = AlazarGetBoardBySystemID(systemId, boardId);
		RETURN_CODE return_code=CfgBoard4Para();
		if (return_code!=ApiSuccess)
			success=false;
		if (success){
			return_code=GetAcqParam();
			if (return_code!=ApiSuccess)
				success=false;
		}
		if (success){
			U32 bufferIndex=0;
			U32 max_buffer_byte=bytesPerRecord*recordsPerBuffer*2;
			for (bufferIndex = 0; (bufferIndex < BUFFER_COUNT) && (success == true); bufferIndex++){
#ifdef _WIN32
				bufferArray[bufferIndex] = static_cast<U8*>(
					VirtualAlloc(NULL, max_buffer_byte, MEM_COMMIT, PAGE_READWRITE)
					);
#else
				bufferArray[bufferIndex] = static_cast<U8*>(malloc(max_buffer_byte));
#endif
				if (bufferArray[bufferIndex] == NULL){
					success = false;
				}
			}
			if (!success)
				return false;
		}
		return success;
	}
	bool AlazarInfo::GetCfgParam(char* cfgParaDir){
		Json::Value root;
		Json::Reader reader;
		std::ifstream fin(cfgParaDir,std::ios::in);
		if (!fin.is_open())
			return false;
		//std::string jstr=string((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
		reader.parse(fin,root,true);
		fin.close();
		//Set function here
		Json::Value section=root["system"];
		BUFFER_COUNT=section["buffer_count"].asInt();
		samplesPerSec=section["samples_per_second"].asDouble();
		systemId=(U32)(section["system_id"].asInt());
		boardId=(U32)(section["board_id"].asInt());

		section=root["clock"];
		clockSourceId=(U32)(section["clock_source"].asInt());
		sampleRateId=(U32)(section["sample_rate"].asInt());
		clockEdgeId=(U32)(section["clock_edge"].asInt());
		clockDecimation=(U32)(section["clock_decimation"].asInt());

		section=root["channel"];
		inputChannel=(U32)(section["input_channel"].asInt());
		Json::Value channels=section["channel_A"];
		inputCouplingIdA=(U32)(channels["input_coupling"].asInt());
		inputRangeIdA=(U32)(channels["input_range"].asInt());
		inputImpedanceIdA=(U32)(channels["input_impedance"].asInt());
		channels=section["channel_B"];
		inputCouplingIdB=(U32)(channels["input_coupling"].asInt());
		inputRangeIdB=(U32)(channels["input_range"].asInt());
		inputImpedanceIdB=(U32)(channels["input_impedance"].asInt());

		section=root["trigger"];
		triggerOperation=(U32)(section["trigger_operation"].asInt());
		Json::Value engines=section["trigger_engine_J"];
		triggerSourceIdJ=(U32)(engines["trigger_source"].asInt());
		triggerSlopeIdJ=(U32)(engines["trigger_slope"].asInt());
		triggerLevelJ=(U32)(engines["trigger_level"].asInt());
		engines=section["trigger_engine_K"];
		triggerSourceIdK=(U32)(engines["trigger_source"].asInt());
		triggerSlopeIdK=(U32)(engines["trigger_slope"].asInt());
		triggerLevelK=(U32)(engines["trigger_level"].asInt());
		triggerExCouplingId=(U32)(section["trigger_ex_coupling"].asInt());
		triggerExRangeId=(U32)(section["trigger_ex_range"].asInt());
		triggerDelaySamples=section["trigger_delay"].asInt();
		triggerTimeoutSec=section["trigger_timeout"].asDouble();

		section=root["AUX"];
		AUXMode=(U32)(section["mode"].asInt());
		AUXParameter=(U32)(section["parameters"].asInt());

		section=root["acqusition_params"];
		preTriggerSamples=(U32)(section["pre_trigger_samples"].asInt());
		postTriggerSamples=(U32)(section["post_trigger_samples"].asInt());
		recordsPerBuffer=(U32)(section["record_per_buffer"].asInt());
		buffersPerImage=(U32)(section["buffers_per_image"].asInt());

		section=root["calib_params"];
		calib_start_index=section["start_index"].asInt();
		calib_end_index=section["end_index"].asInt();
		calib_record_num=section["record_num_in_use"].asInt();
	}
	void AlazarInfo::SetChannalMask(int channalID)
	{
		inputChannel=channalID;
		GetAcqParam();
	}
	RETURN_CODE AlazarInfo::CfgBoard4Para(){
		//Select clock Parameters as required to generate the sample rate.
		RETURN_CODE retCode = AlazarSetCaptureClock(
			boardHandle,
			clockSourceId,
			sampleRateId,
			clockEdgeId,
			clockDecimation
			);
		if (retCode != ApiSuccess){
			return retCode;
		}
		//Select input parameters as required
		retCode = AlazarInputControl(
			boardHandle,
			CHANNEL_A,
			inputCouplingIdA,
			inputRangeIdA,
			inputImpedanceIdA
			);
		if (retCode != ApiSuccess){
			return retCode;
		}
		retCode=AlazarSetBWLimit(
			boardHandle,
			CHANNEL_A,
			0				//0 = disable, 1 = enable
			);
		if (retCode != ApiSuccess){
			return retCode;
		}
		retCode = AlazarInputControl(
			boardHandle,
			CHANNEL_B,
			inputCouplingIdB,
			inputRangeIdB,
			inputImpedanceIdB
			);
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		retCode=AlazarSetBWLimit(
			boardHandle,
			CHANNEL_B,
			0				//0 = disable, 1 = enable
			);
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		retCode=AlazarSetTriggerOperation(
			boardHandle,
			triggerOperation,
			TRIG_ENGINE_J,
			triggerSourceIdJ,
			triggerSlopeIdJ,
			triggerLevelJ,
			TRIG_ENGINE_K,
			triggerSourceIdK,
			triggerSlopeIdK,
			triggerLevelK
			);
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		retCode=AlazarSetExternalTrigger(
			boardHandle,
			triggerExCouplingId,
			triggerExRangeId
			);
		if (retCode!=ApiSuccess)
		{
			return retCode;
		}
		retCode=AlazarSetTriggerDelay(boardHandle, triggerDelaySamples);
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		triggerTimeoutClocks=static_cast<U32>(triggerTimeoutSec / 10.e-6 + 0.5);
		retCode=AlazarSetTriggerTimeOut(boardHandle,triggerTimeoutClocks);
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		retCode=AlazarConfigureAuxIO(boardHandle,AUXMode,AUXParameter);
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		return retCode;
	}
	RETURN_CODE AlazarInfo::GetAcqParam(){
		switch (inputChannel){
		case CHANNEL_A:
		case CHANNEL_B:
			channelCount=1;break;
		case CHANNEL_A | CHANNEL_B:
			channelCount=2;break;
		default:
			channelCount=0;break;
		}
		// Get the sample size in bits, and the on-board memory size in samples per channel
		U8 bitsPerSample=0;
		U32 maxSamplesPerChannel=0;
		RETURN_CODE retCode = AlazarGetChannelInfo(
			boardHandle,
			&maxSamplesPerChannel,
			&bitsPerSample
			);
		if (retCode != ApiSuccess){
			return retCode;
		}
		// Calculate the size of each DMA buffer in bytes
		bytesPerSample = (bitsPerSample + 7) / 8;
		samplesPerRecord = preTriggerSamples + postTriggerSamples;
		bytesPerRecord = bytesPerSample * samplesPerRecord;
		bytesPerBuffer = bytesPerRecord * recordsPerBuffer * channelCount;
		return retCode;
	}
	bool AlazarInfo::IsAcqStoped(){
		return acqStop;
	}
	void AlazarInfo::StopAcq(){
		acqStop=true;
	}
	void AlazarInfo::BeginAcq(){
		acqStop=false;
	}
	void AlazarInfo::GetImageSize(int* w,int* h){
		*w=samplesPerRecord;
		*h=recordsPerBuffer;
	}
	bool AlazarInfo::BeforeAsyncAcqusition(int channel,int buffer_nums){
		SetChannalMask(channel);
		bool success=true;
		RETURN_CODE return_code;
		int record_nums=0;
		if (buffer_nums<0)
			record_nums=0x7fffffff;
		else
			record_nums=buffer_nums*recordsPerBuffer;
		if (success){
			return_code = AlazarSetRecordSize(
				boardHandle,
				preTriggerSamples,
				postTriggerSamples
				);
			success = ParseError(return_code);
		}
		if (success){
			return_code = AlazarBeforeAsyncRead(
				boardHandle,
				inputChannel,
				-(long)preTriggerSamples,
				samplesPerRecord,
				recordsPerBuffer,
				record_nums,
				ADMA_EXTERNAL_STARTCAPTURE | ADMA_NPT
				);
			success = ParseError(return_code);
		}
		for (U32 bufferIndex = 0;
			(bufferIndex < BUFFER_COUNT) && (buffer_nums<0||bufferIndex<buffer_nums) && (success == true); 
			bufferIndex++){
			U8* pBuffer = bufferArray[bufferIndex];
			return_code = AlazarPostAsyncBuffer(boardHandle, pBuffer, bytesPerBuffer);
			success = ParseError(return_code);
		}
		return success;
	}
	bool AlazarInfo::ReadCalibrationData(vector<double>& calib_data){
		bool success=BeforeAsyncAcqusition(CHANNEL_B,1);
		RETURN_CODE return_code;
        calib_data.resize(bytesPerRecord,0);
		if (success){
			return_code = AlazarStartCapture(boardHandle);
			success = ParseError(return_code);
		}
		U8* pBuffer=nullptr;
		if (success){
			DWORD timeout_ms = 5000;
			pBuffer=bufferArray[0];
			return_code = AlazarWaitAsyncBufferComplete(boardHandle, pBuffer, timeout_ms);
			success = ParseError(return_code);
			return_code = AlazarAbortAsyncRead(boardHandle);
			success = ParseError(return_code);
		}
		if (!success){
			cerr<<"Read Calib Data Failed!!"<<endl;
		}
		if (success){
			for (int i=0;i<calib_data.size();i++){
				calib_data[i] = 0;
				for (int j = 0; j<calib_record_num; j++){
					calib_data[i] += static_cast<double>(pBuffer[j*bytesPerRecord + i])/calib_record_num;
				}
			}
			//save calibration data for other use
			FILE* fpData = fopen("../../../Calibs.dat", "wb");
			U8* pRecord = pBuffer;
			for (U32 record = 0; (record < recordsPerBuffer) && (success == TRUE); record++){
				size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), bytesPerRecord, fpData);
				if (bytesWritten != bytesPerRecord){
					success = false;
				}
				pRecord += samplesPerRecord;
			}
			fclose(fpData);
		}
		return success;
	}
    bool AlazarInfo::ReadDriftData(vector<int>& calib_index,vector<float>& drift){
        bool success=BeforeAsyncAcqusition(CHANNEL_A,1);
        RETURN_CODE return_code;
        drift.resize(calib_index.size(),0);
		if (success){
			return_code = AlazarStartCapture(boardHandle);
			success = ParseError(return_code);
		}
		U8* pBuffer=nullptr;
		if (success){
			DWORD timeout_ms = 5000;
			pBuffer=bufferArray[0];
			return_code = AlazarWaitAsyncBufferComplete(boardHandle, pBuffer, timeout_ms);
			success = ParseError(return_code);
			return_code = AlazarAbortAsyncRead(boardHandle);
			success = ParseError(return_code);
		}
		if (!success){
			cerr<<"Read Drift Data Failed!!"<<endl;
		}
		if (success){
            for (int i=0;i<drift.size();i++){
                drift[i]=0;
				if (calib_index[i]<0) continue;
                for (int j=0;j<recordsPerBuffer;j++){
                    drift[i]+=pBuffer[j*bytesPerRecord+calib_index[i]];
                }
                drift[i]/=recordsPerBuffer;
            }
			//save drift data for other use
			FILE* fpData = fopen("../../../Drifts.dat", "wb");
			U8* pRecord = pBuffer;
			for (U32 record = 0; (record < recordsPerBuffer) && (success == TRUE); record++){
				size_t bytesWritten = fwrite(pRecord, sizeof(BYTE), bytesPerRecord, fpData);
				if (bytesWritten != bytesPerRecord){
					success = false;
				}
				pRecord += samplesPerRecord;
			}
			fclose(fpData);
		}
		return success;
    }
}
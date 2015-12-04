#include "stdafx.h"
#include "AlazarInfo.h"

namespace OCTProgram
{
	AlazarInfo::AlazarInfo()
	{

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
	AlazarInfo::~AlazarInfo()
	{
		DeleteBuffer();
	}
	void AlazarInfo::DeleteBuffer()
	{
		if (bufferArray)
		{
			for (U32 bufferIndex = 0; bufferIndex < BUFFER_COUNT; bufferIndex++)
			{
				if (bufferArray[bufferIndex] != NULL)
				{
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
	bool AlazarInfo::ConfigureBoard(char* cfgParaDir)
	{
		DeleteBuffer();
		if (!GetCfgParam(cfgParaDir))
			return false;
		bool success=true;
		bufferArray = new U8*[BUFFER_COUNT];
		boardHandle = AlazarGetBoardBySystemID(systemId, boardId);
		RETURN_CODE return_code=CfgBoard4Para();
		if (return_code!=ApiSuccess)
			success=false;
		if (success)
		{
			return_code=GetAcqParam();
			if (return_code!=ApiSuccess)
				success=false;
		}
		if (success)
		{
			U32 bufferIndex=0;
			for (bufferIndex = 0; (bufferIndex < BUFFER_COUNT) && (success == true); bufferIndex++)
			{
#ifdef _WIN32
				bufferArray[bufferIndex] = static_cast<U8*>(
					VirtualAlloc(NULL, bytesPerBuffer, MEM_COMMIT, PAGE_READWRITE)
					);
#else
				bufferArray[bufferIndex] = static_cast<U8*>(malloc(bytesPerBuffer));
#endif
				if (bufferArray[bufferIndex] == NULL)
				{
					success = false;
				}
			}
			if (!success)
				return false;
		}
		return success;
	}
	bool AlazarInfo::GetCfgParam(char* cfgParaDir)
	{
		// some times later, it may changed to json
		std::ifstream ifs(cfgParaDir,std::ios::in);
		if (!ifs.is_open())
			return false;
		std::string tStr;
		while (!ifs.eof())
		{
			if (ifs.good())
			{
				std::getline(ifs,tStr);
				if (tStr.length()&&tStr.back()=='#')
				{
					if (tStr=="System Info #")
					{
						ifs.ignore(30,'=');
						ifs>>BUFFER_COUNT;
						ifs.ignore(30,'=');
						ifs>>samplesPerSec;
						ifs.ignore(30,'=');
						ifs>>systemId;
						ifs.ignore(30,'=');
						ifs>>boardId;
					}else if (tStr=="Clock #")
					{
						ifs.ignore(30,'=');
						ifs>>clockSourceId;
						ifs.ignore(30,'=');
						ifs>>sampleRateId;
						ifs.ignore(30,'=');
						ifs>>clockEdgeId;
						ifs.ignore(30,'=');
						ifs>>clockDecimation;
					}else if (tStr=="ChannelInput #")
					{
						ifs.ignore(30,'=');
						ifs>>inputChannel;
						ifs.ignore(30,'=');
						ifs>>inputCouplingIdA;
						ifs.ignore(30,'=');
						ifs>>inputRangeIdA;
						ifs.ignore(30,'=');
						ifs>>inputImpedanceIdA;
						ifs.ignore(30,'=');
						ifs>>inputCouplingIdB;
						ifs.ignore(30,'=');
						ifs>>inputRangeIdB;
						ifs.ignore(30,'=');
						ifs>>inputImpedanceIdB;
					}else if (tStr=="Trigger #")
					{
						ifs.ignore(30,'=');
						ifs>>triggerOperation;
						ifs.ignore(30,'=');
						ifs>>triggerSourceIdJ;
						ifs.ignore(30,'=');
						ifs>>triggerSlopeIdJ;
						ifs.ignore(30,'=');
						ifs>>triggerLevelJ;
						ifs.ignore(30,'=');
						ifs>>triggerSourceIdK;
						ifs.ignore(30,'=');
						ifs>>triggerSlopeIdK;
						ifs.ignore(30,'=');
						ifs>>triggerLevelK;
						ifs.ignore(30,'=');
						ifs>>triggerExCouplingId;
						ifs.ignore(30,'=');
						ifs>>triggerExRangeId;
						ifs.ignore(30,'=');
						ifs>>triggerDelaySec;
						ifs.ignore(30,'=');
						ifs>>triggerTimeoutSec;
					}else if (tStr=="AUX Seting #")
					{
						ifs.ignore(30,'=');
						ifs>>AUXMode;
						ifs.ignore(30,'=');
						ifs>>AUXParameter;
					}else if (tStr=="Acq Para #")
					{
						ifs.ignore(30,'=');
						ifs>>preTriggerSamples;
						ifs.ignore(30,'=');
						ifs>>postTriggerSamples;
						ifs.ignore(30,'=');
						ifs>>recordsPerBuffer;
						ifs.ignore(30,'=');
						ifs>>buffersPerImage;
						ifs.ignore(30,'=');
						ifs>>acqMode;
						ifs.ignore(30,'=');
						ifs.getline(saveName,30);
					}
				}
			}
		}
		ifs.close();
		return true;
	}
	void AlazarInfo::SetChannalMask(int channalID)
	{
		inputChannel=channalID;
		GetAcqParam();
	}
	RETURN_CODE AlazarInfo::CfgBoard4Para()
	{
		//Select clock Parameters as required to generate the sample rate.
		RETURN_CODE retCode = AlazarSetCaptureClock(
			boardHandle,
			clockSourceId,
			sampleRateId,
			clockEdgeId,
			clockDecimation
			);
		if (retCode != ApiSuccess)
		{
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
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		retCode=AlazarSetBWLimit(
			boardHandle,
			CHANNEL_A,
			0				//0 = disable, 1 = enable
			);
		if (retCode != ApiSuccess)
		{
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
		triggerDelaySamples=static_cast<U32>(triggerDelaySec*samplesPerSec+0.5);
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
	RETURN_CODE AlazarInfo::GetAcqParam()
	{
		switch (inputChannel)
		{
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
		if (retCode != ApiSuccess)
		{
			return retCode;
		}
		// Calculate the size of each DMA buffer in bytes
		bytesPerSample = (bitsPerSample + 7) / 8;
		samplesPerRecord = preTriggerSamples + postTriggerSamples;//2048
		bytesPerRecord = bytesPerSample * samplesPerRecord;//2048
		bytesPerBuffer = bytesPerRecord * recordsPerBuffer * channelCount;//2048000
		return retCode;
	}
	bool AlazarInfo::IsAcqStoped()
	{
		return acqStop;
	}
	void AlazarInfo::StopAcq()
	{
		acqStop=true;
	}
	void AlazarInfo::BeginAcq()
	{
		acqStop=false;
	}
	void AlazarInfo::GetImageSize(int* w,int* h)
	{
		*w=1024;//w must be 1024
		*h=recordsPerBuffer;
	}
}
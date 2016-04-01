#pragma once 
#include "api/AlazarError.h"
#include "api/AlazarApi.h"
#include "api/AlazarCmd.h"

namespace OCTProgram
{
	class AlazarInfo
	{
	public:
		AlazarInfo();
		~AlazarInfo();
	public:
		HANDLE boardHandle;

		int BUFFER_COUNT;
		U8** bufferArray;
		U32 inputChannel;

		U32 preTriggerSamples;
		U32	postTriggerSamples;
		U32	recordsPerBuffer;

		int channelCount;
		U32 samplesPerRecord;
		U32 bytesPerRecord;
		U32 bytesPerBuffer;
		int buffersPerImage;
	protected:
		U32 systemId;
		U32 boardId;

		U32 clockSourceId;
		U32 sampleRateId;
		U32 clockEdgeId;
		U32 clockDecimation;

		U32 inputCouplingIdA;
		U32 inputRangeIdA;
		U32 inputImpedanceIdA;
		U32 inputCouplingIdB;
		U32 inputRangeIdB;
		U32 inputImpedanceIdB;

		U32 triggerOperation;
		U32 triggerSourceIdJ;
		U32 triggerSlopeIdJ;
		U32 triggerLevelJ;
		U32 triggerSourceIdK;
		U32 triggerSlopeIdK;
		U32 triggerLevelK;
		U32 triggerExCouplingId;
		U32 triggerExRangeId;

		U32 AUXMode;
		U32 AUXParameter;
	private:
		U32 triggerDelaySamples;
		U32 triggerTimeoutClocks;
		U32 bytesPerSample;
		bool acqStop;
	public:
		bool ConfigureBoard(char*);
		void GetImageSize(int* w,int* h);
		bool IsAcqStoped();
		void BeginAcq();
		void StopAcq();
		//int CalibData(int mode,char* dataFile,char* indexFile);
		void SetChannalMask(int channalID);
	private:
		bool GetCfgParam(char*);
		RETURN_CODE CfgBoard4Para();
		RETURN_CODE GetAcqParam();
		void DeleteBuffer();
	};
}
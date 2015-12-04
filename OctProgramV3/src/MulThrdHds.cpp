#include "stdafx.h"
#include "MulThrdHds.h"

HANDLE _HMutex=			::CreateMutex(NULL,false,NULL);
HANDLE _HEmptyGPUMem=	::CreateSemaphore(NULL,2,2,NULL);
HANDLE _HFullGPUMem=	::CreateSemaphore(NULL,0,2,NULL);
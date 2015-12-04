#pragma once
#include "AlazarInfo.h"
#include "AdvantInfo.h"
#include "CLGL.h"
#include <Windows.h>
typedef class _SAcqThread
{
public:
    _SAcqThread(){
        thread_handle = NULL;
        begin_acquisition = CreateEvent(NULL, true, false, NULL);
        end_thread = CreateEvent(NULL, false, false, NULL);
        acquisition_running = CreateEvent(NULL, true, false, NULL);
        alazar = nullptr;
        clgl = nullptr;
		adv=nullptr;
    }
    ~_SAcqThread(){
        EndThread();
        CloseHandle(begin_acquisition);
        CloseHandle(end_thread);
        CloseHandle(acquisition_running);
        end_thread = NULL;
        begin_acquisition = NULL;
        alazar = NULL;
        clgl = NULL;
    }
    void EndThread(){
        if (thread_handle){
            ResetEvent(begin_acquisition);
            SetEvent(end_thread);
            WaitForSingleObject(thread_handle, INFINITE);
            CloseHandle(thread_handle);
            thread_handle = NULL;
        }
    }
public:
    HANDLE thread_handle;
    HANDLE end_thread;
    HANDLE begin_acquisition;
    HANDLE acquisition_running;
	OCTProgram::AlazarInfo* alazar;
	OCTProgram::AdvInfo* adv;
	OpenCLGLClass* clgl;
}AcqParam;
typedef class _SProcessThread
{
public:
    _SProcessThread(){
        thread_handle = NULL;
        end_thread = CreateEvent(NULL, false, false, NULL);
        clgl = NULL;
    }
    ~_SProcessThread(){
        EndThread();
        CloseHandle(end_thread);
        end_thread = NULL;
        clgl = NULL;
    }
    void EndThread(){
        if (thread_handle){
            SetEvent(this->end_thread);
            WaitForSingleObject(this->thread_handle, INFINITE);
            CloseHandle(this->thread_handle);
            thread_handle = NULL;
        }
    }
public:
    HANDLE thread_handle;
    HANDLE end_thread;
	OpenCLGLClass* clgl;
}ProcessParam;
unsigned __stdcall ACQDATA(void* lpParam);
unsigned __stdcall PROCESSDATA(void* lpParam);
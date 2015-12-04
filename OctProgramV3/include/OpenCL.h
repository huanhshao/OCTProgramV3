#pragma once 
#include "CL/cl_gl_ext.h"
#include "GL/glew.h"
#pragma comment(lib,"OpenCL.lib")

class OpenCLClass
{
private:
	cl_program program;
	cl_context context;
	cl_command_queue queue;
	cl_device_id device_id;
	size_t gws[3];
	size_t lws[3];
	//FFT Param
	int line;
	cl_mem* cl_data;
	int maxBufferCount;
	cl_kernel kfft;
	//image param
	cl_mem clTexMemFront;
	cl_mem clTexMemBack;
public:
	OpenCLClass();
	~OpenCLClass();
	int InitFFT(int n,int m);
	int EnqueueCalFFT(unsigned char* buffer,int n,int m,int count,cl_event* fftEvent);
	int BindGLTexture(GLuint texDst,GLuint texSrc);
	void SwapTexMem();
	void WaitEvent(int count,cl_event* waitlist);
	void AcquireTex();
private:
	int InitCL();
	int InitCLGL();
	int LoadProgram(const char* filename);
	int CheckofPow2(int n);
};

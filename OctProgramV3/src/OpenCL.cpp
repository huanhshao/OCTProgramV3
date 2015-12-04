#include "stdafx.h"
#include "MulThrdHds.h"
#include "CLGL.h"

//#pragma OPENCL EXTENSION cl_khr_gl_event : enable
OpenCL::OpenCL()
{
	clTexMemFront=NULL;
	clTexMemBack=NULL;
	k=0.1;
	a=10;
}
void OpenCL::Initialize(OpenGL& gl){
	if (InitCLFromGL()==1){
		cout<<"OpenCL Failed!"<<endl;
		exit(0);
	}
	BindGLTexture(gl.GetFrontTex(),gl.GetBackTex());
	AcquireTex();
}
void OpenCL::BindGLTexture(GLuint front,GLuint back){
	cl_int err;
	clTexMemFront=clCreateFromGLTexture2D(
		context,CL_MEM_READ_WRITE,GL_TEXTURE_2D,0,front,&err);
	clTexMemBack=clCreateFromGLTexture2D(
		context,CL_MEM_READ_WRITE,GL_TEXTURE_2D,0,back,&err);
}
OpenCL::~OpenCL(){
	clReleaseMemObject(clTexMemFront);
	clReleaseMemObject(clTexMemBack);
	if (kfft){
		clReleaseKernel(kfft);
	}
	if (hist){
		clReleaseKernel(hist);
	}
	if (program!=0){
		clReleaseProgram(program);
	}
	if (queue!=0){
		clReleaseCommandQueue(queue);
	}
	if (context!=0){
		clReleaseContext(context);
	}
}
int OpenCL::LoadProgram(const char* filename)
{
	std::ifstream ifs(filename, std::ios_base::binary);
	if(!ifs.good()){
		cout<<"Can't Find Kernal File!!";
		program=0;
		return 1;
	}
	
	// get file length
	ifs.seekg(0, std::ios_base::end);
	size_t length = static_cast<size_t>(ifs.tellg());
	ifs.seekg(0, std::ios_base::beg);

	// read program source
	std::vector<char> data(length + 1);
	ifs.read(&data[0], length);
	data[length] = 0;

	// create and build program 
	const char* source = &data[0];
	program = clCreateProgramWithSource(context, 1, &source, 0, 0);
	if(program == 0) {
		return 1;
	}
	if(clBuildProgram(program, 1, &device_id, NULL, NULL, NULL) != CL_SUCCESS) {
#ifdef __DEBUG__
		size_t len;
		char buffer[0x2048];
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		cout<<buffer<<endl;
		system("pause");
#endif
		program=0;
		assert(false);
		return 1;
	}
	return 0;
}
int OpenCL::InitCLFromGL()
{
	cl_int err;
	cl_uint numPlt;

	err = clGetPlatformIDs(0, 0, &numPlt);
	if(err != CL_SUCCESS||numPlt<=0) {
		return 1;
	}
	std::vector<cl_platform_id> platforms(numPlt);
	err = clGetPlatformIDs(numPlt, &platforms[0], &numPlt);
	if(err != CL_SUCCESS) {
		return 1;
	}

	cl_uint numDev;
	err=clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,0,NULL,&numDev);
	if (err != CL_SUCCESS||numDev<=0){
		return 1;
	}
	err=clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,1,&device_id,NULL);

	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties) wglGetCurrentContext(),
		CL_WGL_HDC_KHR, (cl_context_properties) wglGetCurrentDC(),
		CL_CONTEXT_PLATFORM, (cl_context_properties) platforms[0],
		0
	};
	context=clCreateContext(properties,1,&device_id,NULL,NULL,NULL);

	queue = clCreateCommandQueue(context, device_id, 0, 0);
	if(queue == 0){
		return 1;
	}
	LoadProgram("kernel.cl");
	if(program == 0){
		cout<<"Build Program Failed!!"<<endl;
		return 1;
	}
	kfft = clCreateKernel(program, "kfft", NULL);
	hist = clCreateKernel(program, "hist", NULL);
	return 0;
}
int OpenCL::CheckofPow2(int n)
{
	if (n&(n-1))
	{
		return 0;
	}
	else
	{
		int m=0;
		while((n=n>>1))
			m++;
		return m;
	}
}
int OpenCL::EnqueueCalFFT(memStat* pms,int n,int m,int count)
{
	ReleaseTex();
	AcquireTex();
	if(CheckofPow2(n)<1){
		return 2;
	}
	//n must be 1024,otherwise you should write a kernel yourself
	gws[0]=256;
	gws[1]=m;
	lws[0]=256;
	lws[1]=1;
	WaitForSingleObject(_HMutex,INFINITE);
	clSetKernelArg(kfft, 0, sizeof(cl_mem), (void *)&(pms->memName));
	clSetKernelArg(kfft, 1, sizeof(cl_mem), (void *)&clTexMemBack);
	clSetKernelArg(kfft, 2, sizeof(cl_float), (void *)&k);
	clSetKernelArg(kfft, 3, sizeof(cl_float), (void *)&a);
	ReleaseMutex(_HMutex);
	cl_event fftEvent;
	clEnqueueNDRangeKernel(queue, kfft, 2, NULL, gws, lws, 1, &pms->writeEvent, &fftEvent);
	clWaitForEvents(1,&fftEvent);
	return 0;
}
void OpenCL::SetHstParam(double min,double max,double lastMin,double lastMax)
{
	//k=((float)(lastMax-lastMin))/((float)(max-min))*k;
	//a=(min-lastMin)/k/(max-min)+a;
	WaitForSingleObject(_HMutex,INFINITE);
	a=max;
	k=min;
	ReleaseMutex(_HMutex);
}
cl_mem OpenCL::GenMem(int n,int m)
{
	return clCreateBuffer(context,CL_MEM_READ_WRITE,n*m*sizeof(cl_float),NULL,NULL);
}
void OpenCL::WriteBuffer(float* buffer,memStat* pms,size_t bufferLength)
{
	clEnqueueWriteBuffer(queue,pms->memName,CL_TRUE,0,sizeof(float)*bufferLength,buffer,0,NULL,&pms->writeEvent);
}
void OpenCL::ReleaseMem(cl_mem mem)
{
	if (mem!=nullptr)
		clReleaseMemObject(mem);
}
void OpenCL::SwapTexMem()
{
	cl_mem tmp;
	tmp=clTexMemBack;
	clTexMemBack=clTexMemFront;
	clTexMemFront=tmp;
}
void OpenCL::AcquireTex()
{
	clEnqueueAcquireGLObjects(queue,1,&clTexMemBack,0,NULL,NULL);
}
void OpenCL::ReleaseTex()
{
	clEnqueueReleaseGLObjects(queue,1,&clTexMemBack,0,NULL,NULL);
}
void OpenCL::EnqueueCalHist(int* hst,int n,int m)
{
	const int COUNTN=64;
	cl_event hstEvent;
	cl_mem hstGpu=clCreateBuffer(context,CL_MEM_READ_WRITE|CL_MEM_COPY_HOST_PTR,256*sizeof(cl_int),hst,NULL);
	SwapTexMem();
	AcquireTex();
	clSetKernelArg(hist, 0, sizeof(cl_mem), (void *)&clTexMemBack);
	clSetKernelArg(hist, 1, sizeof(cl_mem), (void *)&hstGpu);
	clSetKernelArg(hist, 2, sizeof(cl_int), (void *)&COUNTN);
	gws[0]=((n+255)/256)*256;
	gws[1]=(m+COUNTN-1)/COUNTN;
	lws[0]=256;
	lws[1]=1;
	clEnqueueNDRangeKernel(queue,hist,2,NULL,gws,lws,0,NULL,&hstEvent);
	clWaitForEvents(1,&hstEvent);
	ReleaseTex();
	SwapTexMem();
	clEnqueueReadBuffer(queue,hstGpu,CL_TRUE,0,sizeof(cl_int)*256,hst,0,NULL,NULL);
	clReleaseMemObject(hstGpu);
}
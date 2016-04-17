#include "stdafx.h"
#include "CLGL.h"
#include "MulThrdHds.h"

OpenCLGLClass::OpenCLGLClass(){
	n_=0;
	m_=0;
	BUFFERCOUNT=2;
	time=0;
	switchCount=0;
	FPS=100000;
	minLev=0;
	maxLev=255;
}
void OpenCLGLClass::Initialize(HDC hdc,int n,int m){
	assert(n==1024);
	mgl.Initialize(n,m);
	mgl.Init(hdc);
	mcl.Initialize(mgl);
	PrepareResources(n,m);
}
OpenCLGLClass::~OpenCLGLClass()
{
	ReleaseMem();
}
void OpenCLGLClass::ClearQueue(std::queue<memStat*> mem_queue){
	while(!mem_queue.empty()){
		mem_queue.pop();
	}
}
void OpenCLGLClass::PrepareResources(int n,int m){
	if (n_!=n||m_!=m){
		ReleaseMem();
		n_=n;
		m_=m;
		while(WaitForSingleObject(_HFullGPUMem,100)==WAIT_OBJECT_0){
			ReleaseSemaphore(_HFullGPUMem,1,NULL);
			Sleep(100);
		}
		ClearQueue(memQueueEm);
		ClearQueue(memQueueFu);
		buffer_mems_.resize(BUFFERCOUNT);
		for (int i=0;i<buffer_mems_.size();i++){
			buffer_mems_[i].memName=mcl.GenMem(n_,m_,sizeof(cl_uchar));
			memQueueEm.push(&buffer_mems_[i]);
		}
		mcl.ReleaseTex();
		mgl.ReshapeTex(1024,m);
		mcl.BindGLTexture(mgl.GetFrontTex(),mgl.GetBackTex());
		mcl.AcquireTex();
	}
}
void OpenCLGLClass::SendDataToGPU(unsigned char* buffer){
	if (!memQueueEm.size())
		return;
	mcl.WriteBuffer(buffer,memQueueEm.front(),n_*m_);
}
void OpenCLGLClass::EmptyToFull(){
    memQueueFu.push(memQueueEm.front());
    memQueueEm.pop();
}
void OpenCLGLClass::CalFFT(){
	if (!memQueueFu.size())
		return;
	mcl.EnqueueCalFFT(memQueueFu.front(),n_,m_,0);
}
void OpenCLGLClass::FullToEmpty(){
	memQueueFu.front()->writeEvent=NULL;
	memQueueEm.push(memQueueFu.front());
	memQueueFu.pop();
}
void OpenCLGLClass::SwapTexBuffer(){
	if (switchCount==11){
		time=GetTickCount()-time;
		FPS=10000/((float)(time));
		if (FPS<1) FPS=0;
		switchCount=0;
		time=GetTickCount();
	}
	mcl.ReleaseTex();
	mcl.SwapTexMem();
	mgl.SwapTexture();
	mcl.AcquireTex();
	switchCount++;
}
int OpenCLGLClass::GetFPS()
{
	return (int)(FPS*100);
}
void OpenCLGLClass::SetColorLevels(double a,double b)
{
	//if (a==b)
	//	return;
	//if (a>b)
	//{
	//	a=a+b;
	//	b=a-b;
	//	a=a-b;
	//}
	mcl.SetHstParam(a,b,minLev,maxLev);
	//minLev=a;
	//maxLev=b;
}
void OpenCLGLClass::SetGLContext(int i)
{
	mgl.SetContext(i);
}
void OpenCLGLClass::SetViewPort(int x, int y, int width, int height)
{
	mgl.ViewPort(x,y,width,height);
}
void OpenCLGLClass::RenderScene()
{
	mgl.RenderScene();
}
bool OpenCLGLClass::CaptureScreen()
{
	return mgl.CaptureScreen();
}
void OpenCLGLClass::CalHistogram(int* hst)
{
	for (int i=0;i<256;i++){
		hst[i]=0;
	}
	int w=0;
	int h=0;
	mgl.GetTexSize(&w,&h);
	mcl.EnqueueCalHist(hst,w,h);
}
void OpenCLGLClass::ReleaseMem(){
	for (int i=0;i<buffer_mems_.size();i++){
		mcl.ReleaseMem(buffer_mems_[i].memName);
	}
	buffer_mems_.clear();
}
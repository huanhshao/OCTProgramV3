#pragma once 
#include "api/CL/cl.h"
#include "api/CL/cl_gl_ext.h"
#include "api/GL/glew.h"
#include <queue>
#include <Windows.h>
#pragma comment(lib,"OpenCL.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"User32.lib")
typedef struct{
	cl_mem memName;
	cl_event writeEvent;
}memStat;
class OpenGL{
public:
	OpenGL();
	~OpenGL(void);
	void Initialize(int n,int m);
	bool Init(HDC hdc);
	void RenderScene();
	void ViewPort(int x, int y, int width, int height);
	bool CaptureScreen();
	void SwapTexture();
	GLuint GetFrontTex();
	GLuint GetBackTex();
	void SetContext(int i);
	void GetTexSize(int* w,int* h);
	void ReshapeTex(int n,int m);
private:
	int OpenGL::IsGLExtensionSupported(const char *extension);
	void InitOpenGL();
	GLuint GenGLTex(int n,int m,int type,GLubyte* pixels=NULL);
private:
	HDC m_hDC;
	HGLRC m_rc;
	HGLRC rcShareTex;
	int list;
	GLsizei texWidth;
	GLsizei texHeight;
	GLuint tex4CL;
	GLuint tex4GL;
	GLint texLast;
};
class OpenCL{
public:
	OpenCL();
	~OpenCL();
	void Initialize(OpenGL& gl);
	int EnqueueCalFFT(memStat* pms,int n,int m,int count);
	void SwapTexMem();
	void WaitEvent(int count,cl_event* waitlist);
	void AcquireTex();
	void ReleaseTex();
	cl_mem GenMem(int n,int m,size_t sample_byte=sizeof(cl_float));
	void WriteBuffer(unsigned char* buffer,memStat* pms,size_t bufferLength);
	void ReleaseMem(cl_mem mem);
	void EnqueueCalHist(int* hst,int n,int m);
	void SetHstParam(double min,double max,double lastMin,double lastMax);
	void BindGLTexture(GLuint front,GLuint back);
	void WriteCalib(vector<int>& calib_indexs);
    void WriteDrift(vector<float>& drifts);
	void SaveTexture(int id);
private:
	int InitCL();
	int InitCLFromGL();		//Must use after a GL texture created
	int LoadProgram(const char* filename);
	int CheckofPow2(int n);
private:
	cl_program program;
	cl_context context;
	cl_command_queue queue;
	cl_device_id device_id;
	size_t gws[3];
	size_t lws[3];
	//FFT Param
	cl_kernel kfft;
	//Image Param
	cl_mem clTexMemFront;
	cl_mem clTexMemBack;
	//Hst Param
	cl_kernel hist;
	cl_float k;
	cl_float a;
	//data param
	cl_mem cl_calib_mem;
    cl_mem cl_drift_mem;
	//buffer
	cl_mem cl_image_mem_back_;
	cl_mem cl_image_mem_front_;
};
class OpenCLGLClass{
public:
	OpenCLGLClass();
	~OpenCLGLClass();
	void PrepareResources(int n,int m);
	void Initialize(HDC hdc,int n,int m);
	void SendDataToGPU(unsigned char* buffer);
	void CalFFT();
	void SwapTexBuffer();
	void SetGLContext(int i);

	void SetViewPort(int x,int y,int width,int height);
	void RenderScene();
	bool CaptureScreen();
	int GetFPS();

	void CalHistogram(int* hst);
	void SetColorLevels(double a,double b);
	void FullToEmpty();
    void EmptyToFull();
	void WriteCalibIndex(vector<int>& calib_index);
    void WriteDriftData(vector<float>& drift);
	void SaveTexture(int id){mcl.SaveTexture(id);}
private:
	void ReleaseMem();
	void ClearQueue(std::queue<memStat*> mem_queue);
private:
	OpenCL mcl;
	OpenGL mgl;
	int BUFFERCOUNT;
	int n_;
	int m_;
	std::vector<memStat> buffer_mems_;
	std::queue<memStat*> memQueueEm;
	std::queue<memStat*> memQueueFu;

	DWORD time;
	int switchCount;
	float FPS;
	int minLev;
	int maxLev;
};
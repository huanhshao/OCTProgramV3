#pragma once 
#include "OpenCL.h"
#include "GL/glew.h"
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"User32.lib")

class OpenGL
{
public:
	OpenGL();
	bool Init(HDC hdc);
    void RenderScene();
    void ViewPort(int x, int y, int width, int height);
	bool CaptureScreen(int c);
	void SwapTexture();
	//CL function
	void SentDataToCL(unsigned char* buffer,int n,int m,int count,cl_event* fftEvent);
	void WaitCLEventList(int count,cl_event* waitlist);
	void SwapCLTexture();
	void InitCLKernel(int n,int m);
	void CLAcquireTex();
private:
	int OpenGL::IsGLExtensionSupported(const char *extension);
	void InitOpenGL();
public:
	~OpenGL(void);
private:
	HDC m_hDC;
	HGLRC m_rc;
	OpenCLClass* m_cl;
	int list;
	GLuint tex4CL;
	GLuint tex4GL;
	GLuint texLast;
};
#include "stdafx.h"
#include "CLGL.h"
#include <string>
#include <fstream>
#include <math.h>

OpenGL::OpenGL()
{
	m_hDC=NULL;
	m_rc=NULL;
	rcShareTex=NULL;
	list=0;
	//n should be 1024//or n be 512 for a half image
}
void OpenGL::Initialize(int n,int m){
	assert(n==1024);
	texWidth=n;
	texHeight=m;
	tex4GL=0;
	tex4CL=0;
	texLast=0;
}
OpenGL::~OpenGL(void)
{  
	if (list!=0&&glIsList(list)){
		glDeleteLists(list,1);
		list=0;
	}
	if (tex4CL!=0){
		glDeleteTextures(1,&tex4CL);
	}
	if (tex4GL!=0){
		glDeleteTextures(1,&tex4GL);
	}
	glDisable(GL_TEXTURE_2D);
	wglMakeCurrent(0,0);
	wglDeleteContext(m_rc);
	wglDeleteContext(rcShareTex);
	m_rc=NULL;
	rcShareTex=NULL;
}
bool OpenGL::Init(HDC hdc)
{   
	m_hDC=hdc;
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion=1;
	pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
	pfd.iPixelType=PFD_TYPE_RGBA;
	pfd.cColorBits=32;
	pfd.cDepthBits=32;
	pfd.iLayerType=PFD_MAIN_PLANE;
	int cpf=ChoosePixelFormat(m_hDC,&pfd);
	if(cpf)
	{
		SetPixelFormat(m_hDC,cpf,&pfd);
		m_rc=wglCreateContext(m_hDC);//´´½¨RC
		rcShareTex=wglCreateContext(m_hDC);
		wglShareLists(rcShareTex,m_rc);
	}
	wglMakeCurrent(m_hDC,m_rc);
	glewInit();
	InitOpenGL();
	return true;
}
void OpenGL::InitOpenGL()
{	
	glEnable(GL_TEXTURE_2D);
	tex4CL=GenGLTex(texWidth,texHeight,0);
	tex4GL=GenGLTex(texWidth,texHeight,0);
	glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
	glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To D
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
GLuint OpenGL::GenGLTex(int n,int m,int type,GLubyte* pixels)
{
	GLuint tmptex=0;
	glGenTextures(1,&tmptex);
	if (tmptex!=0){
		glBindTexture(GL_TEXTURE_2D,tmptex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		if (type==0){
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F_ARB,n,m,0,GL_LUMINANCE,GL_FLOAT,NULL);
		}else if (type==1){
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F_ARB,n,m,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pixels);
		}
		glBindTexture(GL_TEXTURE_2D,0);
	}
	return tmptex;
}
void OpenGL::ViewPort(int x, int y, int width, int height)
{
	glViewport(x,y,width,height);
	glMatrixMode(GL_PROJECTION);		// Select The Projection Matrix
	glLoadIdentity();					// Reset The Projection Matrix
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);			// Select The Modelview Matrix
	glLoadIdentity(); 
	gluLookAt(4,1.8,8.3,4,1.8,0,0,1,0);
	RenderScene();
}

void OpenGL::RenderScene(){
	//h is fixed to 4, and w be count the same ratio.
	//float w=8/static_cast<double>(texHeight)*texWidth*0.9;
	//if (w<1) w=1;
	//if (w>8) w=8;
	//w=8;
	if( list == 0 ){
		GLfloat
			PointA[] = {0,0,0},
			PointB[] = {8,0,0},
			PointC[] = {8,4,0},
			PointD[] = {0,4,0};
		list = glGenLists(1);
		glNewList(list,GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(0.5,0.0);		glVertex3fv(PointA);
		glTexCoord2f(0.5,1.0);		glVertex3fv(PointB);
		glTexCoord2f(0.0,1.0);		glVertex3fv(PointC);
		glTexCoord2f(0.0,0.0);		glVertex3fv(PointD);
		glEnd();
		glEndList();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glPushMatrix();
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &texLast);
	glBindTexture(GL_TEXTURE_2D,tex4GL);
	glCallList(list);
	glBindTexture(GL_TEXTURE_2D,texLast);
	glPopMatrix();
	SwapBuffers(m_hDC);
}

bool OpenGL::CaptureScreen(){
	GLint viewport[4]; 
	glGetIntegerv( GL_VIEWPORT, viewport ); 
	GLint width  = viewport[2]; 
	GLint height = viewport[3]; 
	width -= width%4;
	GLubyte * bmpBuffer = NULL; 
	bmpBuffer = (GLubyte *)malloc(width*height*3*sizeof(GLubyte)); 
	if (!bmpBuffer) 
		return false; 
	glReadPixels(0, 0, width, height, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, bmpBuffer);  
	BITMAPFILEHEADER bitmapFileHeader; 
	BITMAPINFOHEADER bitmapInfoHeader; 
	bitmapFileHeader.bfType = 0x4D42;
	bitmapFileHeader.bfSize = width*height*3; 
	bitmapFileHeader.bfReserved1 = 0; 
	bitmapFileHeader.bfReserved2 = 0; 
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER); 
	bitmapInfoHeader.biWidth = width; 
	bitmapInfoHeader.biHeight = height; 
	bitmapInfoHeader.biPlanes = 1; 
	bitmapInfoHeader.biBitCount = 24; 
	bitmapInfoHeader.biCompression = BI_RGB; 
	bitmapInfoHeader.biSizeImage = 0; 
	bitmapInfoHeader.biXPelsPerMeter = 0; 
	bitmapInfoHeader.biYPelsPerMeter = 0; 
	bitmapInfoHeader.biClrUsed = 0; 
	bitmapInfoHeader.biClrImportant = 0; 
	char index[3];
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y_%m_%d_%H_%M_%S",localtime(&t));
	std::string filename="Capture\\grab_"+std::string(tmp)+".bmp";
	std::ofstream ofs(filename,std::ios::out|std::ios::binary);
	if (!ofs){
		free(bmpBuffer);
		return false;
	}
	ofs.write((const char*)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
	ofs.write((const char*)&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));
	ofs.write((const char*)bmpBuffer,width*height*3);
	ofs.close();
	free(bmpBuffer); 
	return true; 
}
void OpenGL::SetContext(int i){
	if (i==0){
		wglMakeCurrent(m_hDC,0);
	}else{
		wglMakeCurrent(m_hDC,rcShareTex);
	}
}
void OpenGL::SwapTexture(){
	tex4CL=tex4CL+tex4GL;
	tex4GL=tex4CL-tex4GL;
	tex4CL=tex4CL-tex4GL;
}
GLuint OpenGL::GetFrontTex(){
	return tex4GL;
}
GLuint OpenGL::GetBackTex(){
	return tex4CL;
}
void OpenGL::GetTexSize(int* w,int* h){
	*w=texWidth;
	*h=texHeight;
}
void OpenGL::ReshapeTex(int n,int m){
	if (n!=texWidth||m!=texHeight){
		texWidth=n;
		texHeight=m;
		if (tex4CL!=0){
			glDeleteTextures(1,&tex4CL);
		}
		tex4CL=GenGLTex(texWidth,texHeight,0);
		if (tex4GL!=0){
			glDeleteTextures(1,&tex4GL);
		}
		tex4GL=GenGLTex(texWidth,texHeight,0);
	}
}
int OpenGL::IsGLExtensionSupported(const char *extension){
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '/0')
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	start = extensions;
	for (;;) {
		where = ( GLubyte* ) strstr( (const char *) start, extension );
		if ( !where ) 
			break;
		terminator = where + strlen(extension);
		if ( (where == start || *(where - 1) == ' ') && (*terminator == ' ' || *terminator == '/0') )
			return 1;
		start = terminator;
	}
	return 0;
}
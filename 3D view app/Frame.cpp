#include "StdAfx.h"
#include "Frame.h"


Frame::Frame(void)
{
}


Frame::~Frame(void)
{
}

bool Frame::Init( HDC hDC, int width, int height )
{
	GLuint		PixelFormat;	
	HGLRC hRC;
	m_hDC = hDC;

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,						// Must Support Double Buffering
		PFD_TYPE_RGBA,							// Request An RGBA Format
		32,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,						// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		32,								// 32Bit Z-Buffer (Depth Buffer)
		1,								// Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,							// Main Drawing Layer
		0,								// Reserved
		0, 0, 0								// Layer Masks Ignored
	};
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Did Windows Find A Matching Pixel Format?
	{		
		MessageBoxW(NULL,L"Can't Find A Suitable PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))				// Are We Able To Set The Pixel Format?
	{		
		MessageBoxW(NULL,L"Can't Set The PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{		

		MessageBoxW(NULL,L"Can't Create A GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}
	m_hRC = hRC;
	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{		
		MessageBoxW(NULL,L"Can't Activate The GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	ReSizeGLScene(width, height);
	if (!InitGLColor())								// Initialize Our Newly Created GL Window	
	{			
		MessageBoxW(NULL,L"Initialization Failed.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;							// Return FALSE
	}
	return true;	
}

GLvoid Frame::ReSizeGLScene( GLsizei width, GLsizei height )
{
	if(height == 0)
	{
		height=1;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool Frame::InitGLColor( GLvoid )
{
	GLfloat light_ambient[] =  {0.01, 0.01, 0.01, 1.0};
	GLfloat light_diffuse[] =  {0.7, 0.7, 0.7, 1.0};
	GLfloat light_specular[] =  {0.0, 0.0, 0.0, 1.0};
	GLfloat light_position[] =  {1.0, 1.0, 1.0, 0.0};	
	GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat mat_shininess = 40.0;

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	GLfloat ambient[] = {0.2, 0.2, 0.2, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	//glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_NORMALIZE);

	glEnable(GL_POINT_SMOOTH);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); 
	return true;
}

bool Frame::DrawGLScene( GLvoid )
{
	wglMakeCurrent(m_hDC,m_hRC);

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();	
	glTranslatef(0,0,100.0f);

	// draw polygon
	float ambient[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
	float diffuse[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float specular[4] ={ 0.774597f, 0.774597f, 0.774597f, 1.0f };
	float shininess = 76.8f;

	//glDisable(GL_COLOR_MATERIAL);	
	glEnable(GL_COLOR_MATERIAL);	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColor3d(238.0/255.0, 230.0/255.0, 196.0/255.0);
	glPushMatrix();
	m_stl.render_mesh_flat();
	//m_stl.render_point();
	glPopMatrix();	
	//
	SwapBuffers(m_hDC);	

	return TRUE;
}

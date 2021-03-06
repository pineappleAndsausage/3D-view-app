#include "StdAfx.h"
#include "Frame.h"


Frame::Frame(void) : m_fov(45.0f), m_shading(false)
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
	m_height = height;
	m_width = width;
	if(height == 0)
	{
		height=1;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(m_fov, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
GLvoid Frame::set_fov(float f)
{
	m_fov += f;
	
	glViewport(0, 0, m_width, m_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(m_fov, (GLfloat)m_width/(GLfloat)m_height, 0.1f, 100.0f);	
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
	glTranslatef(0,0,-10.0f);
	m_camera.transform();
	
	
	
	// draw polygon
	glEnable(GL_LIGHTING);
	float ambient[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
	float diffuse[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float specular[4] ={ 0.774597f, 0.774597f, 0.774597f, 1.0f };
	float shininess = 76.8f;	
	glEnable(GL_COLOR_MATERIAL);	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColor3d(238.0/255.0, 230.0/255.0, 196.0/255.0);
	glPushMatrix();
	
	m_mesh.render_mesh(m_shading);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	m_mesh.render_highlight_point();

	glPopMatrix();	
	
	SwapBuffers(m_hDC);	

	return TRUE;
}

Frame* Frame::GetInstance()
{
	static Frame k;
	return &k;
}


void Frame::select(int mouse_x, int mouse_y)
{
	
	GLuint	buffer[512];
	GLint	hits;
	GLint   viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);

	mouse_y = (viewport[3]-mouse_y);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0); 
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((GLdouble) mouse_x, (GLdouble) mouse_y, 1.0f, 1.0f, viewport);

	gluPerspective(m_fov, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	DrawGLScene();
	glMatrixMode(GL_PROJECTION);   
	glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW);
	hits=glRenderMode(GL_RENDER);

	if (hits > 0) 
	{
		int choose = buffer[3];
		int depth = buffer[1];
		for (int loop = 1; loop < hits; loop++)         
		{			
			if (buffer[loop*4+1] < GLuint(depth))
			{
				choose = buffer[loop*4+3];        
				depth = buffer[loop*4+1];         
			}       
		}

		// ray 구해서 가장 가까운점 찾음.
		GLdouble modelViewMatrix[16];
		GLdouble projectionMatrix[16];
		int viewport[4];

		glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
		glGetIntegerv(GL_VIEWPORT, viewport);

		GLdouble nearPlaneLocation[3];
		gluUnProject(mouse_x, mouse_y, 0.0, modelViewMatrix, projectionMatrix,
			viewport, &nearPlaneLocation[0], &nearPlaneLocation[1], 
			&nearPlaneLocation[2]);

		GLdouble farPlaneLocation[3];
		gluUnProject(mouse_x, mouse_y, 1.0, modelViewMatrix, projectionMatrix,
			viewport, &farPlaneLocation[0], &farPlaneLocation[1],
			&farPlaneLocation[2]);

		Vector3F ray;
		Vector3F pos;
		for(int i = 0; i < 3; i++)
		{
			ray[i] = farPlaneLocation[i] - nearPlaneLocation[i];
			pos[i] = nearPlaneLocation[i];
		}		
		m_mesh.select_vertex(choose,pos,ray);
	}
}


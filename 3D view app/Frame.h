#pragma once
#include "GL/glut.h"

class Frame
{
public:
	Frame(void);
	~Frame(void);

	HDC m_hDC;
	HGLRC m_hRC;
	bool Init(HDC hDC, int width, int height);
	bool InitGLColor(GLvoid);	
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	bool DrawGLScene(GLvoid);
};


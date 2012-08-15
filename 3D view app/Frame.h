#pragma once
#include "GL/glut.h"
#include "STL.h"
class Frame
{
protected:
	
public:
	Frame(void);
	~Frame(void);
	STL m_stl;
	HDC m_hDC;
	HGLRC m_hRC;
	bool Init(HDC hDC, int width, int height);
	bool InitGLColor(GLvoid);	
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	bool DrawGLScene(GLvoid);
};


#pragma once
#include "GL/glut.h"
#include "STL.h"
#include "Camera.h"
class Frame
{
protected:
	
public:
	Frame(void);
	~Frame(void);
	int m_width, m_height;
	Camera m_camera;
	float m_fov;
	STL m_stl;
	HDC m_hDC;
	HGLRC m_hRC;
	bool Init(HDC hDC, int width, int height);
	bool InitGLColor(GLvoid);	
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	bool DrawGLScene(GLvoid);
	GLvoid set_fov(float f);
};


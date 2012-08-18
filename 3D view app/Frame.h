#pragma once
#include "GL/glut.h"
#include "STL.h"
#include "Camera.h"
class Frame
{
protected:
	
public:
	static Frame* GetInstance();

	Frame(void);
	~Frame(void);
	int m_width, m_height;
	Camera m_camera;
	float m_fov;
	STL m_stl;
	HDC m_hDC;
	HGLRC m_hRC;
	int m_shading;
	Vector3F click_point;
	bool Init(HDC hDC, int width, int height);
	bool InitGLColor(GLvoid);	
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	bool DrawGLScene(GLvoid);
	GLvoid set_fov(float f);
	void select(int mouse_x, int mouse_y);
};


#pragma once
#include "Vector3F.h"
#include "GL\glut.h"
#include <vector>
class Camera
{
protected:
	std::vector<float> rotateQ;	
	std::vector<float> matrix;	

public:
	Camera();
	~Camera(void);
		
	void transform();	
	void panning(int x, int y);	
	void rotate(int x, int y, int x2, int y2);	
protected:
	std::vector<float> quaternion_rotation_axis_angle( const Vector3F& axis, float angle);	
	std::vector<float> quaternion_multiplication(const std::vector<float>& q1, const std::vector<float>& q2);	
	void quaternion_normalize(std::vector<float>& q);	
	std::vector<float> quaternion_to_matrix(const std::vector<float> &q);
	
};


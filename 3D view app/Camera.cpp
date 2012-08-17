#include "StdAfx.h"
#include "Camera.h"

Camera::~Camera(void)
{
}

Camera::Camera()
{		
	rotateQ.resize(4);
	rotateQ[0] = 1; rotateQ[1] = 0; rotateQ[2] = 0; rotateQ[3] =0;		
	matrix = quaternion_to_matrix(rotateQ);
}
void Camera::transform()
{		
	glMultMatrixf(matrix.data());
}
void Camera::panning(int x, int y)
{
	std::vector<float> rotateInvQ = rotateQ;
	for(int i = 0; i < 3; i++)
		rotateInvQ[i+1] = -rotateQ[i+1];

	float scale = 100.0f;		
	std::vector<float> t(4);
	t[0] =0; t[1] = x/scale; t[2] = y/scale; t[3] = 0;			
	for(int i = 0; i < 3; i++)
	{
		matrix[12+i] += t[i+1];			
	}
}
void Camera::rotate(int x, int y, int x2, int y2)
{
	if(x == x2 && y == y2)
		return;
	Vector3F v1,v2;
	float scale = 100.0f;
	v1[0] = x/scale; v1[1] = y2/scale; v1[2] = 10;
	v2[0] = x2/scale; v2[1] = y/scale; v2[2] = 10;
				
	Vector3F axis = v1 % v2;	
	v1 = v1.normalize();
	v2 = v2.normalize();
	float angle = acos(v1 * v2);
	std::vector<float> q = quaternion_rotation_axis_angle(axis,angle);		
	rotateQ = quaternion_multiplication(q,rotateQ);		
	quaternion_normalize(rotateQ);
	std::vector<float> m = quaternion_to_matrix(rotateQ);
	for(int i = 0; i < 3; i++)		
		for(int j = 0; j < 3;j++)			
			matrix[j+i*4] = m[j+i*4];

	//translation
	std::vector<float> InvQ = q;
	for(int i = 0; i < 3; i++)
	InvQ[i+1] = -q[i+1];
	std::vector<float> t(4);
	t[0] = 0; t[1] = matrix[12]; t[2] = matrix[13]; t[3] = matrix[14];
	t = quaternion_multiplication(t,InvQ);
	t = quaternion_multiplication(q,t);		
	for(int i = 0; i < 3; i++)		
		matrix[12+i] = t[1+i];
		
}

std::vector<float> Camera::quaternion_rotation_axis_angle( const Vector3F& axis, float angle)
{	
	std::vector<float> q(4);
	angle *= .5;        
	q[0] = std::cos(angle);
	float s = std::sin(angle);
	q[1] = axis[0] * s;
	q[2] = axis[1] * s;
	q[3] = axis[2] * s;		
	float z = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
	q[0]/=z; q[1]/=z; q[2]/=z; q[3]/=z;
	return q;
}
std::vector<float> Camera::quaternion_multiplication(const std::vector<float>& q1, const std::vector<float>& q2)
{
	std::vector<float> q(4);
	Vector3F v1(q1[1],q1[2],q1[3]);
	Vector3F v2(q2[1],q2[2],q2[3]);
	float w = q1[0]*q2[0] - v1*v2;
	Vector3F v = (q1[0]*v2) + (q2[0]*v1) + (v1%v2);		
	q[0] = w; q[1] = v[0]; q[2] = v[1]; q[3] = v[2];
	return q;
}
void Camera::quaternion_normalize(std::vector<float>& q)
{		
	float z = .0f;
	for(int i = 0; i < 4; i++)
	{
		z += q[i] * q[i];
	}
	z = sqrt(z);
	q[0]/=z; q[1]/=z; q[2]/=z; q[3]/=z;
}
std::vector<float> Camera::quaternion_to_matrix(const std::vector<float> &q)
{
	std::vector<float> mat(16);
	/*mat[0] = q[0]*q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
	mat[1] = 2*(q[1]*q[2] - q[0]*q[3]);
	mat[2] = 2*(q[1]*q[3] + q[0]*q[2]);
	mat[3] = 0;
	mat[4] = 2*(q[1]*q[2] + q[0]*q[3]);		
	mat[5] = q[0]*q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
	mat[6] = 2*(q[2]*q[3] - q[0]*q[1]);
	mat[7] = 0;
	mat[8] = 2*(q[1]*q[3] - q[0]*q[2]);
	mat[9] = 2*(q[2]*q[3] + q[0]*q[1]);
	mat[10] = q[0]*q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];*/
	mat[0] = q[0]*q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
	mat[1] = 2*(q[1]*q[2] + q[0]*q[3]);		
	mat[2] = 2*(q[1]*q[3] - q[0]*q[2]);
	mat[3] = 0;
	mat[4] = 2*(q[1]*q[2] - q[0]*q[3]);
	mat[5] = q[0]*q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
	mat[6] = 2*(q[2]*q[3] + q[0]*q[1]);
	mat[7] = 0;
	mat[8] = 2*(q[1]*q[3] + q[0]*q[2]);
	mat[9] = 2*(q[2]*q[3] - q[0]*q[1]);
	mat[10] = q[0]*q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];		
	mat[11] = 0;
	mat[12] = 0; mat[13] = 0; mat[14] = 0; mat[15] = 1;		
	return mat;
}
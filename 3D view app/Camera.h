#pragma once
#include "Vector3F.h"
#include "GL\glut.h"
#include <vector>
class Camera
{
public:
	
	~Camera(void);

	std::vector<float> rotateQ;
	float mat[16];
		
	Camera()
	{
		rotateQ.resize(4);
		rotateQ[0] = 1; rotateQ[1] = 0; rotateQ[2] = 0; rotateQ[3] =0;
		
		quaternion_to_matrix(rotateQ);
	}
	void transform()
	{		
		glMultMatrixf(mat);
	}

	void rotate(int x, int y, int x2, int y2)
	{
		if(x == x2 && y == y2)
			return;
		Vector3F v1,v2;
		float scale = 100.0f;
		v1[0] = x/scale; v1[1] = y/scale; v1[2] = 10;
		v2[0] = x2/scale; v2[1] = y2/scale; v2[2] = 10;
				
		Vector3F axis = v1 % v2;	
		v1 = v1.normalize();
		v2 = v2.normalize();
		float angle = acos(v1 * v2);
		std::vector<float> q = quaternion_rotation_axis_angle(axis,angle);
		rotateQ = quaternion_multiplication(rotateQ,q);
		quaternion_to_matrix(rotateQ);
	}
	void matrix_rotation_axis_angle(std::vector<float>& m, const Vector3F& axis, float angle)
	{		
		float s = std::sin(angle);
		float c = std::cos(angle);
		float omc = float(1) - c;

		float xomc = axis[0] * omc;
		float yomc = axis[1] * omc;
		float zomc = axis[2] * omc;

		float xxomc = axis[0] * xomc;
		float yyomc = axis[1] * yomc;
		float zzomc = axis[2] * zomc;
		float xyomc = axis[0] * yomc;
		float yzomc = axis[1] * zomc;
		float zxomc = axis[2] * xomc;

		float xs = axis[0] * s;
		float ys = axis[1] * s;
		float zs = axis[2] * s;

		//m.set_basis_element(0,0, xxomc + c );
		//m.set_basis_element(0,1, xyomc + zs);
		//m.set_basis_element(0,2, zxomc - ys);
		//m.set_basis_element(1,0, xyomc - zs);
		//m.set_basis_element(1,1, yyomc + c );
		//m.set_basis_element(1,2, yzomc + xs);
		//m.set_basis_element(2,0, zxomc + ys);
		//m.set_basis_element(2,1, yzomc - xs);
		//m.set_basis_element(2,2, zzomc + c );
	}
	std::vector<float> quaternion_rotation_axis_angle( const Vector3F& axis, float angle)
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
	std::vector<float> quaternion_multiplication(const std::vector<float>& q1, const std::vector<float>& q2)
	{
		std::vector<float> q(4);
		Vector3F v1(q1[1],q1[2],q1[3]);
		Vector3F v2(q2[1],q2[2],q2[3]);
		float w = q1[0]*q2[0] - v1*v2;
		Vector3F v = (q1[0]*v2) + (q2[0]*v1) + (v1%v2);
		float z = sqrt(w*w + v.magnitude());
		q[0] = w/z; q[1] = v[0]/z; q[2] = v[1]/z; q[3] = v[2]/z;
		return q;
	}
	void quaternion_to_matrix(const std::vector<float> &q)
	{
		//float mat[16];
		mat[0] = q[0]*q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
		mat[1] = 2*(q[1]*q[2] - q[0]*q[3]);
		mat[2] = 2*(q[1]*q[3] + q[0]*q[2]);
		mat[3] = 0;
		mat[4] = 2*(q[1]*q[2] + q[0]*q[3]);		
		mat[5] = q[0]*q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
		mat[6] = 2*(q[2]*q[3] - q[0]*q[1]);
		mat[7] = 0;
		mat[8] = 2*(q[1]*q[3] - q[0]*q[2]);
		mat[9] = 2*(q[2]*q[3] + q[0]*q[1]);
		mat[10] = q[0]*q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];
		/*mat[0] = q[0]*q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
		mat[1] = 2*(q[1]*q[2] + q[0]*q[3]);		
		mat[2] = 2*(q[1]*q[3] - q[0]*q[2]);
		mat[3] = 0;
		mat[4] = 2*(q[1]*q[2] - q[0]*q[3]);
		mat[5] = q[0]*q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
		mat[6] = 2*(q[2]*q[3] + q[0]*q[1]);
		mat[7] = 0;
		mat[8] = 2*(q[1]*q[3] + q[0]*q[2]);
		mat[9] = 2*(q[2]*q[3] - q[0]*q[1]);
		mat[10] = q[0]*q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];		*/
		mat[11] = 0;
		mat[12] = 0; mat[13] = 0; mat[14] = 0; mat[15] = 1;
		//transf = mat;
		//return mat;
	}
};


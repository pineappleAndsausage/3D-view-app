#include "StdAfx.h"
#include "Vector3F.h"

const bool operator== (const Vector3F &lhs, const Vector3F &rhs)
{
	static float e = 10e-6f;
	for(int i = 0; i < 3; i++)
	{
		if(lhs[i] - rhs[i] > e || rhs[i] - lhs[i] > e )
			return false;
	}
	return true;
}

const Vector3F operator* (float s, const Vector3F &v)
{
	return Vector3F(v[0]*s,v[1]*s,v[2]*s);
}
const Vector3F operator* (const Vector3F &v, float s)
{
	return Vector3F(v[0]*s,v[1]*s,v[2]*s);
}
const Vector3F operator/ (const Vector3F &v, float s)
{
	return Vector3F(v[0]/s,v[1]/s,v[2]/s);
}
const Vector3F operator+ (const Vector3F &v, float s)
{
	return Vector3F(v[0]+s,v[1]+s,v[2]+s);
}

const Vector3F operator+ (const Vector3F &v, const Vector3F &v1)
{
	return Vector3F(v[0]+v1[0],v[1]+v1[1],v[2]+v1[2]);
}
const Vector3F operator- (const Vector3F &v, float s)
{
	return Vector3F(v[0]-s,v[1]-s,v[2]-s);
}

const Vector3F operator- (const Vector3F &v, const Vector3F &v1)
{
	return Vector3F(v[0]-v1[0],v[1]-v1[1],v[2]-v1[2]);
}

const float operator* (const Vector3F &v, const Vector3F &v2)
{
	return (v[0]*v2[0]+v[1]*v2[1]+v[2]*v2[2]);
}

const Vector3F operator% (const Vector3F &v, const Vector3F &v2)
{
	Vector3F temp;
	temp[0] = v[1]*v2[2] - v[2]*v2[1];
	temp[1] = v[2]*v2[0] - v[0]*v2[2];
	temp[2] = v[0]*v2[1] - v[1]*v2[0];
	return temp;
}
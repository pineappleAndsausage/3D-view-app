#pragma once
#include <cassert>
#include <math.h>
class Vector3F
{
protected:
	float elems[3];
public:
	inline Vector3F(void)
	{
		for(int i = 0; i < 3; i++)
			elems[i] = .0f;
	}
	inline Vector3F(float x,float y, float z)
	{
		elems[0] = x; elems[1] = y; elems[2] = z;
	}
	inline float operator[] (int i) const {	assert(i >= 0); assert( i < 3);	return elems[i];}
	inline float & operator[] (int i) {	assert(i >= 0); assert( i < 3);	return elems[i];}	
	inline const Vector3F operator-() const { return Vector3F(-elems[0],-elems[1],-elems[2]);};

	inline Vector3F & operator+= (float factor)
	{
		for(int i = 0; i < 3; i++)
			elems[i] += factor;
		return *this;
	}
	inline Vector3F & operator-= (float factor)
	{
		for(int i = 0; i < 3; i++)
			elems[i] -= factor;
		return *this;
	}
	inline Vector3F & operator+= (Vector3F factor)
	{
		for(int i = 0; i < 3; i++)
			elems[i] += factor[i];
		return *this;
	}
	inline Vector3F & operator-= (Vector3F factor)
	{
		for(int i = 0; i < 3; i++)
			elems[i] -= factor[i];
		return *this;
	}
	inline Vector3F & operator*= (float factor)
	{
		for(int i = 0; i < 3; i++)
			elems[i] *= factor;
		return *this;
	}
	inline Vector3F & operator/= (float factor)
	{
		for(int i = 0; i < 3; i++)
			elems[i] /= factor;
		return *this;
	}

	friend const bool operator== (const Vector3F &lhs, const Vector3F &rhs);
	friend const Vector3F operator* (float s, const Vector3F &v);
	friend const Vector3F operator* (const Vector3F &v, float s);
	friend const float operator* (const Vector3F &v, const Vector3F &v2);
	friend const Vector3F operator% (const Vector3F &v, const Vector3F &v2);
	friend const Vector3F operator/ (const Vector3F &v, float s);
	friend const Vector3F operator+ (const Vector3F &v, float s);
	friend const Vector3F operator+ (const Vector3F &v, const Vector3F &v2);
	friend const Vector3F operator- (const Vector3F &v, const Vector3F &v2);
	friend const Vector3F operator- (const Vector3F &v, float s);

	float* data() { return &elems[0]; }
	inline float magnitude_squared() 
	{
		return sqrtf(*this * *this);
	}
	inline float magnitude() 
	{
		return *this * *this;
	}
	inline  const Vector3F normalize() 
	{
		float t = this->magnitude_squared();
		return Vector3F(elems[0]/t,elems[1]/t,elems[2]/t);
	}
};
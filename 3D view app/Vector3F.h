#pragma once
#include <cassert>

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

	inline float operator[] (int i) const {	assert(i >= 0); assert( i < 3);	return elems[i];}
	inline float & operator[] (int i) {	assert(i >= 0); assert( i < 3);	return elems[i];}	
	friend const bool operator== (const Vector3F &lhs, const Vector3F &rhs);

	float* data() { return &elems[0]; }

};
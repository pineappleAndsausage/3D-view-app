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
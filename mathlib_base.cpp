#include "stdafx.h"
#include <math.h>
#include <float.h>
#include "math_pfns.h"
#include "Vector.h"
#include "mathlib.h"

// Standard C implementations of optimized routines:
//-----------------------------------------------------------------------------
float _sqrtf(float _X)
{
	return sqrtf(_X);
}

float _rsqrtf(float x)
{
	return 1.f / _sqrtf(x);
}

float __fastcall _VectorNormalize(Vector& vec)
{
	float radius = sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (radius + FLT_EPSILON);

	vec.x *= iradius;
	vec.y *= iradius;
	vec.z *= iradius;

	return radius;
}

// TODO: Add fast C VectorNormalizeFast.
// Perhaps use approximate rsqrt trick, if the accuracy isn't too bad.
void __fastcall _VectorNormalizeFast(Vector& vec)
{
	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z) + FLT_EPSILON);

	vec.x *= iradius;
	vec.y *= iradius;
	vec.z *= iradius;

}

float _InvRSquared(const float* v)
{
	Assert(s_bMathlibInitialized);
	float	r2 = DotProduct(v, v);
	return r2 < 1.f ? 1.f : 1 / r2;
}

//-----------------------------------------------------------------------------
// Function pointers selecting the appropriate implementation
//-----------------------------------------------------------------------------
float(*pfSqrt)(float x) = _sqrtf;
float(*pfRSqrt)(float x) = _rsqrtf;
float(*pfRSqrtFast)(float x) = _rsqrtf;
float (__fastcall *pfVectorNormalize)(Vector& v) = _VectorNormalize;
void  (__fastcall *pfVectorNormalizeFast)(Vector& v) = _VectorNormalizeFast;
float(*pfInvRSquared)(const float* v) = _InvRSquared;
float(*pfFastCos)(float x) = cosf;
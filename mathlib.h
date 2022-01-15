#pragma once
#include "basetypes.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

#define	IS_NAN(x) (((*(int *)&x)&nanmask)==nanmask)

inline vec_t DotProduct(const vec_t *v1, const vec_t *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
inline void VectorSubtract(const vec_t *a, const vec_t *b, vec_t *c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}
inline void VectorAdd(const vec_t *a, const vec_t *b, vec_t *c)
{
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}
inline void VectorCopy(const vec_t *a, vec_t *b)
{
	b[0] = a[0];
	b[1] = a[1];
	b[2] = a[2];
}

inline void VectorClear(vec_t *a)
{
	a[0] = a[1] = a[2] = 0;
}

inline void VectorScale(const float* in, vec_t scale, float* out)
{
	out[0] = in[0] * scale;
	out[1] = in[1] * scale;
	out[2] = in[2] * scale;
}

// Cannot be forceinline as they have overloads:
inline void VectorFill(vec_t *a, float b)
{
	a[0] = a[1] = a[2] = b;
}

inline void VectorNegate(vec_t *a)
{
	a[0] = -a[0];
	a[1] = -a[1];
	a[2] = -a[2];
}

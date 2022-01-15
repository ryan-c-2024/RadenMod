#pragma once

extern float(*pfSqrt)(float x);
extern float(*pfRSqrt)(float x);
extern float(*pfRSqrtFast)(float x);
extern void(*pfFastSinCos)(float x, float *s, float *c);
extern float(*pfFastCos)(float x);

// The following are not declared as macros because they are often used in limiting situations,
// and sometimes the compiler simply refuses to inline them for some reason
#define FastSqrt(x)			(*pfSqrt)(x)
#define	FastRSqrt(x)		(*pfRSqrt)(x)
#define FastRSqrtFast(x)    (*pfRSqrtFast)(x)
#define FastSinCos(x,s,c)   (*pfFastSinCos)(x,s,c)
#define FastCos(x)			(*pfFastCos)(x)

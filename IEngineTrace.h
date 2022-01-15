#pragma once
#include "Util.h"

class CGameTrace;
typedef CGameTrace trace_t;
struct Ray_t;
class ITraceFilter;

class IEngineTrace
{
public:
	// A version that simply accepts a ray (can work as a traceline or tracehull)
	inline void	TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void(__thiscall* tFunc) (void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		Util::CallVirtualFunction<tFunc>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
};
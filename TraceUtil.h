#pragma once

class CBasePlayer;
class Vector;

namespace TraceUtil
{
	//void TraceLine(Vector& vecRayOrigin, Vector& vecRayEnd, ITraceFilter* pFilter, trace_t* pTrace);

	//pass the entity you are aiming at for pSkip2
	bool IsVisible(Vector& vecRayOrigin, Vector& vecRayEnd, CBasePlayer* pSkip2); 
	//Ease of use wrapper for IsVisible when testing if target player's bone is visible
	bool BoneVisibleFromLocalPlayer(CBasePlayer* targetEnt, int boneNum);
}

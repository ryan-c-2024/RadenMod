#include "stdafx.h"
#include "TraceUtil.h"
#include "Raytrace.h"
#include "Global Interfaces.h"
#include "CBasePlayer.h"
#include "Options.h"

bool TraceUtil::IsVisible(Vector& vecRayOrigin, Vector& vecRayEnd, CBasePlayer* pSkip2) 
{
	Ray_t ray;
	ray.Init(vecRayOrigin, vecRayEnd);
	trace_t trace;
	CTraceFilterPlus filter;
	filter.SetSkipEntity(GPtr::pLocalPlayer, pSkip2);
	IFace::enginetrace->TraceRay(ray, MASK_CANSHOOT, &filter, &trace);

	//elite ghetto autowall jebhook state of the art technology
	// 100 -> 0.1
	if (trace.fraction >= 0.97f || (Options::Aimbot::bGhettoAutowall && trace.fraction >= Options::Aimbot::flGhettoAutowallModifier / 100))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TraceUtil::BoneVisibleFromLocalPlayer(CBasePlayer* targetEnt, int boneNum)
{
	if (!GPtr::pLocalPlayer || !targetEnt)
		return false;

	return IsVisible(GPtr::pLocalPlayer->GetCurrentEyePosition(), targetEnt->GetBonePosition(boneNum), targetEnt);
}


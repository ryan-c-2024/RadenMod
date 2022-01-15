#include "stdafx.h"
#include "CGoombaStomp.h"
#include "Options.h"
#include "Global Interfaces.h"
#include "CUserCmd.h"
#include "CAimbot.h"
#include "CBasePlayer.h"

void CGoombaStomp::Run()
{
	if (!Options::GoombaStomp::bEnabled)
		return;
	if (GMisc::aimbot.m_bIsTargeting)
		return;

	if (!(GetAsyncKeyState(VK_PRIOR) & 0x8000)) //if page up is is down
		return;

	FindTarget();

}

void CGoombaStomp::FindTarget()
{
	m_flBestDist = 7000.0; //minimum distance required
	m_pTargetEntity = nullptr;

	for (int i = 1; i < IFace::engineclient->GetMaxClients(); i++) //cycle through, check if valid, then compare distance with minimum
	{
		CBasePlayer* pEntity = IFace::entitylist->GetClientEntity(i);
		if (!pEntity || pEntity->IsDormant() || pEntity->IsLocalPlayer() || !pEntity->IsOnLocalPlayerTeam())
			continue;

		m_vecTargetPos = pEntity->GetOrigin();
		m_vecPlayerPos = GPtr::pLocalPlayer->GetOrigin();

		float flDistanceSquared = m_vecTargetPos.DistToSqr(m_vecPlayerPos);

	//	if (flDistanceSquared > 7000.0)
	//		return;

		if (flDistanceSquared < m_flBestDist)
		{
			m_flBestDist = flDistanceSquared; //met the requirements, bestdist to new distance so the closest entity can be found
			m_pTargetEntity = pEntity;
		}
	
	}
	if (m_pTargetEntity)
	{
		TrackTarget(); // if target is found, track
	}
}

void CGoombaStomp::TrackTarget()
{
	m_vecTargetPos = m_pTargetEntity->GetOrigin();

	Vector vecDelta;
	VectorSubtract(m_vecTargetPos, m_vecPlayerPos, vecDelta);
	vecDelta.Rescale(449.99f); //rescale position vector to the max cmd->___move speed
	
	QAngle angGoombaStomp;
	IFace::engineclient->GetViewAngles(angGoombaStomp);
	m_flYawDeltaStep = (90.0 - angGoombaStomp.y) / 10; //smooth adjustment of viewangles to 90
	angGoombaStomp.y += m_flYawDeltaStep; //big smooth stepping

	angGoombaStomp.ClampAndNormalizeAngles(); //clamp and normalize (setviewangle normalizes for you iirc but whatever)

	//GPtr::cmd->viewangles = angGoombaStomp;
	IFace::engineclient->SetViewAngles(angGoombaStomp); //set the angles for consistent movement

	GPtr::cmd->forwardmove = vecDelta.y; //move to track target
	GPtr::cmd->sidemove = vecDelta.x; //move to track target
	GPtr::cmd->ClampMovement();
}

CGoombaStomp GMisc::goombastomp;
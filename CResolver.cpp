#include "stdafx.h"
#include "CResolver.h"
#include "CBasePlayer.h"
#include "Global Interfaces.h"
#include "Options.h"
#include "Vector.h"

/*

TODO: IMPROVE LBY RESOLVER

(CHECK FOR VIEWANGLE CHANGES AND FIRING FOR LBY UPDATE)

*/


CResolver GMisc::resolver;

void CResolver::Run()
{
	try
	{
		if (!IFace::engineclient->IsInGame())
			return;
		for (int i = 0, iMaxClients = IFace::engineclient->GetMaxClients(); i < iMaxClients; i++)
		{
			CBasePlayer* ent = IFace::entitylist->GetClientEntity(i);
			if (!ent || ent->IsDormant() || !GPtr::pLocalPlayer || ent->IsLocalPlayer())
				continue;
			if (ent->IsOnLocalPlayerTeam())
				continue;

			ResolvePitch(ent);
			ResolveYaw(ent);
		}
	}
	catch (const std::exception& exc)
	{
		if (IFace::engineclient)
		{
			//IFace::engineclient->Con_NPrintf(1, "ISSUE IN RESOLVER: %s", exc.what());
		}
	}

}
void CResolver::ResolvePitch(CBasePlayer* entity)
{
	if (!Options::Resolver::bEnabled)
		return;

}
void CResolver::ResolveYaw(CBasePlayer* entity)
{
	if (!Options::Resolver::bEnabled)
		return;
	if (DidLowerBodyYawUpdate(entity))
	{
		entity->ForceYawAngle(entity->GetLowerBodyYaw());
	}
}
bool CResolver::DidLowerBodyYawUpdate(CBasePlayer* entity)
{
	//static float previousYaw = 0;
	if (entity->GetVelocity().Length2D() > 2.5)
	{
		if (m_BodyAimTargets.find(entity) != m_BodyAimTargets.end())
		{
			m_BodyAimTargets.erase(entity);
		} 
		return true;
	}
	else
	{
		if (Options::Resolver::bBodyAimUnresolvable)
		{
			m_BodyAimTargets.insert(entity);
		}
		else if (m_BodyAimTargets.size() >= 1)
		{
			m_BodyAimTargets.clear();
		}
		return false;
	}
}
bool CResolver::ShouldBodyAim(CBasePlayer* entity)
{
	if (!Options::Resolver::bBodyAimUnresolvable)
		return false;
	if (m_BodyAimTargets.find(entity) != m_BodyAimTargets.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
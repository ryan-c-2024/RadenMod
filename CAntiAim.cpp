#include "stdafx.h"
#include "CAntiAim.h"
#include "CUserCmd.h"
#include "Global Interfaces.h"
#include "Vector.h"
#include "Options.h"
#include "Math.h"
#include "CAimbot.h"
#include <random>
#include "CBaseCombatWeapon.h"
#include "WeaponID.h"
#include "CBunnyhop.h"
#include "CBasePlayer.h"
#include "mathlib.h"

CAntiAim GMisc::antiaim;

void CAntiAim::Run()
{
	if (!Options::AntiAim::bEnabled)
		return;
	if (GPtr::cmd->buttons & IN_ATTACK || GPtr::cmd->buttons & IN_USE || HasGrenadeOut())
		return;
	if (GMisc::aimbot.m_bAimstepping)
		return;
	if (GPtr::pLocalPlayer->GetMoveType() == MOVETYPE_LADDER || GPtr::pLocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;
	PreFixMovement();
	m_shouldFake = !m_shouldFake;

	if (Options::AntiAim::bEnabled)
	{
		DoPitchAntiAim();
		DoYawAntiAim();
	}

	GPtr::cmd->viewangles.ClampAndNormalizeAngles();
	FixMovement();

	if (Options::AntiAim::bShowAngles)
	{
		IFace::engineclient->SetViewAngles(GPtr::cmd->viewangles);
	}
}

void CAntiAim::PreFixMovement()
{
	m_forwardmove = GPtr::cmd->forwardmove;
	m_sidemove = GPtr::cmd->sidemove;
	m_upmove = GPtr::cmd->upmove;
	m_oldYaw = GPtr::cmd->viewangles.y;
}

void CAntiAim::FixMovement()
{
	float deltaView = GPtr::cmd->viewangles.y - m_oldYaw;
	float f1;
	float f2;
	if (m_oldYaw < 0.f)
		f1 = 360.0f + m_oldYaw;
	else
		f1 = m_oldYaw;
	if (GPtr::cmd->viewangles.y < 0.0f)
		f2 = 360.0f + GPtr::cmd->viewangles.y;
	else
		f2 = GPtr::cmd->viewangles.y;
	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);
	deltaView = 360.0f - deltaView;
	GPtr::cmd->forwardmove = cos(DEG2RAD(deltaView)) * m_forwardmove + cos(DEG2RAD(deltaView + 90.f)) * m_sidemove;
	GPtr::cmd->sidemove = sin(DEG2RAD(deltaView)) * m_forwardmove + sin(DEG2RAD(deltaView + 90.f)) * m_sidemove;
	GPtr::cmd->ClampMovement();
}

void CAntiAim::DoPitchAntiAim()
{
	switch (Options::AntiAim::iPitchAntiAimMode)
	{
	case Options::AntiAim::Pitch::Down:
		GPtr::cmd->viewangles.x = 88.9;
		break;
	case Options::AntiAim::Pitch::Up:
		GPtr::cmd->viewangles.x = -88.9;
		break;
	case Options::AntiAim::Pitch::Forward:
		break;
	}
}

void CAntiAim::DoYawAntiAim()
{
	switch (Options::AntiAim::iYawAntiAimMode)
	{
	case Options::AntiAim::Yaw::BackStatic:
		GPtr::cmd->viewangles.y -= 180;
		break;
	case Options::AntiAim::Yaw::BackJitter:
		GPtr::cmd->viewangles.y -= 180;
		AddJitter(23);
		break;
	case Options::AntiAim::Yaw::ForwardStatic:
		break;
	case Options::AntiAim::Yaw::ForwardJitter:
		AddJitter(23);
		break;
	case Options::AntiAim::Yaw::Spin:
		static float prevYaw = GPtr::cmd->viewangles.y;
		prevYaw += 8;
		GPtr::cmd->viewangles.y = prevYaw;
		prevYaw = GPtr::cmd->viewangles.y;
		break;
	case Options::AntiAim::Yaw::Left:
		GPtr::cmd->viewangles.y += 90;
		break;
	case Options::AntiAim::Yaw::Right:
		GPtr::cmd->viewangles.y -= 90;
		break;
	case Options::AntiAim::Yaw::Fukkireta:
		static bool bSwitchSide = false;
		GPtr::cmd->viewangles.y += (bSwitchSide) ? -90 : 90;
		AddJitter(45);
		bSwitchSide = !bSwitchSide;
		break;
	}
}

void CAntiAim::AddJitter(int maxDifference)
{
	srand(IFace::inputsystem->GetPollTick());
	GPtr::cmd->viewangles.y += (rand() % abs(maxDifference * 2)) - maxDifference;
}

bool CAntiAim::HasGrenadeOut()
{
	int weapID = GPtr::pLocalWep->GetWeaponID();

	if (
		weapID == WeaponID::Weapon_Decoy || weapID == WeaponID::Weapon_Flashbang ||
		weapID == WeaponID::Weapon_Hegrenade || weapID == WeaponID::Weapon_Incgrenade || weapID == WeaponID::Weapon_Smokegrenade ||
		weapID == WeaponID::Weapon_Molotov)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CAntiAim::DoFakeYawAntiAim()
{
	if (!Options::AntiAim::bFakeAnglesEnabled)
		return;
	switch (Options::AntiAim::iFakeYawAntiAimMode)
	{
	case Options::AntiAim::Yaw::BackStatic:
		GPtr::cmd->viewangles.y -= 180;
		break;
	case Options::AntiAim::Yaw::BackJitter:
		GPtr::cmd->viewangles.y -= 180;
		AddJitter(40);
		break;
	case Options::AntiAim::Yaw::ForwardStatic:
		break;
	case Options::AntiAim::Yaw::ForwardJitter:
		AddJitter(40);
		break;
	case Options::AntiAim::Yaw::Left:
		GPtr::cmd->viewangles.y += 90;
		break;
	case Options::AntiAim::Yaw::Right:
		GPtr::cmd->viewangles.y -= 90;
		break;
	case Options::AntiAim::Yaw::Spin:
		static float prevYaw = GPtr::cmd->viewangles.y;
		prevYaw += 8;
		GPtr::cmd->viewangles.y = prevYaw;
		prevYaw = GPtr::cmd->viewangles.y;
		break;
	case Options::AntiAim::Yaw::Fukkireta:
		static bool bSwitchSide = false;
		GPtr::cmd->viewangles.y += (bSwitchSide) ? -90 : 90;
		AddJitter(45);
		bSwitchSide = !bSwitchSide;
		break;
	}
}
void CAntiAim::DoFakePitchAntiAim()
{
	switch (Options::AntiAim::iFakePitchAntiAimMode)
	{
	case Options::AntiAim::Pitch::Down:
		GPtr::cmd->viewangles.x = 88.9;
		break;
	case Options::AntiAim::Pitch::Up:
		GPtr::cmd->viewangles.x = -88.9;
		break;
	case Options::AntiAim::Pitch::Forward:
		break;
	}
}

void CAntiAim::PlaySong(const char* songName, int antiAimVar, int songAntiAim)
{
	/*
	
	std::string songTemp(songName);
	std::wstring songTempMB(songTemp.begin(), songTemp.end());

	static bool isPlaying = false;
	if (antiAimVar == songAntiAim && !isPlaying)
	{
		PlaySound(songTempMB.c_str(), NULL, SND_LOOP|SND_FILENAME);
		IFace::engineclient->Con_NPrintf(1, "song");
		isPlaying = true;
	}
	
		else if (antiAimVar != songAntiAim && isPlaying)
	{
		PlaySound(0, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
		isPlaying = false;
	}
	*/
	
	

	
	
}
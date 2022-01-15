#include "stdafx.h"
#include "CBunnyhop.h"
#include "Options.h"
#include "Offsets.h"
#include "Global Interfaces.h"
#include "CUserCmd.h"
#include "QAngle.h"
#include "CBasePlayer.h"

#define FL_ONGROUND (1 << 0)  // At rest / on the ground


//TO FIX: BHOP VERY SLOW (WHETHER AUTOSTRAFER ON OR NOT) WHEN BACKJITTER ANTIAIM IS ON
void CBunnyhop::Run()
{
	m_bunnyHopping = false;
	if (!Options::Bunnyhop::bEnabled)
		return;

	if ((GPtr::cmd->buttons & IN_JUMP))
	{
		JumpIfOnGround();
	}
}

void CBunnyhop::JumpIfOnGround()
{
	m_bunnyHopping = true;

	if (GPtr::pLocalPlayer->GetFlags() & FL_ONGROUND)
	{
		GPtr::cmd->buttons |= IN_JUMP;
	}
	else
	{
		DoAutoStrafe();
		GPtr::cmd->buttons &= ~IN_JUMP; // if not on ground reset jump so we can jump again
	}
}

void CBunnyhop::DoAutoStrafe()
{
	if (!Options::Bunnyhop::bAutoStrafeEnabled)
		return;
	
	float time = IFace::inputsystem->GetPollTick();
	static float oldTime = time;

	static bool goingLeft = false;
	static bool goingRight = false;

	QAngle playerAngles;
	IFace::engineclient->GetViewAngles(playerAngles);
	
	if (GPtr::cmd->sidemove)
		return;

	if (!goingRight)
	{
		goingLeft = false;
		GPtr::cmd->sidemove = 450;
		GPtr::cmd->viewangles.y += 5;
		if ((time - oldTime) > 10)
		{
			goingRight = true;
		}
		
	}
	else if (!goingLeft)
	{
		GPtr::cmd->sidemove = -450;
		GPtr::cmd->viewangles.y -= 5;
		if ((time - oldTime) > 10)
		{
			goingRight = false;
			goingLeft = false;
		}

	}

	GPtr::cmd->viewangles.ClampAndNormalizeAngles();
	GPtr::cmd->ClampMovement();
	if (!Options::Bunnyhop::bSilentStrafe)
	{
		IFace::engineclient->SetViewAngles(GPtr::cmd->viewangles);
	}
	oldTime = time;
}

CBunnyhop GMisc::bhop;
#include "stdafx.h"
#include "CAimbot.h"
#include "Options.h"
#include "QAngle.h"
#include "Global Interfaces.h"
#include "Vector.h"
#include "CUserCmd.h"
#include "Math.h"
#include "TraceUtil.h"
#include "CBaseCombatWeapon.h"
#include "CBasePlayer.h"
#include "CResolver.h"
#include "WeaponID.h"

/*

TODO: ADD AUTOWALL
ADD PREDICTION


*/

CAimbot GMisc::aimbot;

void CAimbot::Run()
{
	if (!Options::Aimbot::bEnabled)
		return;
	if (!GPtr::pLocalPlayer->IsAlive())
		return;
	if (Options::Aimbot::bDisableWhenNoGunOut && !GPtr::pLocalPlayer->HasGunOut())
		return;
	if (Options::Aimbot::bDisableWhenReloading && GPtr::pLocalWep->GetClip1() <= 0)
		return;
	if (!Options::Aimbot::bAutoAim && !(GetAsyncKeyState(Options::Aimbot::iAimkey) & 0x8000)) //aimkey is alt
		return;

	if (!m_bIsTargeting)
	{
		FindTarget();
	}
	else if (ShouldTarget())
	{
		CalculateAndAim();
	}
}

CAimbot::CAimbot()
{
	//Add bone aimspots from highest priority to lowest
	m_aimBones.push_back(Options::Aimbot::Bone::Head);
	m_aimBones.push_back(Options::Aimbot::Chest_Center);
	m_aimBones.push_back(Options::Aimbot::Pelvis);
}

void CAimbot::FindTarget()
{
	m_pBestTarget = nullptr;
	QAngle angLocalPlayer = GPtr::cmd->viewangles; 
	QAngle angLocalPlayerOld = angLocalPlayer; 
	float flBestDist = 0;

	for (int i = 0, iMaxClients = IFace::engineclient->GetMaxClients(); i <= iMaxClients; i++)
	{
		m_pEnt = IFace::entitylist->GetClientEntity(i);

		if (!ShouldTarget())
			continue;

		if (Options::Aimbot::iPrioritization == Options::Aimbot::Distance_To_Crosshair) //bad function that isnt true fov but is rather distance based and also fov
		{
			float flFovDist = Math::GetFovDistance(GPtr::pLocalPlayer->GetOrigin(), m_pEnt->GetOrigin(), angLocalPlayerOld);
			if (flBestDist == 0)
			{
				flBestDist = flFovDist;
			}
			if (flFovDist <= flBestDist)
			{
				m_pBestTarget = m_pEnt;
				flBestDist = flFovDist;
			}
			
		}
		else if (Options::Aimbot::iPrioritization == Options::Aimbot::Distance_To_Player)
		{
			Vector vecLocalPlayer = GPtr::pLocalPlayer->GetOrigin(), vecTarget = m_pEnt->GetOrigin();
			float flDist = vecLocalPlayer.DistToSqr(vecTarget);
	
			if (flDist > flBestDist && flBestDist == 0)
			{
				flBestDist = flDist;
			}
			if (flDist <= flBestDist)
			{
				m_pBestTarget = m_pEnt;
				flBestDist = flDist;
			}
		}
		else if (Options::Aimbot::iPrioritization == Options::Aimbot::Player_Index)
		{
			CalculateAngles(angLocalPlayer);
		}
	}
	if (m_pBestTarget)
	{
		m_pEnt = m_pBestTarget;
		CalculateAngles(angLocalPlayer);
		AimAtTarget(angLocalPlayer, angLocalPlayerOld);
	}
}

bool CAimbot::ShouldTarget() 
{
	m_bIsTargeting = false;

	if (!m_pEnt) 
		return false;
	if (!GPtr::pLocalPlayer)
		return false;
	if (m_pEnt->IsDormant() || !m_pEnt->IsAlive() || m_pEnt->IsLocalPlayer() || m_pEnt->GetHealth() <= 0)
		return false;
	else if (Options::Aimbot::bTargetVisibleOnly)
	{
		m_targetBone = FindBone(m_pEnt); //find bone
		if (!AimspotVisible(m_pEnt, m_targetBone))
			return false;
	}
		
	if (m_pEnt->IsImmune())
		return false;

	bool bOnLocalPlayerTeam = m_pEnt->IsOnLocalPlayerTeam();

	if (!Options::Aimbot::bTargetEnemy && !bOnLocalPlayerTeam)
		return false;
	if (!Options::Aimbot::bTargetTeam && bOnLocalPlayerTeam)
		return false;

	m_bIsTargeting = true;
	return true;
}

inline void CAimbot::CalculateAngles(QAngle& angOutput)
{
	Vector vecLocalPlayerHead = GPtr::pLocalPlayer->GetEyePosition(); //does geteyeposition work for localplayer? i think it does
	Vector vecEnemyAimspot = m_pEnt->GetBonePosition(m_targetBone);//m_pEnt->GetBonePosition(FindAimspot(m_pEnt)); 
	Vector vecDelta = vecEnemyAimspot - vecLocalPlayerHead;

	Math::VectorAngles(vecDelta, angOutput);
}

inline void CAimbot::AimAtTarget(QAngle& angLocalPlayer, QAngle& angLocalPlayerOld) //not this func either
{
	DoAutoStop(angLocalPlayer);
	DoAutoCrouch();
	DoAutoScope();
	DoAimStep(angLocalPlayer, angLocalPlayerOld, Options::Aimbot::flAimstepAngleChange);
	DoRecoilControl(angLocalPlayer, Options::Aimbot::flRecoilControlFactor);
	SmoothAim(angLocalPlayerOld, angLocalPlayer, Options::Aimbot::flSmoothFactor);
	DoAutoShoot();

	angLocalPlayer.ClampAndNormalizeAngles();
	GPtr::cmd->viewangles = angLocalPlayer; 
	if (!Options::Aimbot::bSilentAimEnabled)
	{
		IFace::engineclient->SetViewAngles(angLocalPlayer);
	}
}

inline void CAimbot::SmoothAim(QAngle& angOld, QAngle& angOutput, float flSmoothSpeed)
{
	if (!Options::Aimbot::bSmoothAim)
		return;
	if (!Options::Aimbot::flSmoothFactor) //so you don't divide by 0
		return;

	static QAngle lastTickAngles = angOutput; //variable used to make aimstep work with silent aim
	if (Options::Aimbot::bSilentAimEnabled)
	{
		angOld = lastTickAngles; //necessary because cmd viewangles are reset to where you are looking every tick
		//this results in the smooth shooting one spot because it keeps getting reset and redoing the same movement
	} 
	angOutput.ClampAndNormalizeAngles();
	QAngle angDelta = angOutput - angOld;
	QAngle angAimstep = angDelta / flSmoothSpeed;
	angOutput = angOld + angAimstep;
	angOutput.ClampAndNormalizeAngles();

	lastTickAngles = angOutput; //update last tick view angles to the next smooth step so it can progress
}

inline void CAimbot::DoRecoilControl(QAngle& angOutput, float flRCSFactor)
{
	if (!Options::Aimbot::bControlRecoil)
		return;
	QAngle punch = GPtr::pLocalPlayer->GetAimPunchAngle();
	angOutput -= (GPtr::pLocalPlayer->GetAimPunchAngle() * flRCSFactor);
}

inline void CAimbot::CalculateAndAim()
{
	QAngle angLocalPlayer = GPtr::cmd->viewangles;
	QAngle angLocalPlayerOld = angLocalPlayer;
	CalculateAngles(angLocalPlayer);
	AimAtTarget(angLocalPlayer, angLocalPlayerOld);
}

inline void CAimbot::DoAutoShoot() 
{
	if (!Options::Aimbot::bAutoShoot)
		return;
	if (m_bAimstepping)
		return;
	if (GPtr::pLocalPlayer->GetWeapon()->GetNextPrimaryAttack() < GPtr::pLocalPlayer->GetTime())		//	if ((GPtr::pLocalPlayer->GetWeapon())->GetNextPrimaryAttack() <= IFace::engineclient->GetLastTimeStamp())
	{
		GPtr::cmd->buttons |= IN_ATTACK;
	}
}

void CAimbot::DoAutoStop(QAngle& angNew)
{
	if (!Options::Aimbot::bAutoStop)
		return;

	Vector vecVelocity = GPtr::pLocalPlayer->GetVelocity();
	vecVelocity.z = 0;
	float speed = vecVelocity.Length2D();
	if (speed < 20)
	{
		GPtr::cmd->forwardmove = 0;
		GPtr::cmd->sidemove = 0;
	}
	else
	{
		//This is copypasted -- I don't quite get what the purpose of "direction.y = cmd->viewangles.y - direction.y" is
		QAngle direction;
		Math::VectorAngles(vecVelocity, direction);
		direction.y = angNew.y - direction.y;

		Vector forward;
		Math::AngleVectors(direction, &forward, 0, 0);
		Vector negated_direction = forward * -speed;

		GPtr::cmd->forwardmove = negated_direction.x;
		GPtr::cmd->sidemove = negated_direction.y;
		GPtr::cmd->ClampMovement();
	}
}

inline void CAimbot::DoAutoCrouch()
{
	if (!Options::Aimbot::bAutoCrouch)
		return;
	GPtr::cmd->buttons |= IN_DUCK;
}

inline void CAimbot::DoAutoScope()
{
	if (!Options::Aimbot::bAutoScope || GPtr::pLocalPlayer->IsScoped())
		return;

	if (GPtr::pLocalPlayer->UsingScopeWeapon() || GPtr::pLocalPlayer->UsingSightWeapon())
	{
		GPtr::cmd->buttons |= IN_ATTACK2;
	}
}
 
void CAimbot::DoAimStep(QAngle& angNew, QAngle& angOld, float angleChangePerStep)//seems to give vac auth error eventually
{
	m_bAimstepping = false; 
	if (!Options::Aimbot::bAimstepEnabled)
		return;
	static QAngle lastTickAngles = GPtr::cmd->viewangles; //variable used to make aimstep work with silent aim
	if (Options::Aimbot::bSilentAimEnabled)
	{
		angOld = lastTickAngles; //necessary because cmd viewangles are reset to where you are looking every tick
		//this results in the aimstep shooting one spot because it keeps getting reset and redoing the same movement
	}

	angNew.ClampAndNormalizeAngles();

	float flDeltaYaw = GetDelta(angNew.y, angOld.y);//angNew.y - angOld.y;
	float flStepsYaw = flDeltaYaw / angleChangePerStep;
	float flDeltaPitch = angNew.x - angOld.x;
	float flStepsPitch = flDeltaPitch / angleChangePerStep;

	if (flStepsYaw >= 1)
	{
		angNew.y = angOld.y + angleChangePerStep;
		m_bAimstepping = true;
	}
	else if (flStepsYaw <= -1)
	{
		angNew.y = angOld.y - angleChangePerStep;
		m_bAimstepping = true;
	}
	if (flStepsPitch >= 1)
	{
		angNew.x = angOld.x + angleChangePerStep;
		m_bAimstepping = true;
	}
	else if (flStepsPitch <= -1)
	{
		angNew.x = angOld.x - angleChangePerStep;
		m_bAimstepping = true;	
	}
	angNew.ClampAndNormalizeAngles();

	lastTickAngles = angNew; // update last tick view angles to the next aimstep so it can progress
}

float CAimbot::GetDelta(float newYaw, float oldYaw) const
{

	float delta1 = ((180 + oldYaw) + (180 - newYaw)) * -1;
	float delta2 = newYaw - oldYaw;
	float delta3 = (180 + newYaw) + (180 - oldYaw);
	
	float delta1Abs = abs(delta1);
	float delta2Abs = abs(delta2);
	float delta3Abs = abs(delta3);

	if (delta1Abs < delta2Abs)
	{
		if (delta1Abs < delta3Abs)
		{
			return delta1;
		}
		else
		{
			return delta3;
		}
	}
	else if (delta2Abs < delta1Abs)
	{
		if (delta2Abs < delta3Abs)
		{
			return delta2;
		}
		return delta3;
	}
}

bool CAimbot::AimspotVisible(CBasePlayer* entity, int aimBone)
{
	if (aimBone == -1)
	{
		m_targetBone = Options::Aimbot::iTargetBone;
		return false;
	}
	else
	{
		return true;
	}
}

int CAimbot::FindBone(CBasePlayer* entity)
{
	if (GMisc::resolver.ShouldBodyAim(m_pEnt)) //If target should be bodyaimed, do so
	{
		return Options::Aimbot::Chest_Lower;
	}

	if (Options::Aimbot::bMultiAimspot) //if multiaimspot is on, try to find appropriate aimspot
	{
		for (int bone : m_aimBones)
		{
			if (TraceUtil::BoneVisibleFromLocalPlayer(m_pEnt, bone))
			{
				return bone;
			}
		}
	}
	else //neither baim nor multi aimspot
	{
		if (TraceUtil::BoneVisibleFromLocalPlayer(m_pEnt, Options::Aimbot::iTargetBone))
		{
			return Options::Aimbot::iTargetBone;
		}
	}

	return -1; //No visible bone was found (handled by caller)
}
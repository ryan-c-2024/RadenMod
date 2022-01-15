#include "stdafx.h"
#include "CBasePlayer.h"
#include "Offsets.h"
#include "QAngle.h"
#include "Global Interfaces.h"
#include "Vector.h"
#include "matrix3x4.h"
#include "CBaseCombatWeapon.h"
#include "WeaponID.h"
#include "CUserCmd.h"

#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box


int CBasePlayer::GetHealth()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iHealth);
}

bool CBasePlayer::IsAlive()
{
	if (*(bool*)((uintptr_t)this + GMisc::offset.m_lifeState))
	{
		return false;
	}
	else
	{
		return true;
	}
}

int CBasePlayer::GetArmor()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_ArmorValue);
}

bool CBasePlayer::HasHelmet()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bHasHelmet);
}

bool CBasePlayer::IsDefusing()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bIsDefusing);
}

bool CBasePlayer::HasDefuser()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bHasDefuser);
}

bool CBasePlayer::IsScoped()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bIsScoped);
}

int CBasePlayer::GetFlags()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_fFlags);
}

int CBasePlayer::GetFOV()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iFOV);
}

void CBasePlayer::SetFOV(int iFOV)
{
	*(int*)((uintptr_t)this + GMisc::offset.m_iFOV) = iFOV;
}

int CBasePlayer::GetObserverMode()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iObserverMode);
}

std::string CBasePlayer::GetLastPlaceName()
{
	return std::string(((const char*)((uintptr_t)this + GMisc::offset.m_szLastPlaceName)));
}

CBasePlayer* CBasePlayer::GetObserverTarget()
{
	uintptr_t* targetHandle = *(uintptr_t**)((uintptr_t)this + GMisc::offset.m_hObserverTarget);
	return IFace::entitylist->GetClientEntityFromHandle(targetHandle);
}

float CBasePlayer::GetDuckAmount()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flDuckAmount);
}

float CBasePlayer::GetDuckSpeed()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flDuckSpeed);
}

QAngle CBasePlayer::GetViewPunchAngle()
{
	return *(QAngle*)((uintptr_t)this + GMisc::offset.m_viewPunchAngle);
}
QAngle CBasePlayer::GetAimPunchAngle()
{
	return *(QAngle*)((uintptr_t)this + GMisc::offset.m_aimPunchAngle);
}

/*
void CBasePlayer::DisableSkyboxFog()
{
*(bool*)((uintptr_t)this + GMisc::offset.m_skybox3dfogenable) = false;
}
*/


int CBasePlayer::IsDucked()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_bDucked);
}

int CBasePlayer::GetCurrentMoney()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iAccount);
}

bool CBasePlayer::IsImmune()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bGunGameImmunity);
}

void CBasePlayer::SetFlashDuration(float flDuration)
{
	*(float*)((uintptr_t)this + GMisc::offset.m_flFlashDuration) = flDuration;
}

void CBasePlayer::SetFlashAlpha(float flAlpha)
{
	*(float*)((uintptr_t)this + GMisc::offset.m_flFlashMaxAlpha) = flAlpha;
}

float CBasePlayer::GetFlashAlpha()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flFlashMaxAlpha);
}

bool CBasePlayer::IsInDuckJump()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bInDuckJump);
}

float CBasePlayer::GetFallVelocity()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flFallVelocity);
}

void CBasePlayer::ShouldDrawViewmodel(bool bShouldDraw)
{
	*(bool*)((uintptr_t)this + GMisc::offset.m_flFlashMaxAlpha) = bShouldDraw;
}

bool CBasePlayer::IsAutoMovementAllowed()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bInDuckJump);
}

/*
void CBasePlayer::SetSkyboxScale(float flScale)
{
*(float*)((uintptr_t)this + GMisc::offset.m_skybox3dscale) = flScale;
}
*/


bool CBasePlayer::IsInBuyZone()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bInBuyZone);
}

QAngle CBasePlayer::GetEyeAngles()
{
	return *(QAngle*)((uintptr_t)this + GMisc::offset.m_angEyeAngles);
}

void CBasePlayer::ForcePitchAngle(float flNewPitch)
{
	(*(QAngle*)((uintptr_t)this + GMisc::offset.m_angEyeAngles)).x = flNewPitch;
}

void CBasePlayer::ForceYawAngle(float flNewYaw)
{
	(*(QAngle*)((uintptr_t)this + GMisc::offset.m_angEyeAngles)).y = flNewYaw;
}

bool CBasePlayer::IsLocalPlayer()
{
	return (this == Util::GetLocalPlayerPointer()) ? true : false;
}

float CBasePlayer::GetMolotovUseTime()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_fMolotovUseTime);
}

CLocalPlayer* Util::GetLocalPlayerPointer()
{
	return (CLocalPlayer*)IFace::entitylist->GetClientEntity(IFace::engineclient->GetLocalPlayer());
}

int CBasePlayer::GetTeam()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iTeamNum);
}

bool CBasePlayer::IsOnLocalPlayerTeam()
{
	if (!this)
		return false;
	int iEntTeam = GetTeam();
	int iLocalPlayerTeam = GPtr::pLocalPlayer->GetTeam(); //issue: pLocalPlayer is sometimes 0 on injection and it crashes
	return (iEntTeam == iLocalPlayerTeam) ? true : false;
}

Vector CBasePlayer::GetViewOffset()
{
	return *(Vector*)((uintptr_t)this + GMisc::offset.m_vecViewOffset);
}

Vector CBasePlayer::GetOrigin()
{
	return *(Vector*)((uintptr_t)this + GMisc::offset.m_vecOrigin);
}

bool CBasePlayer::IsDormant()
{
	return *(bool*)((uintptr_t)this + GMisc::offset.m_bDormant);
}

int CBasePlayer::GetIndex()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iEntityIndex);
}

int CBasePlayer::GetShotsFired()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iShotsFired);
}

uintptr_t CBasePlayer::GetWeaponHandle()
{
	return *(uintptr_t*)((uintptr_t)this + GMisc::offset.m_hActiveWeapon);
}

CBaseCombatWeapon* CBasePlayer::GetWeapon()
{
	return (CBaseCombatWeapon*)IFace::entitylist->GetClientEntityFromHandle((uintptr_t*)GetWeaponHandle());
}

Vector CBasePlayer::GetEyePosition()
{
	return (GetOrigin() + GetViewOffset());
}

Vector CBasePlayer::GetCurrentEyePosition()
{
	Vector vecOrigin = GetOrigin();
	Vector vecEyePos = vecOrigin;

	if (GetFlags() & FL_DUCKING)
	{
		vecEyePos.z += 46.045;
	}
	else
	{
		vecEyePos.z += 64.063;
	}
	return vecEyePos;
}

float CBasePlayer::GetLowerBodyYaw()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flLowerBodyYawTarget);
}

int CBasePlayer::GetMoveState()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iMoveState);
}

Vector CBasePlayer::GetBonePosition(int iBoneNumber)
{
	static matrix3x4_t boneMatrix[MAXSTUDIOBONES];

	if (!SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0))
		return Vector(0, 0, 0);

	return Vector(boneMatrix[iBoneNumber][0][3], boneMatrix[iBoneNumber][1][3], boneMatrix[iBoneNumber][2][3]);
}

Vector CBasePlayer::GetVelocity()
{
	uintptr_t Address = (uintptr_t)this + GMisc::offset.m_vecVelocity;
	return *(Vector*)((uintptr_t)this + GMisc::offset.m_vecVelocity);
}
float CBasePlayer::GetTime()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flTime);
}

bool CBasePlayer::HasGunOut()
{
	int weapID = GPtr::pLocalWep->GetWeaponID();

	if (weapID == WeaponID::Weapon_C4 || weapID == WeaponID::Weapon_KnifeCT || weapID == WeaponID::Weapon_KnifeT ||
		weapID == WeaponID::Weapon_Decoy || weapID == WeaponID::Weapon_Taser || weapID == WeaponID::Weapon_Flashbang ||
		weapID == WeaponID::Weapon_Hegrenade || weapID == WeaponID::Weapon_Incgrenade || weapID == WeaponID::Weapon_Smokegrenade ||
		weapID == WeaponID::Weapon_Molotov || weapID == WeaponID::Weapon_None)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CBasePlayer::IsReloading()
{
	if (GetFlags() & IN_RELOAD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

MoveType_t CBasePlayer::GetMoveType()
{
	return *(MoveType_t*)((uintptr_t)this + GMisc::offset.movetype);
}

bool CBasePlayer::UsingScopeWeapon()
{
	int weaponID = GPtr::pLocalWep->GetWeaponID();

	if (weaponID == WeaponID::Weapon_Ssg08 || weaponID == WeaponID::Weapon_G3sg1 || weaponID == WeaponID::Weapon_Scar20 || weaponID == WeaponID::Weapon_Awp)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CBasePlayer::UsingSightWeapon() 
{
	int weaponID = GPtr::pLocalWep->GetWeaponID();

	if (weaponID == WeaponID::Weapon_Aug || weaponID == WeaponID::Weapon_Sg552 || weaponID == WeaponID::Weapon_Sg550 || 
		weaponID == WeaponID::Weapon_Sg556) //three sg's ??
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CLocalPlayer::SetSendPacket(bool stateToSet)
{
	if (GetSendPacket() == stateToSet)
		return;

	static bool* sendPacket = reinterpret_cast<bool*>((uintptr_t)GetModuleHandleA("engine.dll") + 0xCACAA);
	DWORD oldProtection;
	VirtualProtect(sendPacket, 1, PAGE_EXECUTE_READWRITE, &oldProtection);
	*sendPacket = stateToSet; //bool is implicitly converted back to a byte here.
	VirtualProtect(sendPacket, 1, oldProtection, &oldProtection);
}

bool CLocalPlayer::GetSendPacket()
{
	static bool* sendPacket = reinterpret_cast<bool*>((uintptr_t)GetModuleHandleA("engine.dll") + 0xCACAA);
	return *sendPacket;
}


#pragma once
#include <string> //have to include or or i get errors
#include "IClientEntity.h"

#define MAXSTUDIOBONES 128

class QAngle;
class Vector;
class CBaseCombatWeapon;
enum MoveType_t;

class CBasePlayer : public IClientEntity
{
public:

	int GetHealth();
	bool IsAlive();
	int GetArmor();
	bool HasHelmet();
	bool IsDefusing();
	bool HasDefuser();
	bool IsScoped();
	int GetFlags();
	int GetFOV();
	void SetFOV(int iFOV);
	int GetObserverMode();
	std::string GetLastPlaceName();
	float GetDuckAmount();
	float GetDuckSpeed();
	CBasePlayer* GetObserverTarget();

	int IsDucked(); //difference between isducked and isducking????
	bool IsInDuckJump();
	float GetFallVelocity();
	QAngle GetViewPunchAngle();
	QAngle GetAimPunchAngle();
	void ShouldDrawViewmodel(bool bShouldDraw);
	bool IsAutoMovementAllowed();
	int GetCurrentMoney();
	bool IsImmune();
	void SetFlashDuration(float flDuration);
	void SetFlashAlpha(float flAlpha);
	float GetFlashAlpha();
	bool IsInBuyZone();
	QAngle GetEyeAngles();
	void ForceYawAngle(float flNewYaw);
	void ForcePitchAngle(float flNewPitch);
	bool IsLocalPlayer();
	//Only works with molo T side
	float GetMolotovUseTime(); 
	int GetTeam();
	bool IsOnLocalPlayerTeam();
	Vector GetViewOffset();
	Vector GetOrigin();
	int GetShotsFired();
	uintptr_t GetWeaponHandle();
	CBaseCombatWeapon* GetWeapon();
	Vector GetEyePosition();
	float GetLowerBodyYaw();
	int GetMoveState();
	//Because GetEyePosition only updates once the entity (if not localplayer) goes dormant and comes back into range
	Vector GetCurrentEyePosition();

	Vector GetBonePosition(int iBoneNumber);
	Vector GetVelocity();

	bool IsDormant();
	int GetIndex();

	float GetTime();

	bool HasGunOut();
	bool IsReloading();
	MoveType_t GetMoveType();
	bool UsingScopeWeapon(); //using weapon that has magnifying scope
	bool UsingSightWeapon(); //using weapon that has a usable sight (not including scoped weapons)
};

class CLocalPlayer : public CBasePlayer
{
public:
	void SetSendPacket(bool stateToSet);
private:
	inline bool GetSendPacket();
};

namespace GPtr
{
	extern CLocalPlayer* pLocalPlayer;
}

namespace Util
{
	CLocalPlayer* GetLocalPlayerPointer();
}

enum CS_TEAM
{
	TEAM_UNASSIGNED = 0,
	TEAM_SPECTATOR = 1
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,	// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

								// should always be defined as the last item in the list
								MOVETYPE_LAST = MOVETYPE_CUSTOM,

								MOVETYPE_MAX_BITS = 4
};
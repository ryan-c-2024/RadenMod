#include "stdafx.h"
#include "Offsets.h"
#include "CNetvarManager.h"

Offsets GMisc::offset;

void Offsets::SetupOffsets()
{
	CNetvarManager netvar;
	netvar.Init();
	netvar.DumpTables();

	m_iHealth = netvar.GetNetvarOffset("DT_BasePlayer", "m_iHealth");
	m_fFlags = netvar.GetNetvarOffset("DT_BasePlayer", "m_fFlags");
	m_lifeState = netvar.GetNetvarOffset("DT_BasePlayer", "m_lifeState");
	m_iFOV = netvar.GetNetvarOffset("DT_BasePlayer", "m_iFOV");
	m_iObserverMode = netvar.GetNetvarOffset("DT_BasePlayer", "m_iObserverMode");
	m_szLastPlaceName = netvar.GetNetvarOffset("DT_BasePlayer", "m_szLastPlaceName");
	m_flDuckAmount = netvar.GetNetvarOffset("DT_BasePlayer", "m_flDuckAmount");
	m_flDuckSpeed = netvar.GetNetvarOffset("DT_BasePlayer", "m_flDuckSpeed");
	m_hObserverTarget = netvar.GetNetvarOffset("DT_BasePlayer", "m_hObserverTarget");

	m_Local = netvar.GetNetvarOffset("DT_BasePlayer", "m_Local");
	m_iHideHUD = netvar.GetNetvarOffset("DT_BasePlayer", "m_iHideHUD") + m_Local;
	m_bDucked = netvar.GetNetvarOffset("DT_BasePlayer", "m_bDucked") + m_Local;
	//m_bDucking = netvar.GetNetvarOffset("DT_BasePlayer", "m_bDucking") + m_Local;
	//m_flLastDuckTime = netvar.GetNetvarOffset("DT_BasePlayer", "m_flLastDuckTime") + m_Local;
	m_bInDuckJump = netvar.GetNetvarOffset("DT_BasePlayer", "m_bInDuckJump") + m_Local;
	m_flFallVelocity = netvar.GetNetvarOffset("DT_BasePlayer", "m_flFallVelocity") + m_Local;
	m_viewPunchAngle = netvar.GetNetvarOffset("DT_BasePlayer", "m_viewPunchAngle") + m_Local;
	m_aimPunchAngle = netvar.GetNetvarOffset("DT_BasePlayer", "m_aimPunchAngle") + m_Local;
	//m_aimPunchAngleVel = netvar.GetNetvarOffset("DT_BasePlayer", "m_aimPunchAngleVel");
	m_bDrawViewmodel = netvar.GetNetvarOffset("DT_BasePlayer", "m_bDrawViewmodel") + m_Local;
	//m_flStepSize = netvar.GetNetvarOffset("DT_BasePlayer", "m_flStepSize") + m_Local;
	m_bAllowAutoMovement = netvar.GetNetvarOffset("DT_BasePlayer", "m_bAllowAutoMovement") + m_Local;
	m_vecViewOffset = netvar.GetNetvarOffset("DT_BasePlayer", "m_vecViewOffset[0]"); //should i add to m_local?

	m_angEyeAngles = netvar.GetNetvarOffset("DT_CSPlayer", "m_angEyeAngles");
	m_bIsRespawningForDMBonus = netvar.GetNetvarOffset("DT_CSPlayer", "m_bIsRespawningForDMBonus");
	m_iPlayerState = netvar.GetNetvarOffset("DT_CSPlayer", "m_iPlayerState");
	m_iAccount = netvar.GetNetvarOffset("DT_CSPlayer", "m_iAccount");
	m_iStartAccount = netvar.GetNetvarOffset("DT_CSPlayer", "m_iStartAccount");
	m_bInBombZone = netvar.GetNetvarOffset("DT_CSPlayer", "m_bInBombZone");
	m_bInBuyZone = netvar.GetNetvarOffset("DT_CSPlayer", "m_bInBuyZone");
	m_bInNoDefuseArea = netvar.GetNetvarOffset("DT_CSPlayer", "m_bInNoDefuseArea");
	m_iMoveState = netvar.GetNetvarOffset("DT_CSPlayer", "m_iMoveState");
	m_iClass = netvar.GetNetvarOffset("DT_CSPlayer", "m_iClass");
	m_ArmorValue = netvar.GetNetvarOffset("DT_CSPlayer", "m_ArmorValue");
	m_bHasDefuser = netvar.GetNetvarOffset("DT_CSPlayer", "m_bHasDefuser");
	m_bInHostageRescueZone = netvar.GetNetvarOffset("DT_CSPlayer", "m_bInHostageRescueZone");
	m_bIsDefusing = netvar.GetNetvarOffset("DT_CSPlayer", "m_bIsDefusing");
	m_bIsGrabbingHostage = netvar.GetNetvarOffset("DT_CSPlayer", "m_bIsGrabbingHostage");
	m_bIsScoped = netvar.GetNetvarOffset("DT_CSPlayer", "m_bIsScoped");
	m_bIsWalking = netvar.GetNetvarOffset("DT_CSPlayer", "m_bIsWalking");
	m_bResumeZoom = netvar.GetNetvarOffset("DT_CSPlayer", "m_bResumeZoom");
	m_fImmuneToGunGameDamageTime = netvar.GetNetvarOffset("DT_CSPlayer", "m_fImmuneToGunGameDamageTime");
	m_bGunGameImmunity = netvar.GetNetvarOffset("DT_CSPlayer", "m_bGunGameImmunity");
	m_bHasMovedSinceSpawn = netvar.GetNetvarOffset("DT_CSPlayer", "m_bHasMovedSinceSpawn");
	m_fMolotovUseTime = netvar.GetNetvarOffset("DT_CSPlayer", "m_fMolotovUseTime");
	m_bIsRescuing = netvar.GetNetvarOffset("DT_CSPlayer", "m_bIsRescuing");
	m_isCurrentGunGameLeader = netvar.GetNetvarOffset("DT_CSPlayer", "m_isCurrentGunGameLeader");
	m_iMatchStats_Kills = netvar.GetNetvarOffset("DT_CSPlayer", "m_iMatchStats_Kills");
	m_iMatchStats_Damage = netvar.GetNetvarOffset("DT_CSPlayer", "m_iMatchStats_Damage");
	m_iMatchStats_CashEarned = netvar.GetNetvarOffset("DT_CSPlayer", "m_iMatchStats_CashEarned");
	m_rank = netvar.GetNetvarOffset("DT_CSPlayer", "m_rank");
	m_bHasHelmet = netvar.GetNetvarOffset("DT_CSPlayer", "m_bHasHelmet");
	m_flFlashDuration = netvar.GetNetvarOffset("DT_CSPlayer", "m_flFlashDuration");
	m_flFlashMaxAlpha = netvar.GetNetvarOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
	m_bIsControllingBot = netvar.GetNetvarOffset("DT_CSPlayer", "m_bIsControllingBot");
	m_bCanControlObservedBot = netvar.GetNetvarOffset("DT_CSPlayer", "m_bCanControlObservedBot");
	m_iControlledBotEntIndex = netvar.GetNetvarOffset("DT_CSPlayer", "m_iControlledBotEntIndex");
	m_nLastKillerIndex = netvar.GetNetvarOffset("DT_CSPlayer", "m_nLastKillerIndex");
	m_flLowerBodyYawTarget = netvar.GetNetvarOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
	m_bStrafing = netvar.GetNetvarOffset("DT_CSPlayer", "m_bStrafing");
	m_flThirdpersonRecoil = netvar.GetNetvarOffset("DT_CSPlayer", "m_flThirdpersonRecoil");

	m_iTeamNum = netvar.GetNetvarOffset("DT_BaseEntity", "m_iTeamNum");
	m_vecOrigin = netvar.GetNetvarOffset("DT_BaseEntity", "m_vecOrigin");
	movetype = 0x258;

	m_iShotsFired = netvar.GetNetvarOffset("DT_CSPlayer", "m_iShotsFired");
	m_vecVelocity = netvar.GetNetvarOffset("DT_BasePlayer", "m_vecVelocity[0]");
	m_flTime = 0x3c; //hardcoded offset lol

	m_bBombPlanted = netvar.GetNetvarOffset("DT_CSGameRulesProxy", "m_bBombPlanted");
	m_iRoundTime = netvar.GetNetvarOffset("DT_CSGameRulesProxy", "m_iRoundTime");

	m_hActiveWeapon = netvar.GetNetvarOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");

	m_flNextPrimaryAttack = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	m_flNextSecondaryAttack = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_flNextSecondaryAttack");
	m_iClip1 = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_iClip1");
	m_iSecondaryReserveAmmoCount = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_iSecondaryReserveAmmoCount");
	m_hWeaponWorldModel = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
	m_iNumEmptyAttacks = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_iNumEmptyAttacks");
	m_iPrimaryReserveAmmoCount = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
	m_iViewModelIndex = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");

	m_AttributeManager = netvar.GetNetvarOffset("DT_EconEntity", "m_AttributeManager");
	m_Item = netvar.GetNetvarOffset("DT_EconEntity", "m_Item");
	m_iItemDefinitionIndex = netvar.GetNetvarOffset("DT_EconEntity", "m_iItemDefinitionIndex");

	m_bDormant = 0xE9;
	m_iEntityIndex = 0x64;

	m_bInReload = netvar.GetNetvarOffset("DT_BaseCombatWeapon", "m_bInReload");
}


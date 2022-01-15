#pragma once

typedef unsigned long OffsetType;

struct Offsets
{
	void SetupOffsets();

	OffsetType m_fFlags; //Start of DT_BasePlayer
	OffsetType m_iHealth;
	OffsetType m_lifeState;
	OffsetType m_iFOV;
	OffsetType m_iObserverMode;
	OffsetType m_szLastPlaceName;
	OffsetType m_flDuckAmount;
	OffsetType m_flDuckSpeed;
	OffsetType m_hObserverTarget;

	//Start of DT_Local (after m_Local itself)
	OffsetType m_Local; //need m_local for other offsets in DT_Local (baseplayer + m_local + other offset)
	OffsetType m_iHideHUD; //However, I add it when grabbing the offsets so its all good
	OffsetType m_bDucked;
	//OffsetType m_bDucking;
	//OffsetType m_flLastDuckTime;
	OffsetType m_bInDuckJump;
	OffsetType m_flFallVelocity;
	OffsetType m_viewPunchAngle;
	OffsetType m_aimPunchAngle;
	//OffsetType m_aimPunchAngleVel;
	OffsetType m_bDrawViewmodel;
	//OffsetType m_flStepSize;
	OffsetType m_bAllowAutoMovement;
	OffsetType m_vecViewOffset;

	//Start of DT_CSPlayer:
	OffsetType m_angEyeAngles;
	OffsetType m_bIsRespawningForDMBonus;
	OffsetType m_iPlayerState;
	OffsetType m_iAccount;
	OffsetType m_iStartAccount;
	OffsetType m_bInBombZone;
	OffsetType m_bInBuyZone;
	OffsetType m_bInNoDefuseArea;
	OffsetType m_iMoveState;
	OffsetType m_iClass;
	OffsetType m_ArmorValue;
	OffsetType m_bHasDefuser;
	OffsetType m_bInHostageRescueZone;
	OffsetType m_bIsDefusing;
	OffsetType m_bIsGrabbingHostage;
	OffsetType m_bIsScoped;
	OffsetType m_bIsWalking;
	OffsetType m_bResumeZoom;
	OffsetType m_fImmuneToGunGameDamageTime;
	OffsetType m_bGunGameImmunity;
	OffsetType m_bHasMovedSinceSpawn;
	OffsetType m_fMolotovUseTime; //  <---- what's this
	//OffsetType m_fMolotovDamageTime;
	OffsetType m_bIsRescuing;
	OffsetType m_isCurrentGunGameLeader;
	OffsetType m_iMatchStats_Kills;
	OffsetType m_iMatchStats_Damage;
	OffsetType m_iMatchStats_CashEarned;
	OffsetType m_rank;
	OffsetType m_bHasHelmet;
	OffsetType m_flFlashDuration;
	OffsetType m_flFlashMaxAlpha;
	OffsetType m_bIsControllingBot;
	OffsetType m_bCanControlObservedBot;
	OffsetType m_iControlledBotEntIndex;
	OffsetType m_nLastKillerIndex;
	OffsetType m_flLowerBodyYawTarget;
	OffsetType m_bStrafing;
	OffsetType m_flThirdpersonRecoil;	

	//Start of DT_BaseEntity
	OffsetType m_iTeamNum;
	OffsetType m_vecOrigin;
	OffsetType movetype;

	//Start of DT_LocalPlayerExclusive
	OffsetType m_iShotsFired;
	OffsetType m_flTime;
	OffsetType m_vecVelocity;

	//Start of non DT netvars
	OffsetType m_bDormant;
	OffsetType m_iEntityIndex;

	//Start of GameRules
	OffsetType m_bBombPlanted;
	OffsetType m_iRoundTime;

	//Start of BaseCombatCharacter
	OffsetType m_hActiveWeapon;

	OffsetType m_flNextPrimaryAttack;
	OffsetType m_flNextSecondaryAttack;

	OffsetType m_iClip1;
	OffsetType m_hWeaponWorldModel;
	OffsetType m_iNumEmptyAttacks;
	OffsetType m_iPrimaryReserveAmmoCount;
	OffsetType m_iSecondaryReserveAmmoCount;
	OffsetType m_iViewModelIndex;

	OffsetType m_AttributeManager;
	OffsetType m_Item;
	OffsetType m_iItemDefinitionIndex;
	OffsetType m_bInReload;
};

namespace GMisc
{
	extern Offsets offset;
}

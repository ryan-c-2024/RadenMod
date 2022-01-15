#pragma once
#include <string>

namespace Options
{
	namespace Bunnyhop
	{
		extern bool bEnabled;
		extern bool bAutoStrafeEnabled;
		extern bool bSilentStrafe;
	}
	namespace GoombaStomp
	{
		extern bool bEnabled;
	}
	namespace Misc
	{
		extern bool bChangeFlashAlphaEnabled;
		extern float flNewFlashAlpha;
		extern bool bChatSpamEnabled;
		extern bool bSlowFall;
		extern bool bFakeLag;
		extern int iFakeLagChokedTicks;
	}
	namespace ChatSpamPositions
	{
		extern bool bEnabled;
		extern bool bCalloutTeam;
		extern bool bCalloutEnemy;
		extern bool bUseTeamChat;
	}
	namespace Visual
	{
		extern bool bDisableScopeVisual;
	}
	namespace Esp
	{
		extern bool bEnabled;
		extern bool bDrawTeam;
		extern bool bDrawEnemy;
		extern bool bDrawHealthBar;
		extern bool bDrawArmorBar;
		extern bool bDrawBonePos;
		extern bool bDrawBoxEsp;
		extern bool bNameEsp;
		extern bool bWeaponEsp;
		extern bool bHealthBasedColoring;
	}
	namespace Aimbot
	{
		enum 
		{
			Distance_To_Player = 1,
			Distance_To_Crosshair,
			Player_Index
		};
		enum Bone
		{
			//some of these are broken
			Stomach = 3,
			Chest_Lower,
			Chest_Center,
			Chest_Upper,
			Head = 8,
			Neck = 9,
			Left_Elbow = 12,
			Right_Elbow = 42,
			Pelvis = 77,
			Left_Knee = 71,
			Right_Knee = 78,
			Left_Toe = 68,
			Hand = 38
		};
		extern bool bEnabled;
		extern bool bTargetTeam;
		extern bool bTargetEnemy;
		extern bool bSmoothAim;
		extern bool bSilentAimEnabled;
		extern bool bControlRecoil;
		extern float flSmoothFactor;
		extern float flRecoilControlFactor;
		extern int iPrioritization;
		extern int iTargetBone;
		extern bool bTargetVisibleOnly;
		extern bool bAutoShoot;
		extern bool bAutoStop;
		extern int iAimkey;
		extern bool bAutoCrouch;
		extern bool bAimstepEnabled;
		extern float flAimstepAngleChange;
		extern bool bAutoScope;
		extern bool bDisableWhenNoGunOut;
		extern bool bSilentRCS;
		extern bool bAutoAim;
		extern bool bDisableWhenReloading;
		extern bool bMultiAimspot;

		//autowall solely based on lowering traceray fraction lol
		extern bool bGhettoAutowall;
		extern float flGhettoAutowallModifier;
	}
	namespace NetvarManager
	{
		extern bool bDumpDataTables;
	}
	namespace AntiAim
	{
		enum Yaw
		{
			BackStatic = 1,
			BackJitter,
			ForwardStatic,
			ForwardJitter,
			Left,
			Right,
			Spin,
			Fukkireta
		};
		enum Pitch
		{
			Down = 1,
			Forward,
			Up
		};
		extern bool bEnabled;
		extern bool bFakeAnglesEnabled;
		extern bool bShowAngles;
		extern int iYawAntiAimMode;
		extern int iPitchAntiAimMode;
		extern int iFakeYawAntiAimMode;
		extern int iFakePitchAntiAimMode;
	}
	namespace Resolver
	{
		extern bool bEnabled;
		extern bool bBodyAimUnresolvable;
	}
	namespace Config
	{
		extern bool bUseLoadedConfig;
		//note: config is selected but may not be in use
		extern std::string selectedConfig;
	}
}
#include "stdafx.h"
#include "Options.h"

bool Options::Bunnyhop::bEnabled = true;
bool Options::Bunnyhop::bAutoStrafeEnabled = true;
bool Options::Bunnyhop::bSilentStrafe = true;

bool Options::GoombaStomp::bEnabled = true;

bool Options::Misc::bChangeFlashAlphaEnabled = true;
float Options::Misc::flNewFlashAlpha = 40.0f;
bool Options::Misc::bChatSpamEnabled = false;
bool Options::Misc::bSlowFall = false;
bool Options::Misc::bFakeLag = false;
int Options::Misc::iFakeLagChokedTicks = 13;

bool Options::ChatSpamPositions::bEnabled = false;
bool Options::ChatSpamPositions::bCalloutTeam = true;
bool Options::ChatSpamPositions::bCalloutEnemy = false;
bool Options::ChatSpamPositions::bUseTeamChat = false;

bool Options::Visual::bDisableScopeVisual = false;
bool Options::Esp::bDrawEnemy = true;
bool Options::Esp::bDrawTeam = true;
bool Options::Esp::bEnabled = true;
bool Options::Esp::bDrawArmorBar = true;
bool Options::Esp::bDrawHealthBar = true;
bool Options::Esp::bDrawBonePos = false;
bool Options::Esp::bDrawBoxEsp = true;
bool Options::Esp::bNameEsp = true;
bool Options::Esp::bWeaponEsp = true;
bool Options::Esp::bHealthBasedColoring = false;

bool Options::Aimbot::bEnabled = true;
bool Options::Aimbot::bSmoothAim = false;
float Options::Aimbot::flSmoothFactor = 10.0f;
bool Options::Aimbot::bControlRecoil = true;
float Options::Aimbot::flRecoilControlFactor = 2.0f;
bool Options::Aimbot::bTargetEnemy = true;
bool Options::Aimbot::bTargetTeam = false;
bool Options::Aimbot::bSilentAimEnabled = false;
int Options::Aimbot::iTargetBone = Options::Aimbot::Bone::Head;
int Options::Aimbot::iPrioritization = Options::Aimbot::Distance_To_Player;
bool Options::Aimbot::bTargetVisibleOnly = true;
bool Options::Aimbot::bAutoShoot = true;
bool Options::Aimbot::bAutoStop = true;
bool Options::Aimbot::bAutoCrouch = false;
int Options::Aimbot::iAimkey = VK_MENU;
bool Options::Aimbot::bAimstepEnabled = true;
float Options::Aimbot::flAimstepAngleChange = 18.0f;
bool Options::Aimbot::bAutoScope = true;
bool Options::Aimbot::bDisableWhenNoGunOut = true;
bool Options::Aimbot::bSilentRCS = false;
bool Options::Aimbot::bAutoAim = false;
bool Options::Aimbot::bDisableWhenReloading = true;
bool Options::Aimbot::bMultiAimspot = false;
bool Options::Aimbot::bGhettoAutowall = false;
float Options::Aimbot::flGhettoAutowallModifier = 65.0f;

bool Options::AntiAim::bEnabled = false;
bool Options::AntiAim::bFakeAnglesEnabled = false;
bool Options::AntiAim::bShowAngles = false;
int Options::AntiAim::iPitchAntiAimMode = Options::AntiAim::Pitch::Down;
int Options::AntiAim::iYawAntiAimMode = Options::AntiAim::Yaw::BackJitter;
int Options::AntiAim::iFakePitchAntiAimMode = Options::AntiAim::Pitch::Up;
int Options::AntiAim::iFakeYawAntiAimMode = Options::AntiAim::Yaw::Fukkireta;

bool Options::Resolver::bEnabled = false;
bool Options::Resolver::bBodyAimUnresolvable = true;

bool Options::NetvarManager::bDumpDataTables = false;

bool Options::Config::bUseLoadedConfig = true;
std::string Options::Config::selectedConfig;
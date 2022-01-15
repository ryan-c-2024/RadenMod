#include "stdafx.h"
#include "Config.h"
#include <fstream>
#include <string>
#include "ConMsg.h"
#include <Windows.h>
#include "Cleanup.h" //for jebhook dll's handle
#include "json.h" //nlohmann's json library
#include "Options.h"
#include <memory>

// for convenience
using json = nlohmann::json;

std::string Config::Internal::m_configdir_path;
std::map<std::string, std::string> Config::m_availableConfigs;

/*

TODO: FINISH ADDING CONFIG SYSTEM

SLIDER BARS ARE FILLED BASED ON OLD POSITION WHEN CONFIG IS LOADED, NOT NEW ONE

*/

void Config::Init()
{
	char dll_full_path[MAX_PATH];
	GetModuleFileNameA(GMisc::hMyDll, dll_full_path, MAX_PATH); //get directory the jebhook dll is in so we can find the configs folder
	std::string path_string(dll_full_path);
	size_t backslash_index = path_string.find_last_of('\\'); //index of the last backslash in the path
	path_string = path_string.substr(0, backslash_index + 1); //remove the dll name from the string
	path_string += "configs\\"; //add the configs folder to the path
	Internal::m_configdir_path = path_string; //set internal path variable to char* (downcasted from const char*)

	RefreshConfigList(); //refresh list of configs when first initialized
}

void Config::RefreshConfigList()
{
	m_availableConfigs.clear();
	std::string generic_path = Internal::m_configdir_path;
	generic_path += "*.json"; //path has wildcard for any json file in config folder;

	WIN32_FIND_DATAA data;
	HANDLE find_handle = FindFirstFileA(generic_path.c_str(), &data); //look for files that are json in folder. 
	
	if (find_handle != INVALID_HANDLE_VALUE) //if a first file could be found, add to the map and look for more...
	{
		std::string filename(data.cFileName); // use string type to convert char array 
		Internal::AddFoundConfig(filename); // call addfoundconfig to add it to maps list

		bool result; //result from findnextfile
		do
		{
			result = FindNextFileA(find_handle, &data); //look for the file

			if (result) //if a valid next file was found
			{
				filename = data.cFileName; //reassign filename string to the new filename
				Internal::AddFoundConfig(filename);
			}
		} while (result); //keep looping as long as there are more valid config jsons in the directory
	}

	ConMsg con;
	con.Msg("Config list refreshed!\n"); //print path into console
}

void Config::Internal::AddFoundConfig(std::string& config_filename)
{
	std::string filename_with_type = config_filename; //get c_str of string temporary with .json ending on it
	size_t filetype_dot_index = config_filename.rfind('.'); //find '.' as in ".json"
	config_filename.erase(filetype_dot_index); //remove filetype ending of .json

	std::string heap_config_filename = std::string(config_filename); 

	m_availableConfigs[heap_config_filename] = filename_with_type; //add to map
}

void Config::SaveSelectedConfig()
{
	if (m_availableConfigs.size() == 0 || Options::Config::selectedConfig == "") return;

	SaveConfigAs(Options::Config::selectedConfig.c_str());

	ConMsg con;
	con.Msg("Selected config (%s) saved!\n", Options::Config::selectedConfig.c_str()); //print path into console
}

void Config::CreateConfigTemplate()
{
	std::string path_string = Internal::m_configdir_path;
	CreateDirectoryA(path_string.c_str(), NULL); //create the config dir in the dll's folder. Func fails if directory already exists.
	path_string += "newcfg.json"; //add the config file name and json extension to the path
	
	SaveConfigAs(path_string.c_str());

	ConMsg con;
	con.Msg("New config template with path %s created!\n", path_string.c_str()); //print path into console
}

void Config::SaveConfigAs(const char* config_filename)
{
	std::fstream file;
	file.open(config_filename, std::fstream::out); //open the config file path for writing
	json cfg; //the config will be stored in json format. json library used for this.

			  //Set all the values in the template json to what the current settings are
	cfg["aimbot"]["enabled"] = Options::Aimbot::bEnabled;
	cfg["aimbot"]["smooth enabled"] = Options::Aimbot::bSmoothAim;
	cfg["aimbot"]["smooth factor"] = Options::Aimbot::flSmoothFactor;
	cfg["aimbot"]["aimstep enabled"] = Options::Aimbot::bAimstepEnabled;
	cfg["aimbot"]["aimstep threshold"] = Options::Aimbot::flAimstepAngleChange;
	cfg["aimbot"]["rcs enabled"] = Options::Aimbot::bControlRecoil;
	cfg["aimbot"]["rcs factor"] = Options::Aimbot::flRecoilControlFactor;
	cfg["aimbot"]["target team"] = Options::Aimbot::bTargetTeam;
	cfg["aimbot"]["target enemy"] = Options::Aimbot::bTargetEnemy;
	cfg["aimbot"]["silent aim enabled"] = Options::Aimbot::bSilentAimEnabled;
	cfg["aimbot"]["autoaim enabled"] = Options::Aimbot::bAutoAim;
	cfg["aimbot"]["autoshoot enabled"] = Options::Aimbot::bAutoShoot;
	cfg["aimbot"]["autostop enabled"] = Options::Aimbot::bAutoStop;
	cfg["aimbot"]["autocrouch enabled"] = Options::Aimbot::bAutoCrouch;
	cfg["aimbot"]["target bone"] = Options::Aimbot::iTargetBone;
	cfg["aimbot"]["aimkey"] = Options::Aimbot::iAimkey;
	cfg["aimbot"]["multi-aimspot enabled"] = Options::Aimbot::bMultiAimspot;
	cfg["aimbot"]["vischeck enabled"] = Options::Aimbot::bTargetVisibleOnly;
	cfg["aimbot"]["target prioritization"] = Options::Aimbot::iPrioritization;
	cfg["aimbot"]["autoscope enabled"] = Options::Aimbot::bAutoScope;
	cfg["aimbot"]["gun only enabled"] = Options::Aimbot::bDisableWhenNoGunOut;
	cfg["aimbot"]["off when reloading"] = Options::Aimbot::bDisableWhenReloading;
	cfg["aimbot"]["ghetto autowall enabled"] = Options::Aimbot::bGhettoAutowall;
	cfg["aimbot"]["ghetto autowall modifier"] = Options::Aimbot::flGhettoAutowallModifier;

	cfg["esp"]["esp enabled"] = Options::Esp::bEnabled;
	cfg["esp"]["draw team"] = Options::Esp::bDrawTeam;
	cfg["esp"]["draw enemies"] = Options::Esp::bDrawEnemy;
	cfg["esp"]["armor bar enabled"] = Options::Esp::bDrawArmorBar;
	cfg["esp"]["health bar enabled"] = Options::Esp::bDrawHealthBar;
	cfg["esp"]["2d box esp enabled"] = Options::Esp::bDrawBoxEsp;
	cfg["esp"]["name esp"] = Options::Esp::bNameEsp;
	cfg["esp"]["weapon esp"] = Options::Esp::bWeaponEsp;
	cfg["esp"]["health-based hp bar"] = Options::Esp::bHealthBasedColoring;

	cfg["visuals"]["disable scope visual"] = Options::Visual::bDisableScopeVisual;

	cfg["misc"]["flash reduction enabled"] = Options::Misc::bChangeFlashAlphaEnabled;
	cfg["misc"]["flash alpha"] = Options::Misc::flNewFlashAlpha;
	cfg["misc"]["basic chatspam enabled"] = Options::Misc::bChatSpamEnabled;
	cfg["misc"]["position spam"]["enabled"] = Options::ChatSpamPositions::bEnabled;
	cfg["misc"]["position spam"]["callout team positions"] = Options::ChatSpamPositions::bCalloutTeam;
	cfg["misc"]["position spam"]["callout enemy positions"] = Options::ChatSpamPositions::bCalloutEnemy;

	cfg["bunnyhop"]["autobhop enabled"] = Options::Bunnyhop::bEnabled;
	cfg["bunnyhop"]["autostrafer enabled"] = Options::Bunnyhop::bAutoStrafeEnabled;
	cfg["bunnyhop"]["autostrafer silent strafes"] = Options::Bunnyhop::bSilentStrafe;

	cfg["griefing"]["goomba stomp enabled"] = Options::GoombaStomp::bEnabled;

	cfg["hvh"]["antiaim"]["enabled"] = Options::AntiAim::bEnabled;
	cfg["hvh"]["antiaim"]["yaw type"] = Options::AntiAim::iYawAntiAimMode;
	cfg["hvh"]["antiaim"]["pitch type"] = Options::AntiAim::iPitchAntiAimMode;
	cfg["hvh"]["antiaim"]["show antiaim angles"] = Options::AntiAim::bShowAngles;
	cfg["hvh"]["resolver"]["enabled"] = Options::Resolver::bEnabled;
	cfg["hvh"]["resolver"]["bodyaim unresolvable"] = Options::Resolver::bBodyAimUnresolvable;

	file << std::setw(4) << cfg;
	file.close();
}

void Config::LoadSelectedConfig()
{
	if (m_availableConfigs.size() == 0 || Options::Config::selectedConfig == "") return;

	LoadConfig(Options::Config::selectedConfig.c_str()); //load the selected config

	ConMsg con;
	con.Msg("Selected config (%s) loaded!\n", Options::Config::selectedConfig.c_str()); //print path into console
}

void Config::LoadConfig(const char* config_filename)
{
	std::fstream file;
	file.open(config_filename, std::fstream::in); //open the config file path for writing
	json cfg; //the config will be stored in json format. json library used for this.
	file >> cfg; //give cfg the values from the config file

	Options::Aimbot::bEnabled = cfg["aimbot"]["enabled"];
	Options::Aimbot::bSmoothAim = cfg["aimbot"]["smooth enabled"];
	Options::Aimbot::flSmoothFactor = cfg["aimbot"]["smooth factor"];
	Options::Aimbot::bAimstepEnabled = cfg["aimbot"]["aimstep enabled"];
	Options::Aimbot::flAimstepAngleChange = cfg["aimbot"]["aimstep threshold"];
	Options::Aimbot::bControlRecoil = cfg["aimbot"]["rcs enabled"];
	Options::Aimbot::flRecoilControlFactor = cfg["aimbot"]["rcs factor"];
	Options::Aimbot::bTargetTeam = cfg["aimbot"]["target team"];
	Options::Aimbot::bTargetEnemy = cfg["aimbot"]["target enemy"];
	Options::Aimbot::bSilentAimEnabled = cfg["aimbot"]["silent aim enabled"];
	Options::Aimbot::bAutoAim = cfg["aimbot"]["autoaim enabled"];
	Options::Aimbot::bAutoShoot = cfg["aimbot"]["autoshoot enabled"];
	Options::Aimbot::bAutoStop = cfg["aimbot"]["autostop enabled"];
	Options::Aimbot::bAutoCrouch = cfg["aimbot"]["autocrouch enabled"];
	Options::Aimbot::iTargetBone = cfg["aimbot"]["target bone"];
	Options::Aimbot::iAimkey = cfg["aimbot"]["aimkey"];
	Options::Aimbot::bMultiAimspot = cfg["aimbot"]["multi-aimspot enabled"];
	Options::Aimbot::bTargetVisibleOnly = cfg["aimbot"]["vischeck enabled"];
	Options::Aimbot::iPrioritization = cfg["aimbot"]["target prioritization"];
	Options::Aimbot::bAutoScope = cfg["aimbot"]["autoscope enabled"];
	Options::Aimbot::bDisableWhenNoGunOut = cfg["aimbot"]["gun only enabled"];
	Options::Aimbot::bDisableWhenReloading = cfg["aimbot"]["off when reloading"];
	Options::Aimbot::bGhettoAutowall = cfg["aimbot"]["ghetto autowall enabled"];
	Options::Aimbot::flGhettoAutowallModifier = cfg["aimbot"]["ghetto autowall modifier"];

	Options::Esp::bEnabled = cfg["esp"]["esp enabled"];
	Options::Esp::bDrawTeam = cfg["esp"]["draw team"];
	Options::Esp::bDrawEnemy = cfg["esp"]["draw enemies"];
	Options::Esp::bDrawArmorBar = cfg["esp"]["armor bar enabled"];
	Options::Esp::bDrawHealthBar = cfg["esp"]["health bar enabled"];
	Options::Esp::bDrawBoxEsp = cfg["esp"]["2d box esp enabled"];
	Options::Esp::bNameEsp = cfg["esp"]["name esp"];
	Options::Esp::bWeaponEsp = cfg["esp"]["weapon esp"];
	Options::Esp::bHealthBasedColoring = cfg["esp"]["health-based hp bar"];
	Options::Visual::bDisableScopeVisual = cfg["visuals"]["disable scope visual"];
	Options::Misc::bChangeFlashAlphaEnabled = cfg["misc"]["flash reduction enabled"];
	Options::Misc::flNewFlashAlpha = cfg["misc"]["flash alpha"];
	Options::Misc::bChatSpamEnabled = cfg["misc"]["basic chatspam enabled"];
	Options::ChatSpamPositions::bEnabled = cfg["misc"]["position spam"]["callout team positions"];
	Options::ChatSpamPositions::bCalloutTeam = cfg["misc"]["position spam"]["enabled"];
	Options::ChatSpamPositions::bCalloutEnemy = cfg["misc"]["position spam"]["callout enemy positions"];
	Options::Bunnyhop::bEnabled = cfg["bunnyhop"]["autobhop enabled"];
	Options::Bunnyhop::bAutoStrafeEnabled = cfg["bunnyhop"]["autostrafer enabled"];
	Options::Bunnyhop::bSilentStrafe = cfg["bunnyhop"]["autostrafer silent strafes"];
	Options::GoombaStomp::bEnabled = cfg["griefing"]["goomba stomp enabled"];
	Options::AntiAim::bEnabled = cfg["hvh"]["antiaim"]["enabled"];
	Options::AntiAim::iYawAntiAimMode = cfg["hvh"]["antiaim"]["yaw type"];
	Options::AntiAim::iPitchAntiAimMode = cfg["hvh"]["antiaim"]["pitch type"];
	Options::AntiAim::bShowAngles = cfg["hvh"]["antiaim"]["show antiaim angles"];
	Options::Resolver::bEnabled = cfg["hvh"]["resolver"]["enabled"];
	Options::Resolver::bBodyAimUnresolvable = cfg["hvh"]["resolver"]["bodyaim unresolvable"];

	file.close();
}

/*
CConfig::CConfig(const char* configName)
{
/*
char dll_full_path[MAX_PATH];
GetModuleFileNameA(GMisc::hMyDll, dll_full_path, MAX_PATH); //get directory the jebhook dll is in so we can find the configs folder
std::string path_string(dll_full_path);
size_t backslash_index = path_string.find_last_of('\\'); //index of the last backslash in the path
path_string.erase(backslash_index + 1); //remove from the dll name from the string
m_dll_dir_path = path_string.c_str(); //set m_dll_dir_path to this

if (!DoesConfigExist(configName))
{
CreateConfigTemplate();
}
else
{
LoadConfig(configName);
}


}

bool CConfig::DoesConfigExist(const char* configFileName)
{
	std::string config_path(m_dll_dir_path);
	config_path += "configs\\";
	CreateDirectoryA(config_path.c_str(), NULL); //create directory. if it already exists the func will fail so it doesn't matter
	config_path += configFileName;
	config_path.append(".json"); //add the json type extension in

	WIN32_FIND_DATAA data;
	HANDLE retn = FindFirstFileA(config_path.c_str(), &data); //look for the file
	if (retn == INVALID_HANDLE_VALUE) //if the FindFirstFile failed or couldn't find the file
	{
		return false; //this likely means config doesn't exist
	}

	return true;
}
*/

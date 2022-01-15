#pragma once
#include <map>
#include <string>

//this could be a class but I don't need the instance and I need to be able to easily get the address of member functions
namespace Config
{
	//set up internals and refresh config list
	void Init();

	//create a new template with the currently active settings in it	
	void CreateConfigTemplate();

	//load specified config
	void LoadConfig(const char* config_filename);

	//load the config that is selected. Wrapper around LoadConfig
	void LoadSelectedConfig();

	//refresh the available configs map
	void RefreshConfigList();

	//save selected config and overwrites old one
	void SaveSelectedConfig();

	//save config as json with the specified name
	void SaveConfigAs(const char* config_filename);

	//note: key has no .json extension on it and value does
	extern std::map<std::string, std::string> m_availableConfigs;

	//pseudo-encapsulation
	namespace Internal
	{
		void AddFoundConfig(std::string& config_filename);
		extern std::string m_configdir_path;
	}
};
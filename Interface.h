#pragma once
#include <string>

class CInterface
{
public:
	void Init();
private:

	void* GetInterface(const char* interfacename, LPCSTR modulename)
	{
			typedef void* (*CreateInterfaceFn) (const char*, bool);
			CreateInterfaceFn CreateInterface = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(GetModuleHandleA(modulename), "CreateInterface"));

			return CreateInterface(interfacename, 0);
	}
	
	template <typename T>
	T GetInterfaceAndVersion(std::string interfaceName, LPCSTR moduleName)
	{
		int iVersionNumber = 0;
		std::string interfaceGuess = interfaceName;
		T interfaceAddress = 0;

		while (!(interfaceAddress = reinterpret_cast<T>(GetInterface(interfaceGuess.c_str(), moduleName))))
		{
			iVersionNumber++;
			if (iVersionNumber <= 9)
			{
				interfaceGuess = interfaceName + "00" + std::to_string(iVersionNumber);
			}
			else
			{
				interfaceGuess = interfaceName + "0" + std::to_string(iVersionNumber);
			}

			if (iVersionNumber > 999)
			{
				std::string exceptionString = interfaceName + " in " + moduleName + " could not be grabbed.";
				throw exceptionString;
			}
		} 

		return interfaceAddress;
	}
};

namespace GMisc
{
	extern CInterface iface;
}
 
// dllmain.cpp : Defines the entry point for the DLL application.
//Jeb Platinum: Most up to date version
#include "stdafx.h"
#include "Interface.h"
#include "HookManager.h"
#include "Cleanup.h"
#include "Offsets.h"
#include "DrawAssist.h"
#include "CMenu.h"
#include "Security.h"	
#include "Config.h"

int main()
{
	Security initCheck;
	initCheck.RunCheck();
	GMisc::iface.Init();
	GMisc::offset.SetupOffsets();
	DrawAssist::SetupFonts();
	HookManager::InitHooks();
	GMisc::menu = std::make_unique<CMenu>();
	Config::Init();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		GMisc::hMyDll = hModule;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&main, 0, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


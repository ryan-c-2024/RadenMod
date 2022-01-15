#include "stdafx.h"
#include "Cleanup.h"
#include "HookManager.h"
#include "ConMsg.h"
#include "CUserCmd.h"
#include "Global Hooks.h"
#include "CBasePlayer.h"
#include <exception>

HMODULE GMisc::hMyDll = 0;

void Cleanup()
{
	try
	{
		GPtr::pLocalPlayer->SetSendPacket(true);
		Misc::con.Msg("\n\n\nDLL EJECTING...\n\n\n");
		IFace::engineclient->ClientCmd("cl_mouseenable 1"); //just in case menu was open when uninjecting
		HookManager::Reset();
		FreeLibraryAndExitThread(GMisc::hMyDll, 0);
	}
	catch (const std::exception& exc)
	{
		if (IFace::engineclient)
		{
			IFace::engineclient->Con_NPrintf(1, "ERROR WHEN UNINJECTING: %s", exc);
		}
	}
	catch (...)
	{
		if (IFace::engineclient)
		{
			IFace::engineclient->Con_NPrintf(1, "ERROR WHEN UNINJECTING");
		}
	}
}
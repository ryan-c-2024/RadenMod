#include "stdafx.h"
#include "HookedFunctions.h"
#include "Global Hooks.h"
#include "Global Interfaces.h"
#include "Cleanup.h"
#include "Visuals.h"
#include "Options.h"
#include "CVisuals.h"

typedef void(__thiscall* PaintTraverseFn) (void*, VPANEL, bool, bool);

void __fastcall HookedFunc::PaintTraverse(void* pThis, void* EDX, VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
	static bool bEject = false;

	static VPANEL targetPanel = 0; //Saves desired panel's VPANEL value once it is found
	static VPANEL scopePanel = 0;
	
	if (!bEject && (GetAsyncKeyState(VK_END) & 0x8000)) //Eject dll
	{
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Cleanup), 0, 0, 0);
		bEject = true;
	}

	if (Options::Visual::bDisableScopeVisual && vguiPanel == scopePanel) //if the current panel is the unwanted one exit so it doesn't draw
	{
		return;
	}
	
	GHook::panel->CallOriginalFunc<PaintTraverseFn>(41)(pThis, vguiPanel, forceRepaint, allowForce);  //Call original paint traverse so HUD etc. aren't messed up

	if (!targetPanel) //If the drawing panel below hasn't been found run this and see if the current panel is it
	{
		if (!strcmp(IFace::panel->GetName(vguiPanel), "FocusOverlayPanel"))
		{
			targetPanel = vguiPanel;
		}
	}
	else if (vguiPanel == targetPanel) //if the panel has been found, do whatever
	{
		try
		{
			Visuals::Run();
		}
		catch (const std::exception& exc)
		{
			if (IFace::engineclient)
			{
				//IFace::engineclient->Con_NPrintf(1, "ISSUE IN PAINTTRAVERSE: %s", exc.what());
			}
		}
		catch (...)
		{
			if (IFace::engineclient)
			{
				//IFace::engineclient->Con_NPrintf(1, "ISSUE IN PAINTTRAVERSE");
			}
		}
	}

	if (!scopePanel) //if unwanted panel is found save its VPANEL
	{
		const char* szPanelName = IFace::panel->GetName(vguiPanel);
		if (!strcmp(szPanelName, "HudZoom"))
		{
			scopePanel = vguiPanel;
		}
	}
	
}
#include "stdafx.h"
#include "Visuals.h"
#include "CEsp.h"
#include "DrawAssist.h"
#include "Color.h"
#include "Options.h"
#include "CMenu.h"
#include "CVisuals.h"
#include "Global Interfaces.h"
#include "CBasePlayer.h"

void Visuals::Run()
{
	if (IFace::engineclient->IsInGame())
	{
		GMisc::esp.Run();
		Visuals::DrawScopeCrosshairs();
	}
	GMisc::menu->DrawAll();
	DisplayWatermark();
	
}

void Visuals::DisplayWatermark()
{
	DrawAssist::DrawString("Owned By Chige's Jebhook - V1.1975 Beta", Fonts::fontWatermark, Color(255, 255, 255, 255), 5, 5);
}

void Visuals::DrawScopeCrosshairs()
{
	if (!Options::Visual::bDisableScopeVisual || !GPtr::pLocalPlayer->IsScoped() || !GPtr::pLocalPlayer->UsingScopeWeapon() ||
		!IFace::engineclient->IsInGame())
		return;

	static int screenX, screenY;
	IFace::engineclient->GetScreenSize(screenX, screenY);
	DrawAssist::DrawLine(Color(0, 0, 0, 255), 0, screenY / 2, screenX, screenY / 2); //horizontal crosshair line
	DrawAssist::DrawLine(Color(0, 0, 0, 255), screenX / 2, 0, screenX / 2, screenY); //vertical crosshair line
}
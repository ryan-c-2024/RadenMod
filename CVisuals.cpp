#include "stdafx.h"
#include "CVisuals.h"
#include "Options.h"
#include "DrawAssist.h"
#include "Global Interfaces.h"
#include "CBasePlayer.h"

CVisuals GMisc::visualmisc;

void CVisuals::RunAll()
{

}

void CVisuals::DrawScopeCrosshairs()
{
	if (!Options::Visual::bDisableScopeVisual || !GPtr::pLocalPlayer->IsScoped())
		return;

	static int screenX = 0, screenY = 0;
	if (!screenX || !screenY)
	{
		IFace::engineclient->GetScreenSize(screenX, screenY);
	}
	DrawAssist::DrawLine(Color(0, 0, 0, 255), 1, screenY / 2, screenX - 1, screenY / 2);
	DrawAssist::DrawLine(Color(0, 0, 0, 255), screenX / 2, 1, screenX / 2, screenY - 1); //doesnt work
}
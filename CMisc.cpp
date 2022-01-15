#include "stdafx.h"
#include "CMisc.h"
#include "Global Interfaces.h"
#include "Options.h"
#include <string>
#include "player_info.h"
#include "CBaseCombatWeapon.h"
#include "CBasePlayer.h"
#include "Recv.h"

/*

TODO: ONCE NETVAR PROXYING IMPLEMENTED, PROXY FLASH ALPHA AND CHANGE IT THERE SO IT IS MORE EFFICIENT

right now changeflashalpha is implemented but doesn't seem to be working
*/

void CMisc::RunAllMisc()
{
	ChatSpamPositions();
	ChatSpamJebhook();
	DoSlowFall(); //changing sendpacket in game crashes the game
	DoFakeLag();
}

void CMisc::ChangeFlashAlpha(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
	float alpha; 
	if (Options::Misc::bChangeFlashAlphaEnabled)
	{
		alpha = Options::Misc::flNewFlashAlpha; //when alpha gets reset by the game, make it this
	}
	else
	{
		alpha = 255.0f; //if flash reducer disabled, make it default
	}

	*(float*)pOut = alpha;
}

void CMisc::ChatSpamPositions()
{
	if (!Options::ChatSpamPositions::bEnabled)
		return;

	if (!IFace::engineclient->IsInGame())
		return;

	static float OldTime = 0;
	float currenttime = IFace::engineclient->GetLastTimeStamp();

	if (OldTime > currenttime)
	{
		OldTime = 0;
	}

	if ((currenttime - OldTime) < 0.8)
		return;

	static int iNextID = 1;

	for (int i = iNextID, iMaxClients = IFace::engineclient->GetMaxClients(); i < iMaxClients; i++)
	{
		
		iNextID++;

		if (iNextID >= iMaxClients)
			iNextID = 1;

		CBasePlayer* pEnt = IFace::entitylist->GetClientEntity(i);

		if (!pEnt || pEnt->IsDormant() || pEnt->IsLocalPlayer() || !pEnt->IsAlive())
			continue;

		bool bOnLocalPlayerTeam = pEnt->IsOnLocalPlayerTeam();

		if (!Options::ChatSpamPositions::bCalloutEnemy && !bOnLocalPlayerTeam)
			continue;
		if (!Options::ChatSpamPositions::bCalloutTeam && bOnLocalPlayerTeam)
			continue;

		std::string strLocation = pEnt->GetLastPlaceName(); //crash at getlastplacename or it returns 0. dereferencing const char** doesnt work either
		player_info_s playerinfo;
		IFace::engineclient->GetPlayerInfo(i, &playerinfo);

		std::string szSayString;
		if (Options::ChatSpamPositions::bUseTeamChat)
		{
			szSayString = "say_team \"";
		}
		else
		{
			szSayString = "say \"";
		}
		szSayString += std::string(playerinfo.name) + " is at: " + strLocation;
		szSayString += ", with " + std::to_string(pEnt->GetHealth()) + "HP, ";
		szSayString += "and has $" + std::to_string(pEnt->GetCurrentMoney());
		szSayString += " and a " + pEnt->GetWeapon()->GetWeaponName();
		szSayString += "\"";

		IFace::engineclient->ClientCmd(szSayString.c_str());
		break;
	}

	OldTime = IFace::engineclient->GetLastTimeStamp();
}

void CMisc::ChatSpamJebhook()
{
	if (!Options::Misc::bChatSpamEnabled)
		return;
	static float OldTime = 0;
	float currenttime = IFace::engineclient->GetLastTimeStamp();

	if (OldTime > currenttime)
	{
		OldTime = 0;
	}

	if ((currenttime - OldTime) < 0.8)
		return;

	IFace::engineclient->ClientCmd("say JEBHOOKOFFICIAL.GITHUB.IO | PREMIUM CHEATS | FAIR PRICE | GET YOUR FRAG ON ");

	OldTime = IFace::engineclient->GetLastTimeStamp();
}

inline void CMisc::DoSlowFall()
{
	if (!Options::Misc::bSlowFall)
		return;
	if (GetAsyncKeyState('V') & 0x8000)
	{
		GPtr::pLocalPlayer->SetSendPacket(false);
	}
	else
	{
		GPtr::pLocalPlayer->SetSendPacket(true);
	}
}

void CMisc::DoFakeLag()
{
	if (!Options::Misc::bFakeLag)
	{
		GPtr::pLocalPlayer->SetSendPacket(true);
		return;
	}

	static int tick = 0;
	if (tick >= Options::Misc::iFakeLagChokedTicks)
	{
		GPtr::pLocalPlayer->SetSendPacket(true);
		tick = 0;
	}
	else if (tick < Options::Misc::iFakeLagChokedTicks)
	{
		GPtr::pLocalPlayer->SetSendPacket(false);
	}
	tick++;
}

CMisc GMisc::misc;
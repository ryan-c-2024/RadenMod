#include "stdafx.h"
#include "CEsp.h"
#include "VMatrix.h"
#include "Global Interfaces.h"
#include "Options.h"
#include "DrawAssist.h"
#include "EspMath.h"
#include "player_info.h"
#include "CBaseCombatWeapon.h"
#include "KeyToggle.h"
#include "CBasePlayer.h"

CEsp GMisc::esp;


/*
TODO: FOR ESP:

3D BOX ESP (OUTLINE CHANGES TO REFLECT HP)
GLOW ESP

*/

void CEsp::Run()
{
	try
	{
		static KeyToggle espToggle;
		espToggle.KeyPressToggle(VK_HOME, Options::Esp::bEnabled);

		if (!Options::Esp::bEnabled)
			return;

		FindEntities();
	}
	catch (const std::exception& exc)
	{
		if (IFace::engineclient)
		{
			//IFace::engineclient->Con_NPrintf(1, "ISSUE IN ESP: %s", exc.what());
		}
	}
	
}

void CEsp::FindEntities()
{
	for (int i = 1; i < IFace::engineclient->GetMaxClients(); i++)
	{
		m_pEntity = IFace::entitylist->GetClientEntity(i);

		if (!ShouldDrawEntity()) //crashes in shoulddrawentity sometimes
			continue;

		CalculateEsp();
		DrawEsp();
	}
}

bool CEsp::ShouldDrawEntity()
{
	if (!m_pEntity)
		return false;
	if (!GPtr::pLocalPlayer)
		return false;
	if (m_pEntity->IsDormant() || !m_pEntity->IsAlive() || m_pEntity->IsLocalPlayer())
		return false;
	if (GPtr::pLocalPlayer->GetObserverTarget() == m_pEntity)
		return false;
	m_bOnLocalPlayerTeam = m_pEntity->IsOnLocalPlayerTeam();

	if (!Options::Esp::bDrawTeam && m_bOnLocalPlayerTeam)
		return false;
	if (!Options::Esp::bDrawEnemy && !m_bOnLocalPlayerTeam)
		return false;
	
	return true;
}

inline void CEsp::CalculateEsp()
{
	EspMath::WorldToScreen(m_pEntity->GetOrigin(), m_vecTargetOrigin);
	EspMath::WorldToScreen(m_pEntity->GetCurrentEyePosition(), m_vecTargetTop);

	m_flTargetHeight = m_vecTargetOrigin.y - m_vecTargetTop.y;
	m_flTargetWidth = m_flTargetHeight / 3;
}

void CEsp::DrawEsp()
{
	m_iNumTextEsps = 0;

	if (m_bOnLocalPlayerTeam)
	{
		DrawBoxEsp(Color(50, 150, 255, 255));
		DrawHealthBar();
		DrawArmorBar();
		DisplayBonePositions();
		DrawNameEsp();
		DrawWeaponEsp();
	}
	else if (!m_bOnLocalPlayerTeam)
	{
		DrawBoxEsp(Color(255, 0, 0, 255));
		DrawHealthBar();
		DrawArmorBar();
		DisplayBonePositions();
		DrawNameEsp();
		DrawWeaponEsp();
	}
}

inline void CEsp::DrawBoxEsp(Color& boxcolor)
{
	if (!Options::Esp::bDrawBoxEsp)
		return;

	DrawAssist::DrawOutlinedRect(boxcolor, m_vecTargetTop.x - m_flTargetWidth, m_vecTargetTop.y - (m_flTargetHeight * 0.2), m_vecTargetTop.x + m_flTargetWidth, m_vecTargetTop.y + m_flTargetHeight);
	DrawAssist::DrawOutlinedRect(Color(0, 0, 0, 255), m_vecTargetTop.x - m_flTargetWidth - 1, m_vecTargetTop.y - (m_flTargetHeight * 0.2) - 1, m_vecTargetTop.x + m_flTargetWidth + 1, m_vecTargetTop.y + m_flTargetHeight + 1);
	DrawAssist::DrawOutlinedRect(Color(0, 0, 0, 255), m_vecTargetTop.x - m_flTargetWidth + 1, m_vecTargetTop.y - (m_flTargetHeight * 0.2) + 1, m_vecTargetTop.x + m_flTargetWidth - 1, m_vecTargetTop.y + m_flTargetHeight - 1);
}

void CEsp::DrawHealthBar()
{
	if (!Options::Esp::bDrawHealthBar)
		return;

	int entity_health = m_pEntity->GetHealth();
	float health_factor = entity_health / 100.0f;
	float inverse_health_factor = 1.0f - health_factor;

	float bar_left = m_vecTargetTop.x - (m_flTargetWidth * 1.2);
	float bar_right = m_vecTargetTop.x - (m_flTargetWidth * 1);
	float bar_top = m_vecTargetTop.y - (m_flTargetHeight * 0.2); //black border top
	float bar_height = m_vecTargetOrigin.y - bar_top;
	float bar_bottom = m_vecTargetOrigin.y;
	
	//Color(21, 178, 55, 255)
	DrawAssist::DrawOutlinedRect(Color(0, 0, 0, 255), bar_left, bar_top, bar_right, bar_bottom);
	DrawAssist::DrawFilledRect((Options::Esp::bHealthBasedColoring) ? GetHealthColor(entity_health) : Color(21, 178, 55, 255), bar_left + 1, bar_top + (inverse_health_factor * bar_height) + 1, bar_right - 1, bar_bottom - 1); //green hp bar filling
	DrawAssist::DrawFilledRect(Color(30, 30, 30, 180), bar_left + 1, bar_top + 1, bar_right - 1, bar_top + (inverse_health_factor * bar_height) + 1); //grey part to fill in part of bar
}

void CEsp::DrawArmorBar()
{
	if (!Options::Esp::bDrawArmorBar)
		return;

	float flArmorFactor = m_pEntity->GetArmor() / 100.0f;
	float flInverseArmorFactor = 1.0f - flArmorFactor;

	if (flInverseArmorFactor >= 1.0) //if no armor don't display bar
		return;

	float barLeft = m_vecTargetTop.x - (m_flTargetWidth * 1.3);
	float barRight = m_vecTargetTop.x - (m_flTargetWidth * 1.21);
	float barTop = m_vecTargetTop.y;
	float colorBarTop = m_vecTargetTop.y + (flInverseArmorFactor * m_flTargetHeight);
	float barBottom = m_vecTargetTop.y + m_flTargetHeight; //colored armor bar top

	Color barColor;

	bool bHasHelmet = m_pEntity->HasHelmet();

	if (bHasHelmet)
	{
		barColor = Color(0, 203, 255, 255);
	}
	else
	{
		barColor = Color(0, 43, 186, 255);
	}

	DrawAssist::DrawOutlinedRect(Color(0, 0, 0, 255), barLeft, barTop, barRight, barBottom);
	DrawAssist::DrawFilledRect(barColor, barLeft + 1, colorBarTop + 1, barRight - 1, barBottom - 1);
	DrawAssist::DrawFilledRect(Color(30, 30, 30, 180), barLeft + 1, barTop + 1, barRight - 1, m_vecTargetTop.y + (flInverseArmorFactor * m_flTargetHeight) + 1);
}

void CEsp::DisplayBonePositions()
{
	//absolutely destroys FPS
	if (!Options::Esp::bDrawBonePos)
		return;

	for (int i = 0; i < MAXSTUDIOBONES; i++)
	{
		static Vector vecBonePos;
		static Vector vecScreenBonePos;
		vecBonePos = m_pEntity->GetBonePosition(i);
		EspMath::WorldToScreen(vecBonePos, vecScreenBonePos);
		std::string szToPrint = "Bone" + std::to_string(i);
		DrawAssist::DrawString(szToPrint.c_str(), Fonts::fontEsp, Color(255, 255, 255, 255), vecScreenBonePos.x, vecScreenBonePos.y);
	}
}

void CEsp::DrawNameEsp()
{
	if (!Options::Esp::bNameEsp)
		return;

	player_info_t playerInfo;
	IFace::engineclient->GetPlayerInfo(m_pEntity->GetIndex(), &playerInfo);
	DrawAssist::DrawString(playerInfo.name, Fonts::fontEsp, Color(255, 255, 255, 255), m_vecTargetTop.x - m_flTargetWidth, m_vecTargetTop.y + m_flTargetHeight + (13 * m_iNumTextEsps));
	m_iNumTextEsps++;
}

void CEsp::DrawWeaponEsp() //I believe this is causing the crash
{
	if (!Options::Esp::bWeaponEsp)
		return;
	try
	{
		DrawAssist::DrawString(m_pEntity->GetWeapon()->GetWeaponName().c_str(), Fonts::fontEsp, Color(255, 255, 255, 255), m_vecTargetTop.x - m_flTargetWidth, m_vecTargetTop.y + m_flTargetHeight + (13 * m_iNumTextEsps));
		m_iNumTextEsps++;
	}
	catch (const std::bad_alloc& exc)
	{
		//IFace::engineclient->Con_NPrintf(1, "ISSUE IN WEAPON ESP: std::bad_alloc", exc.what());
	}
	catch (const std::exception& exc)
	{
		//IFace::engineclient->Con_NPrintf(1, "ISSUE IN WEAPON ESP: %s", exc.what());
	}
}

Color CEsp::GetHealthColor(int health)
{
	if (health >= 100)
	{
		return Color(21, 178, 55, 255);
	}
	else if (health < 100 && health >= 70)
	{
		return Color(0, 117, 25, 255);
	}
	else if (health < 70 && health >= 30)
	{
		return Color(209, 217, 59, 255);
	}
	else if (health < 30)
	{
		return Color(191, 19, 19, 255);
	}
}
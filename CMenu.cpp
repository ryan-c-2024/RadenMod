#include "stdafx.h"
#include "Global Interfaces.h"
#include "KeyToggle.h"
#include "Options.h"
#include "CMenu.h"
#include "MenuSkeleton.h"
#include <memory>
//Color(40, 132, 55, 220);
//http://paletton.com/palette.php?uid=12R0-0kllllaFw0g0qFqFg0w0aF

/*

TODO: Add section in menu to customize menu colors (rgb sliders)
Add config tab
Add buttons (execute function pointer on click)

*/

void CMenu::DrawAll()
{
	//Toggling menu and cursor visibility:
	static bool shouldDrawMenu = false;
	static KeyToggle menuToggle;
	menuToggle.KeyPressToggle(VK_INSERT, shouldDrawMenu);

	static bool mouseVisible = false;
	if (!shouldDrawMenu && mouseVisible)
	{
		IFace::engineclient->ClientCmd("cl_mouseenable 1");
		mouseVisible = false;
	}
	if (!shouldDrawMenu)
	{
		return;
	}

	//Here is where they actually get drawn:
	m_mainBody.Draw();
	m_tabManager.DrawTabs();

	//cursor visibility:
	if (!IFace::engineclient->IsInGame())
		return;
	else if (shouldDrawMenu && !mouseVisible)
	{
		IFace::engineclient->ClientCmd("cl_mouseenable 0");
		mouseVisible = true;
	}
	IFace::baseclient->IN_DeactivateMouse();
}

CMenu::CMenu() : m_mainBody(MainBody(Color(2, 84, 0, 255), Color(0, 0, 0, 213), 360, 300, 1560, 940, "Jebhook Menu")), 
m_tabManager(Color(17, 115, 17, 255))
{ }

std::unique_ptr<CMenu> GMisc::menu = nullptr;
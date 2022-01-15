#pragma once
#include "MenuElements.h"
#include "MenuSkeleton.h"
#include <memory>

class TabManager;

class CMenu
{
public:
	void DrawAll();
	CMenu();
private:
	MainBody m_mainBody;
	TabManager m_tabManager;
};


namespace GMisc
{
	extern std::unique_ptr<CMenu> menu;
}
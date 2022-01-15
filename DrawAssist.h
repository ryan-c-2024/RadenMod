#pragma once
#include <string>

class Color;

namespace vgui
{
	typedef unsigned long HFont;
}


namespace DrawAssist
{
	void DrawFilledRect(Color& color, int x0, int y0, int x1, int y1);
	void DrawOutlinedRect(Color& color, int x0, int y0, int x1, int y1);
	void DrawLine(Color& color, int x0, int y0, int x1, int y1);
	void DrawString(const char* text, vgui::HFont& font, Color& color, int x, int y);
	inline void DrawString(std::string& text, vgui::HFont& font, Color& color, int x, int y)
	{
		DrawString(text.c_str(), font, color, x, y);
	}
	bool SetupFonts();
}

namespace Fonts
{
	extern vgui::HFont fontEsp;
	extern vgui::HFont fontWatermark;
	extern vgui::HFont fontMenu;
	extern vgui::HFont fontMenuTitle;
}

namespace GMisc
{
	extern float scaleFactor;
}
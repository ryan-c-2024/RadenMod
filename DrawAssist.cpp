#include "stdafx.h"
#include "DrawAssist.h"
#include "Global Interfaces.h"

vgui::HFont Fonts::fontEsp;
vgui::HFont Fonts::fontMenu;
vgui::HFont Fonts::fontWatermark;
vgui::HFont Fonts::fontMenuTitle;

float GMisc::scaleFactor = 1.0;

void DrawAssist::DrawFilledRect(Color& color, int x0, int y0, int x1, int y1)
{
	IFace::surface->DrawSetColor(color);
	IFace::surface->DrawFilledRect(x0, y0, x1, y1);
}

void DrawAssist::DrawOutlinedRect(Color& color, int x0, int y0, int x1, int y1)
{
	IFace::surface->DrawSetColor(color);
	IFace::surface->DrawOutlinedRect(x0, y0, x1, y1);
}

void DrawAssist::DrawLine(Color& color, int x0, int y0, int x1, int y1)
{
	IFace::surface->DrawSetColor(color);
	IFace::surface->DrawLine(x0, y0, x1, y1);
}

void DrawAssist::DrawString(const char* text, vgui::HFont& font, Color& color, int x, int y)
{
	std::string sTmp = (std::string)text; //converts const char* to std::string and then to std::wstring for DrawPrintText
	std::wstring wsTmp(sTmp.begin(), sTmp.end());

	IFace::surface->DrawSetTextFont(font);
	IFace::surface->DrawSetTextColor(color);
	IFace::surface->DrawSetTextPos(x, y);
	IFace::surface->DrawPrintText(wsTmp.c_str(), wcslen(wsTmp.c_str())); //prints with the const char* converted to wchar_t*
}

bool DrawAssist::SetupFonts()
{
	int screenX, screenY;
	IFace::engineclient->GetScreenSize(screenX, screenY);
	if (!screenX)
	{
		GMisc::scaleFactor = 1.0;
	}
	else
	{
		GMisc::scaleFactor = screenX / 1920;
	}
	//assuming that everyone is gonna be 1080p or more and 16:9 ratio
	IFace::surface->SetFontGlyphSet(Fonts::fontWatermark = IFace::surface->CreateNewFont(), "GothicE", 18 * GMisc::scaleFactor, 0, 0, 0, vgui::FONTFLAG_OUTLINE);
	IFace::surface->SetFontGlyphSet(Fonts::fontEsp = IFace::surface->CreateNewFont(), "Calibri", 14 * GMisc::scaleFactor, 0, 0, 0, vgui::FONTFLAG_OUTLINE);
	IFace::surface->SetFontGlyphSet(Fonts::fontMenu = IFace::surface->CreateNewFont(), "Arial", 16 * GMisc::scaleFactor, 0, 0, 0, vgui::FONTFLAG_ANTIALIAS);
	IFace::surface->SetFontGlyphSet(Fonts::fontMenuTitle = IFace::surface->CreateNewFont(), "GothicE", 40 * GMisc::scaleFactor, 0, 0, 0, vgui::FONTFLAG_ANTIALIAS);

	return true;
}


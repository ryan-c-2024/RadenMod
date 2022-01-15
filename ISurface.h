#pragma once
#include "Util.h"
#include "Color.h"
#include <string>

namespace vgui
{
	enum EFontFlags
	{
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
		FONTFLAG_ANTIALIAS = 0x010,
		FONTFLAG_GAUSSIANBLUR = 0x020,
		FONTFLAG_ROTARY = 0x040,
		FONTFLAG_DROPSHADOW = 0x080,
		FONTFLAG_ADDITIVE = 0x100,
		FONTFLAG_OUTLINE = 0x200,
		FONTFLAG_CUSTOM = 0x400,		// custom generated font - never fall back to asian compatibility mode
		FONTFLAG_BITMAP = 0x800,		// compiled bitmap font - no fallbacks
	};

	enum FontDrawType_t
	{
		// Use the "additive" value from the scheme file
		FONT_DRAW_DEFAULT = 0,

		// Overrides
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,

		FONT_DRAW_TYPE_COUNT = 2,
	};


	class IImage;
	class Image;
	class Point;

	// handles
	typedef unsigned long HCursor;
	typedef unsigned long HTexture;
	typedef unsigned long HFont;

	//-----------------------------------------------------------------------------
	// Purpose: Wraps contextless windows system functions
	//-----------------------------------------------------------------------------
	class ISurface
	{
	public:

		inline void DrawSetColor(Color& col)
		{
			typedef void(__thiscall* tFunc) (void*, Color);
			Util::CallVirtualFunction<tFunc>(this, 14)(this, col);
		}

		inline void DrawSetColor(int r, int g, int b, int a)
		{
			typedef void(__thiscall* tFunc) (void*, int, int, int, int);
			Util::CallVirtualFunction<tFunc>(this, 15)(this, r, g, b, a);
		}

		inline void DrawFilledRect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* tFunc) (void*, int, int, int, int);
			Util::CallVirtualFunction<tFunc>(this, 16)(this, x0, y0, x1, y1);
		}

		inline void DrawOutlinedRect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* tFunc) (void*, int, int, int, int);
			Util::CallVirtualFunction<tFunc>(this, 18)(this, x0, y0, x1, y1);
		}

		inline void DrawLine(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall* tFunc) (void*, int, int, int, int);
			Util::CallVirtualFunction<tFunc>(this, 19)(this, x0, y0, x1, y1);
		}

		inline void DrawSetTextFont(HFont& font)
		{
			typedef void(__thiscall* tFunc) (void*, HFont);
			Util::CallVirtualFunction<tFunc>(this, 23)(this, font);
		}

		inline void DrawSetTextColor(Color& col)
		{
			typedef void(__thiscall* tFunc) (void*, Color);
			Util::CallVirtualFunction<tFunc>(this, 24)(this, col);
		}

		inline void DrawSetTextColor(int r, int g, int b, int a)
		{
			typedef void(__thiscall* tFunc) (void*, int, int, int, int);
			Util::CallVirtualFunction<tFunc>(this, 25)(this, r, g, b, a);
		}

	
		inline void DrawSetTextPos(int x, int y)
		{
			typedef void(__thiscall* tFunc) (void*, int, int);
			Util::CallVirtualFunction<tFunc>(this, 26)(this, x, y);
		}

		inline void DrawPrintText(const wchar_t *text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
		{
			typedef void(__thiscall* tFunc) (void*, const wchar_t*, int, FontDrawType_t);
			Util::CallVirtualFunction<tFunc>(this, 28)(this, text, textLen, drawType);
		}

		HFont CreateNewFont() //originally CreateFont but it conflicted with a Windows macro
		{
			typedef HFont(__thiscall* tFunc) (void*);
			return Util::CallVirtualFunction<tFunc>(this, 71)(this);
		}

		bool SetFontGlyphSet(HFont& font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
		{
			typedef bool(__thiscall* tFunc) (void*, HFont, const char*, int, int, int, int, int, int, int);
			return Util::CallVirtualFunction<tFunc>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
		}

		//originally const wchar_t *text
		inline void GetTextSize(HFont font, const char *text, int &wide, int &tall) 
		{
			std::string tempString(text);
			std::wstring tempWString(tempString.begin(), tempString.end());
			typedef bool(__thiscall* tFunc) (void*, HFont, const wchar_t*, int&, int&);
			Util::CallVirtualFunction<tFunc>(this, 79)(this, font, tempWString.c_str(), wide, tall);
		}

		inline void GetTextSize(HFont font, std::string& text, int &wide, int &tall)
		{
			GetTextSize(font, text.c_str(), wide, tall);
		}

		//SurfaceGetCursorPos
		inline void GetCursorPos(int &x, int &y) 
		{
			typedef void(__thiscall* tFunc) (void*, int&, int&);
			Util::CallVirtualFunction<tFunc>(this, 100)(this, x, y);
		}
	};
}
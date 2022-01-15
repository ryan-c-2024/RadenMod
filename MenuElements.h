#pragma once
#include "Color.h"
#include <map>

struct Column;

class BaseElement
{
public:
	BaseElement() = default;
	BaseElement(const Color& color, const char* description);
	virtual void Draw() = 0;
	virtual int GetElementHeight() = 0;
	virtual int GetElementWidth() = 0;
	virtual bool ShouldDraw() = 0;
	//Currently only considers X coords
	virtual bool ClickAllowed() = 0;
	virtual bool IsUnderElement(BaseElement* element) = 0;
	Color m_elementColor;
	const char* m_elementDescription;
	int m_posX0, m_posY0;
};

class RectangleElement : public BaseElement
{
public:
	RectangleElement() = default;
	RectangleElement(const Color& color, const char* description);
	virtual void Draw() override;
	virtual bool ClickAllowed() override;
	virtual void Init(const Color& newColor, int x0, int y0, int x1, int y1);
	int m_posX1, m_posY1;
	virtual int GetElementHeight() override;
	virtual int GetElementWidth() override;
	virtual bool IsUnderElement(BaseElement* element) override;
	virtual bool ShouldDraw() override;
};

class MainBody : public RectangleElement
{
public:
	MainBody() = default;
	MainBody(const Color& headerColor, const Color& bodyColor, int x0, int y0, int x1, int y1, const char* headerTitle);
	virtual int GetElementHeight();
	virtual void Init(const Color& headerColor, const Color& bodyColor, int x0, int y0, int x1, int y1, const char* headerTitle);
	virtual void Draw() override;
	int m_headerPosX0, m_headerPosX1, m_headerPosY0, m_headerPosY1;
private:
	Color m_bodyColor;
};

class SubHeader : public BaseElement
{
public:
	virtual void Init(const Color& newColor, int x0, int y0, const char* headerTitle);
	virtual void Draw();
};

class ClickableRectangle : public RectangleElement
{
protected:
	ClickableRectangle() = default;
	ClickableRectangle(const Color& color, const char* description);
	//checks whether you clicked in within coordinates passed as arguments 
	//also takes into consideration tick of the click so it doesn't toggle on and off really fast
	bool inline IsValidRectClick();
	virtual inline void OnClick() = 0;
};

class Checkbox : public ClickableRectangle
{
public:
	Checkbox(const Color& borderColor, const Color& fillColor, const char* boxLabel, bool& linkedVar);
	virtual void Draw() override;
	int m_sideLength = 20;
	Color m_boxFillColor;
	int m_posLabelX, m_posLabelY;
	int m_posBoxFillX0, m_posBoxFillX1, m_posBoxFillY0, m_posBoxFillY1;
	virtual inline int GetElementWidth() override;
private:
	bool& m_linkedVar;
	inline void SetSideLength(int newSideLength);
protected:
	virtual inline void OnClick() override;
};

class Button : public ClickableRectangle
{
public:
	typedef void(*Func)();

	//functionPointer = function pointed to called when button clicked
	Button(const Color& mainColor, const char* boxLabel, Func functionPointer);
	virtual void Draw() override;
private:
	int m_text_width, m_text_height;
	Func m_onClickFunction;
protected:
	virtual void OnClick() override;
};

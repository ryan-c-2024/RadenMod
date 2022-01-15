#include "stdafx.h"
#include "MenuElements.h"
#include "DrawAssist.h"
#include "Global Interfaces.h"
#include "MenuSkeleton.h"
#include "MenuUtil.h"
#include <set>
#include "ButtonCode_t.h"
#include "MenuTemplateElements.h"

//TO DO: PERHAPS INITIALIZE RECTANGLEELEMENT POSITION IN ITS CONSTRUCTOR, TRY TO CHANGE OUT INIT FUNCS AND INSTEAD USE INITIALIZER LISTS...

BaseElement::BaseElement(const Color& color, const char* description) : m_elementColor(color), m_elementDescription(description)
{ }

RectangleElement::RectangleElement(const Color& color, const char* description) : BaseElement(color, description)
{ }

void RectangleElement::Draw()
{
	DrawAssist::DrawFilledRect(m_elementColor, m_posX0, m_posY0, m_posX1, m_posY1);
}
void RectangleElement::Init(const Color& newColor, int x0, int y0, int x1, int y1) 
{
	m_posX0 = x0 * GMisc::scaleFactor, m_posX1 = x1 * GMisc::scaleFactor;
	m_posY0 = y0 * GMisc::scaleFactor, m_posY1 = y1 * GMisc::scaleFactor;
}
int RectangleElement::GetElementHeight()
{
	return m_posY1 - m_posY0;
}
int RectangleElement::GetElementWidth()
{
	return m_posX1 - m_posX0;
}
bool RectangleElement::IsUnderElement(BaseElement* element)
{
	if (m_posX0 > element->m_posX0 && m_posX1 < element->m_posX0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool RectangleElement::ClickAllowed()
{
	/*
	for (auto bar : expandedBars)
	{
		if (IsUnderElement(bar) && this != bar)
		{
			return false;
		}
	}
	return true;
	*/
	return true;
}
bool RectangleElement::ShouldDraw()
{
	return true;
}

MainBody::MainBody(const Color& headerColor, const Color& bodyColor, int x0, int y0, int x1, int y1, const char* headerTitle) : 
	RectangleElement(headerColor, headerTitle), m_bodyColor(bodyColor)
{
	m_posX0 = x0 * GMisc::scaleFactor, m_posX1 = x1 * GMisc::scaleFactor;
	m_posY0 = y0 * GMisc::scaleFactor, m_posY1 = y1 * GMisc::scaleFactor;
	m_headerPosX0 = m_posX0, m_headerPosX1 = m_posX1;
	m_headerPosY0 = m_posY0 - (55 * GMisc::scaleFactor), m_headerPosY1 = m_posY0;
}
void MainBody::Draw()
{
	DrawAssist::DrawFilledRect(m_bodyColor, m_posX0, m_posY0, m_posX1, m_posY1);
	DrawAssist::DrawFilledRect(m_elementColor, m_headerPosX0, m_headerPosY0, m_headerPosX1, m_headerPosY1);

	int fontWidth, fontHeight;
	IFace::surface->GetTextSize(Fonts::fontMenuTitle, m_elementDescription, fontWidth, fontHeight);
	DrawAssist::DrawString(m_elementDescription, Fonts::fontMenuTitle, Color(255, 255, 255, 255), (m_headerPosX0 + m_headerPosX1) / 2 - fontWidth / 2, (m_headerPosY0 + m_headerPosY1) / 2 - fontHeight / 2);
}
void MainBody::Init(const Color& headerColor, const Color& bodyColor, int x0, int y0, int x1, int y1, const char* headerTitle)
{
	m_posX0 = x0 * GMisc::scaleFactor, m_posX1 = x1 * GMisc::scaleFactor;
	m_posY0 = y0 * GMisc::scaleFactor, m_posY1 = y1 * GMisc::scaleFactor;
	m_headerPosX0 = m_posX0, m_headerPosX1 = m_posX1;
	m_headerPosY0 = m_posY0 - (55 * GMisc::scaleFactor), m_headerPosY1 = m_posY0;
}
int MainBody::GetElementHeight()
{
	return m_posY1 - m_headerPosY0;
}

void SubHeader::Init(const Color& newColor, int x0, int y0, const char* headerTitle)
{
	m_elementDescription = headerTitle;
	m_posX0 = x0;
	m_posY0 = y0;
}
void SubHeader::Draw()
{
	DrawAssist::DrawString(m_elementDescription, Fonts::fontMenu, Color(255, 255, 255, 255), m_posX0, m_posY0);
}

Checkbox::Checkbox(const Color& borderColor, const Color& fillColor, const char* boxLabel, bool& linkedVar) : ClickableRectangle(borderColor, boxLabel),
	m_boxFillColor(fillColor), m_linkedVar(linkedVar)
{
	m_sideLength *= GMisc::scaleFactor;
	m_elementDescription = boxLabel;
	m_linkedVar = linkedVar;
}
void Checkbox::OnClick()
{
	m_linkedVar = !m_linkedVar; //toggle linked var value
}
void Checkbox::Draw()
{
	if (IsValidRectClick())
	{
		OnClick();
	}

	DrawAssist::DrawOutlinedRect(m_elementColor, m_posX0, m_posY0, m_posX0 + m_sideLength, m_posY0 + m_sideLength);
	DrawAssist::DrawString(m_elementDescription, Fonts::fontMenu, Color(255, 255, 255, 255), m_posLabelX, m_posLabelY);

	if (m_linkedVar) //draw filled in checkbox if linked bool is true
	{
		DrawAssist::DrawFilledRect(m_boxFillColor, m_posBoxFillX0, m_posBoxFillY0, m_posBoxFillX1, m_posBoxFillY1);
	}
}
void Checkbox::SetSideLength(int newSideLength)
{
	m_sideLength = newSideLength;
}
int Checkbox::GetElementWidth()
{
	return m_posX1 - m_posLabelX;
}

ClickableRectangle::ClickableRectangle(const Color& color, const char* description) : RectangleElement(color, description)
{ }

inline bool ClickableRectangle::IsValidRectClick() 
{ 
	if (!ClickAllowed())
		return false;

	return (MenuUtil::IsValidClick(m_posX0, m_posY0, m_posX1, m_posY1));
}

//consider adding variable length buttons (depending on how long the text label is)
Button::Button(const Color& mainColor, const char* boxLabel, Func functionPointer) :
	ClickableRectangle(mainColor, boxLabel), m_onClickFunction(functionPointer)
{
	IFace::surface->GetTextSize(Fonts::fontMenu, m_elementDescription, m_text_width, m_text_height);
}
void Button::Draw()
{
	//DrawAssist::DrawOutlinedRect(Color(0, 0, 0, 255), m_posX0, m_posY0, m_posX1, m_posY1); //black outline around button
	DrawAssist::DrawFilledRect(m_elementColor, m_posX0 + 1, m_posY0 + 1, m_posX1 - 1, m_posY1 - 1); //actual color of button
	
	int button_middle_x = (m_posX0 + m_posX1) / 2;
	int button_middle_y = (m_posY0 + m_posY1) / 2;
	int text_x = button_middle_x - (m_text_width / 2);
	int text_y = button_middle_y - (m_text_height / 2);
	DrawAssist::DrawString(m_elementDescription, Fonts::fontMenu, Color(255, 255, 255, 255), text_x, text_y);

	if (IsValidRectClick())
	{
		OnClick();
	}
}
void Button::OnClick()
{
	m_onClickFunction();
}

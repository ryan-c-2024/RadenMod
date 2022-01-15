
//std::set<DropDownBar<const char*, int>> expandedBars = {};

//definitions for the menu template elements. This file is included into the MenuTemplateElements.h header

#include "DrawAssist.h"
#include "MenuUtil.h"

template <typename T>
Slider<T>::Slider(const Color& barColor, const Color& outlineColor, const char* sliderLabel, T& linkedVar, T valueStart, T valueEnd) :
	ClickableRectangle(barColor, sliderLabel), m_linkedVar(linkedVar), m_outlineColor(outlineColor), m_valueStart(valueStart), m_valueEnd(valueEnd)
{
	m_barFillFactor = (m_linkedVar - valueStart) / valueEnd;
}

template <typename T>
void Slider<T>::Draw()
{
	if (SliderGetClick()) //using this instead of typical mousedown so you can hold LMB to adjust
	{
		OnClick();
		ClampSliderValues();
	}

	int barWidth = m_posX1 - m_posX0;
	int barFillX = m_posX0 + (barWidth * m_barFillFactor) - 1;
	DrawAssist::DrawFilledRect(m_elementColor, m_posX0 + 1, m_posY0 + 1, barFillX, m_posY1 - 1); //bar fill
	DrawAssist::DrawOutlinedRect(m_outlineColor, m_posX0, m_posY0, m_posX1, m_posY1); //black outline

	std::string labelString(m_elementDescription); //text that shows current value and description
	labelString += ": " + std::to_string(m_linkedVar);

	int textWidth, textHeight;
	IFace::surface->GetTextSize(Fonts::fontMenu, labelString.c_str(), textWidth, textHeight);

	int textX = m_posX0, textY = m_posY0 - textHeight;
	textY -= 3 * GMisc::scaleFactor;
	DrawAssist::DrawString(labelString.c_str(), Fonts::fontMenu, Color(255, 255, 255, 255), textX, textY);
}

template <typename T>
inline void Slider<T>::ClampSliderValues()
{
	if (m_linkedVar > m_valueEnd)
	{
		m_linkedVar = m_valueEnd;
	}
	else if (m_linkedVar < m_valueStart)
	{
		m_linkedVar = m_valueStart;
	}
}

template <typename T>
void Slider<T>::AdjustVariable(int movedAmount)
{
	T valueDifference = m_valueEnd - m_valueStart;
	int barWidth = m_posX1 - m_posX0;
	float mousePosRelative = (movedAmount - m_posX0);
	float mousePosFactor = mousePosRelative / barWidth;
	m_barFillFactor = mousePosFactor;
	m_linkedVar = m_valueStart + (valueDifference * mousePosFactor);
}

template <typename T>
bool Slider<T>::SliderGetClick()
{
	if (MenuUtil::IsBeingClicked(m_posX0, m_posY0, m_posX1, m_posY1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
void Slider<T>::OnClick()
{
	int movedX, movedY;
	IFace::surface->GetCursorPos(movedX, movedY);
	AdjustVariable(movedX);
}

template <typename T, typename U>
DropDownBar<T, U>::DropDownBar(const Color& outlineColor, const Color& barColor, const Color& currentItemColor, const char* boxLabel, U& linkedVar,
	const std::map<T, U>& valueMap) : ClickableRectangle(outlineColor, boxLabel), m_barColor(barColor), m_valueMap(valueMap),
	m_isExpanded(false), m_linkedVar(linkedVar), m_currentItemColor(currentItemColor)
{ }

template <typename T, typename U>
void DropDownBar<T, U>::Draw()
{
	DrawAssist::DrawOutlinedRect(m_elementColor, m_posX0, m_posY0, m_posX1, m_posY1);
	DrawAssist::DrawFilledRect(m_elementColor, m_posX0 + 1, m_posY0 + 1, m_posX1 - 1, m_posY1 - 1);
	int textWidth, textHeight;
	IFace::surface->GetTextSize(Fonts::fontMenu, m_elementDescription, textWidth, textHeight);
	int textX = ((m_posX0 + m_posX1) / 2) - (textWidth / 2), textY = ((m_posY0 + m_posY1) / 2) - (textHeight / 2);
	DrawAssist::DrawString(m_elementDescription, Fonts::fontMenu, Color(255, 255, 255, 255), textX, textY);

	if (IsValidRectClick())
	{
		OnClick();
	}

	if (m_isExpanded) //draw bar items if expanded
	{
		static int barHeight = GetElementHeight();
		int index = 1; // used and multiplied by height so the minibars dont stack on top of each other

		for (auto it = m_valueMap.begin(), end = m_valueMap.end(); it != end; ++it, index++)
		{
			int barItemY0 = m_posY0 + (barHeight * index), barItemY1 = barItemY0 + barHeight;
			DrawBarItem(it->first, m_posX0, barItemY0, m_posX1, barItemY1); // it->first is the map's key (going to be const char* usually)
		}
	}
}

template <typename T, typename U>
void DropDownBar<T, U>::OnClick()
{
	m_isExpanded = !m_isExpanded;
	/*
	if (m_isExpanded)
	{
	expandedBars.insert(this);
	}
	else if (!m_isExpanded && expandedBars.find(this) != expandedBars.end())
	{
	expandedBars.erase(this);
	}
	*/

}

template <typename T, typename U>
void DropDownBar<T, U>::DrawBarItem(T itemText, int x0, int y0, int x1, int y1)
{
	int textWidth, textHeight;
	IFace::surface->GetTextSize(Fonts::fontMenu, itemText, textWidth, textHeight); //error reading characters of string here and crash
	int textX = ((x0 + x1) / 2) - (textWidth / 2), textY = ((y0 + y1) / 2) - (textHeight / 2);

	DrawAssist::DrawOutlinedRect(m_elementColor, x0, y0, x1, y1);
	DrawAssist::DrawFilledRect((m_linkedVar == m_valueMap.at(itemText)) ? m_currentItemColor : m_barColor, x0 + 1, y0 + 1, x1 - 1, y1 - 1);
	DrawAssist::DrawString(itemText, Fonts::fontMenu, Color(255, 255, 255, 255), textX, textY);

	if (MenuUtil::IsValidClick(x0 + 1, y0 + 1, x1 - 1, y1 - 1))
	{
		OnItemClick(m_valueMap.at(itemText));
	}
}

template <typename T, typename U>
inline int DropDownBar<T, U>::GetElementHeight()
{
	return m_posY1 - m_posY0;
}

template <typename T, typename U>
inline void DropDownBar<T, U>::OnItemClick(U itemValue)
{
	if (!ClickAllowed())
		return;
	m_linkedVar = itemValue;
}


#ifndef MENU_TEMPLATE_ELEMENTS_H
#define MENU_TEMPLATE_ELEMENTS_H
#include <set>

class ClickableRectangle;

template <typename T>
class Slider : public ClickableRectangle
{
public:
	Slider() = default;
	Slider(const Color& barColor, const Color& outlineColor, const char* sliderLabel, T& linkedVar, T valueStart, T valueEnd);

	virtual void Draw() override;
private:
	inline void ClampSliderValues();
	void AdjustVariable(int movedAmount);
	bool SliderGetClick();

	T m_valueStart, m_valueEnd;
	float m_barFillFactor;
	T& m_linkedVar;
	Color m_barColor;
	Color m_outlineColor;
protected:
	virtual void OnClick() override;
};


// T is the type of the map key, U is the type of the map value
template <typename T, typename U>
class DropDownBar : public ClickableRectangle
{
public:
	DropDownBar(const Color& outlineColor, const Color& barColor, const Color& currentItemColor, const char* boxLabel, U& linkedVar,
		const std::map<T, U>& valueMap);
	virtual void Draw() override;
	//in this case we get the bar's height unexpanded
	virtual int GetElementHeight() override;
private:
	// for the dropdownbar's actual bar
	U& m_linkedVar;
	Color m_barColor;
	Color m_currentItemColor;
	const std::map<T, U>& m_valueMap;
	void DrawBarItem(T itemText, int x0, int y0, int x1, int y1);
	void OnItemClick(U itemValue);
	bool m_isExpanded;

protected:
	virtual void OnClick() override;
};

#include "MenuTemplateElements.inl"

#endif
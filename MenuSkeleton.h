#pragma once
#include <vector>
#include "Color.h"
#include <memory>

class MainBody;
class BaseElement;
class Checkbox;

//class DropDownBar<T>;
class ClickableRectangle;
class Button;

//column for keeping track of the number of elements and determining their position
struct Column
{
	int m_startX0, m_startX1, m_startY0, m_startY1;
	int m_numElements;
	int m_nextAvailableSpotX, m_nextAvailableSpotY;
	Column(int x0, int y0, int x1, int y1);
	int m_oldX0, m_oldY0, m_oldX1, m_oldY1;
};

//tab in menu
struct Tab
{
	Tab(const char* tabName, const Color& color);
	std::vector<std::shared_ptr<BaseElement>> m_elements;

	void DrawContents();
	void DrawTab();
	void AddNewCheckbox(std::unique_ptr<Column>& column, std::shared_ptr<Checkbox> checkbox);
	void AddNewDropDownBar(std::unique_ptr<Column>& column, std::shared_ptr<ClickableRectangle> dropDownBar, bool onSide = false);
	void AddNewSlider(std::unique_ptr<Column>& column, std::shared_ptr<ClickableRectangle> slider);
	void AddNewButton(std::unique_ptr<Column>& column, std::shared_ptr<Button> button, bool onSide = false);
	int m_posX0, m_posX1, m_posY0, m_posY1;
	const char* m_tabName;
	int m_tabWidth, m_tabHeight;
	int m_textWidth, m_textHeight;

	std::unique_ptr<Column> m_column1;
	std::unique_ptr<Column> m_column2;

private:
	Color m_color;
};

//core class: wraps around elements and tabs
class TabManager
{
public:
	TabManager(const Color& colorOfTabs);
	//Loop through tab vector and draw them along with other stuff
	void DrawTabs();
private:
	//Initialize the elements, such as the checkboxes. Was originally just in constructor and not a func.
	void InitElements(const Color& colorOfTabs, const Color& barFillColor, const Color& currentItemColor);
	//add new tab and set its position
	void AddNewTab(Tab* newTab);
	//Wrapper to get if a tab click is valid, using the member variable coordinates
	bool IsValidTabClick(Tab* tab);
	//Calculates tab dimensions. Used for calculating position of new tabs
	void GetTabDimensions(Tab* tab, int& tabWidth, int& tabHeight);

	Tab* m_activeTab;
	std::vector<Tab*> m_Tabs;

	std::unique_ptr<Tab> m_aimbotTab;
	std::unique_ptr<Tab> m_espTab;
	std::unique_ptr<Tab> m_visualTab;
	std::unique_ptr<Tab> m_miscTab;
	std::unique_ptr<Tab> m_griefTab;
	std::unique_ptr<Tab> m_hvhTab;
	std::unique_ptr<Tab> m_configTab;

	MainBody& m_mainBody;

	//to do: perhaps "centralize" the element coloring more so it is easier to change
	const Color m_mainColor;
	const Color m_alternateColor;
};


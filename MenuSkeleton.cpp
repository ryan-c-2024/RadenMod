#include "stdafx.h"
#include "MenuSkeleton.h"
#include "MenuUtil.h"
#include "DrawAssist.h"
#include <memory>
#include "MenuElements.h"
#include "Global Interfaces.h"
#include "MenuTemplateElements.h"
#include "Options.h"
#include "Config.h"

//maps for the dropdown lists
std::map<const char*, int> aimTargets = { { "Head", Options::Aimbot::Head },{ "Neck", Options::Aimbot::Neck },{ "Lower Chest", Options::Aimbot::Chest_Lower },{ "Upper Chest", Options::Aimbot::Chest_Upper },
{ "Chest Center", Options::Aimbot::Chest_Center },{ "Stomach", Options::Aimbot::Stomach },{ "Pelvis", Options::Aimbot::Pelvis } };

std::map<const char*, int> yawAntiAims = { { "Static Forward", Options::AntiAim::Yaw::ForwardStatic },{ "Forward Jitter", Options::AntiAim::Yaw::ForwardJitter },
{ "Backward Jitter", Options::AntiAim::Yaw::BackJitter },{ "Backward Static", Options::AntiAim::Yaw::BackStatic },{ "Spin", Options::AntiAim::Yaw::Spin },{ "Left", Options::AntiAim::Left },
{ "Right", Options::AntiAim::Right },{ "Fukkireta", Options::AntiAim::Fukkireta } };

std::map<const char*, int> pitchAntiAims = { { "Default", Options::AntiAim::Pitch::Forward },{ "Down", Options::AntiAim::Pitch::Down },{ "Up", Options::AntiAim::Pitch::Up } };


Column::Column(int x0, int y0, int x1, int y1)
{
	m_startX0 = x0, m_startX1 = x1;
	m_startY0 = y0, m_startY1 = y1;
	m_numElements = 0;
	m_nextAvailableSpotX = m_startX0, m_nextAvailableSpotY = m_startY0;
}

Tab::Tab(const char* tabName, const Color& color)
{
	m_tabName = tabName;
	m_color = color;
}

void Tab::AddNewCheckbox(std::unique_ptr<Column>& column, std::shared_ptr<Checkbox> checkbox)
{
	//label starts where the column starts (the start of text is aligned)
	checkbox->m_posLabelX = column->m_nextAvailableSpotX, checkbox->m_posLabelY = column->m_nextAvailableSpotY;
	checkbox->m_posY0 = column->m_nextAvailableSpotY, checkbox->m_posY1 = checkbox->m_posY0 + checkbox->m_sideLength;

	int textWidth, textHeight;
	//calc width and height for centering and alignment
	IFace::surface->GetTextSize(Fonts::fontMenu, checkbox->m_elementDescription, textWidth, textHeight); 

	int paddingSpace = (200 * GMisc::scaleFactor) - textWidth; //so both the start of the label and the checkboxes are aligned

	// since padding is included, all checkboxes are aligned
	checkbox->m_posX0 = checkbox->m_posLabelX + paddingSpace + textWidth, checkbox->m_posX1 = checkbox->m_posX0 + checkbox->m_sideLength;
	//Calculate the inner box "filling" which is displayed when the box is checked
	checkbox->m_posBoxFillX0 = checkbox->m_posX0 + (3 * GMisc::scaleFactor), checkbox->m_posBoxFillX1 = checkbox->m_posX1 - (3 * GMisc::scaleFactor);
	checkbox->m_posBoxFillY0 = checkbox->m_posY0 + (3 * GMisc::scaleFactor), checkbox->m_posBoxFillY1 = checkbox->m_posY1 - (3 * GMisc::scaleFactor);

	//Once a checkbox is added, the next available spot moves down
	column->m_nextAvailableSpotY += checkbox->GetElementHeight() + (GMisc::scaleFactor * 10);
	//add the checkbox into the elements vector so it can be drawn 
	m_elements.push_back(checkbox);
}
void Tab::AddNewDropDownBar(std::unique_ptr<Column>& column, std::shared_ptr<ClickableRectangle> dropDownBar, bool onSide)
{
	if (onSide)
	{
		dropDownBar->m_posX0 = column->m_oldX1 + (30 * GMisc::scaleFactor), dropDownBar->m_posX1 = dropDownBar->m_posX0 + (125 * GMisc::scaleFactor);
		dropDownBar->m_posY0 = column->m_oldY0, dropDownBar->m_posY1 = dropDownBar->m_posY0 + (25 * GMisc::scaleFactor);
	}
	else
	{
		dropDownBar->m_posX0 = column->m_nextAvailableSpotX, dropDownBar->m_posX1 = dropDownBar->m_posX0 + (125 * GMisc::scaleFactor);
		dropDownBar->m_posY0 = column->m_nextAvailableSpotY, dropDownBar->m_posY1 = dropDownBar->m_posY0 + (25 * GMisc::scaleFactor);
	}
	column->m_oldX0 = column->m_nextAvailableSpotX, column->m_oldY0 = column->m_nextAvailableSpotY;
	column->m_oldX1 = dropDownBar->m_posX1, column->m_oldY1 = dropDownBar->m_posY1;
	column->m_nextAvailableSpotY += dropDownBar->GetElementHeight() + (GMisc::scaleFactor * 10);
	m_elements.push_back(dropDownBar);
}
void Tab::AddNewSlider(std::unique_ptr<Column>& column, std::shared_ptr<ClickableRectangle> slider)
{
	slider->m_posX0 = column->m_nextAvailableSpotX, slider->m_posX1 = slider->m_posX0 + (180 * GMisc::scaleFactor);
	slider->m_posY0 = column->m_nextAvailableSpotY + (10 * GMisc::scaleFactor), slider->m_posY1 = slider->m_posY0 + (24 * GMisc::scaleFactor);
	column->m_oldX0 = column->m_nextAvailableSpotX, column->m_oldY0 = column->m_nextAvailableSpotY;
	column->m_oldX1 = slider->m_posX1, column->m_oldY1 = slider->m_posY1;
	column->m_nextAvailableSpotY += slider->GetElementHeight() + (GMisc::scaleFactor * 15);
	m_elements.push_back(slider);
}
void Tab::AddNewButton(std::unique_ptr<Column>& column, std::shared_ptr<Button> button, bool onSide)
{
	if (onSide)
	{
		button->m_posX0 = column->m_oldX1 + (30 * GMisc::scaleFactor);
		button->m_posX1 = button->m_posX0 + (90 * GMisc::scaleFactor);
		button->m_posY0 = column->m_oldY0;
		button->m_posY1 = button->m_posY0 + (30 * GMisc::scaleFactor);
	}
	else
	{
		button->m_posX0 = column->m_nextAvailableSpotX;
		button->m_posX1 = button->m_posX0 + (90 * GMisc::scaleFactor);
		button->m_posY0 = column->m_nextAvailableSpotY + (10 * GMisc::scaleFactor);
		button->m_posY1 = button->m_posY0 + (30 * GMisc::scaleFactor);
	}

	column->m_oldX0 = button->m_posX0, column->m_oldY0 = button->m_posY0;
	column->m_oldX1 = button->m_posX1, column->m_oldY1 = button->m_posY1;

	column->m_nextAvailableSpotY += button->GetElementHeight() + (GMisc::scaleFactor * 15);

	m_elements.push_back(button);
}

void Tab::DrawContents()
{
	for (std::shared_ptr<BaseElement> element : m_elements)
	{
		element->Draw();
	}
}
void Tab::DrawTab()
{
	DrawAssist::DrawFilledRect(Color(0, 0, 0, 255), m_posX0 - 1, m_posY0 - 1, m_posX1 + 1, m_posY1 + 1); //black outline of tab
	DrawAssist::DrawFilledRect(m_color, m_posX0, m_posY0, m_posX1, m_posY1); //tab itself
	//below: draws tab name so it is centered on the tab
	DrawAssist::DrawString(m_tabName, Fonts::fontMenu, Color(255, 255, 255, 255), ((m_posX0 + m_posX1) / 2) - m_textWidth / 2, ((m_posY0 + m_posY1) / 2) - (m_textHeight / 2));
}

TabManager::TabManager(const Color& colorOfTabs) : m_mainBody(MainBody(Color(2, 84, 0, 255), Color(0, 0, 0, 213), 360, 300, 1560, 940, "Jebhook Menu"))
{
	//Create the tabs as smart pointers so they dont have to be constructed 
	// in the header and so they dont go out of scope
	m_aimbotTab = std::make_unique<Tab>("Aimbot", colorOfTabs);
	m_espTab = std::make_unique<Tab>("ESP", colorOfTabs);
	m_visualTab = std::make_unique<Tab>("Visuals", colorOfTabs);
	m_miscTab = std::make_unique<Tab>("Misc", colorOfTabs);
	m_griefTab = std::make_unique<Tab>("Griefing", colorOfTabs);
	m_hvhTab = std::make_unique<Tab>("HvH", colorOfTabs);
	m_configTab = std::make_unique<Tab>("Config", colorOfTabs);
	//used for settings positions and colors to be the same as the main body's

	//Add the new tabs in using the tab pointers
	AddNewTab(m_aimbotTab.get());
	AddNewTab(m_espTab.get());
	AddNewTab(m_visualTab.get());
	AddNewTab(m_miscTab.get());
	AddNewTab(m_griefTab.get());
	AddNewTab(m_hvhTab.get());
	AddNewTab(m_configTab.get());

	InitElements(colorOfTabs, Color(1, 45, 5, 255), Color(1, 135, 14, 255));
}

void TabManager::InitElements(const Color& colorOfTabs, const Color& barFillColor, const Color& currentItemColor)
{
	/*
	INIT CHECKBOXES
	*/
	//Create smart pointers to checkbox objects so they dont go out of scope, as the pointers are added to the Tab's element vector
	std::shared_ptr<Checkbox> aimbotEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Aimbot Enabled", Options::Aimbot::bEnabled);
	std::shared_ptr<Checkbox> aimbotVischeck = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Vischeck", Options::Aimbot::bTargetVisibleOnly);
	std::shared_ptr<Checkbox> aimbotAimstep = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Aimstep", Options::Aimbot::bAimstepEnabled);
	std::shared_ptr<Checkbox> aimbotAutoAim = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "AutoAim", Options::Aimbot::bAutoAim);
	std::shared_ptr<Checkbox> aimbotAutoCrouch = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "AutoCrouch", Options::Aimbot::bAutoCrouch);
	std::shared_ptr<Checkbox> aimbotAutoStop = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "AutoStop", Options::Aimbot::bAutoStop);
	std::shared_ptr<Checkbox> aimbotAutoScope = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "AutoScope", Options::Aimbot::bAutoScope);
	std::shared_ptr<Checkbox> aimbotAutoShoot = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "AutoShoot", Options::Aimbot::bAutoShoot);
	std::shared_ptr<Checkbox> aimbotControlRecoil = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Recoil Control", Options::Aimbot::bControlRecoil);
	std::shared_ptr<Checkbox> aimbotTargetTeam = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Target Team", Options::Aimbot::bTargetTeam);
	std::shared_ptr<Checkbox> aimbotTargetEnemy = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Target Enemy", Options::Aimbot::bTargetEnemy);
	std::shared_ptr<Checkbox> aimbotSilentAim = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Silent Aim", Options::Aimbot::bSilentAimEnabled);
	std::shared_ptr<Checkbox> aimbotSmoothEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Smooth Aim", Options::Aimbot::bSmoothAim);
	std::shared_ptr<Checkbox> aimbotDisableWhenNoGunOut = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Disable When No Gun Out", Options::Aimbot::bDisableWhenNoGunOut);
	std::shared_ptr<Checkbox> aimbotDisableWhenReloading = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Disable When Reloading", Options::Aimbot::bDisableWhenReloading);
	std::shared_ptr<Checkbox> aimbotMultiAimspot = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Multi-Aimspot", Options::Aimbot::bMultiAimspot);
	std::shared_ptr<Checkbox> aimbotGhettoAutowall = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Ghetto Autowall", Options::Aimbot::bGhettoAutowall);

	std::shared_ptr<Checkbox> espEspEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Esp Enabled", Options::Esp::bEnabled);
	std::shared_ptr<Checkbox> espBoxEsp = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Box Esp", Options::Esp::bDrawBoxEsp);
	std::shared_ptr<Checkbox> espNameEsp = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Name Esp", Options::Esp::bNameEsp);
	std::shared_ptr<Checkbox> espWeaponEsp = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Weapon Esp", Options::Esp::bWeaponEsp);
	std::shared_ptr<Checkbox> espDrawEnemy = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Enemy Esp", Options::Esp::bDrawEnemy);
	std::shared_ptr<Checkbox> espDrawTeam = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Team Esp", Options::Esp::bDrawTeam);
	std::shared_ptr<Checkbox> espHealthBar = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Health Bar", Options::Esp::bDrawHealthBar);
	std::shared_ptr<Checkbox> espArmorBar = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Armor Bar", Options::Esp::bDrawArmorBar);
	std::shared_ptr<Checkbox> espHealthBasedColor = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Health-Based Color", Options::Esp::bHealthBasedColoring);

	std::shared_ptr<Checkbox> visualRemoveScope = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Remove Scope Border", Options::Visual::bDisableScopeVisual);

	std::shared_ptr<Checkbox> miscReduceFlash = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Reduce Flash", Options::Misc::bChangeFlashAlphaEnabled);
	std::shared_ptr<Checkbox> miscSlowFall = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Slowfall (V key)", Options::Misc::bSlowFall);
	std::shared_ptr<Checkbox> miscFakeLag = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Fake Lag", Options::Misc::bFakeLag);
	std::shared_ptr<Checkbox> miscBunnyHopEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Bunnyhop", Options::Bunnyhop::bEnabled);
	std::shared_ptr<Checkbox> miscBunnyHopAutoStrafe = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Autostrafer", Options::Bunnyhop::bAutoStrafeEnabled);
	std::shared_ptr<Checkbox> miscBunnyHopSilentStrafe = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Silent Strafes", Options::Bunnyhop::bSilentStrafe);
	std::shared_ptr<Checkbox> miscChatSpamEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Chat Spam", Options::Misc::bChatSpamEnabled);
	std::shared_ptr<Checkbox> miscPositionSpamEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Position Spam", Options::ChatSpamPositions::bEnabled);
	std::shared_ptr<Checkbox> miscPositionSpamTeam = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Spam Friendly Positions", Options::ChatSpamPositions::bCalloutTeam);
	std::shared_ptr<Checkbox> miscPositionSpamEnemy = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Spam Enemy Positions", Options::ChatSpamPositions::bCalloutEnemy);
	std::shared_ptr<Checkbox> miscPositionSpamUseTeamChat = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Position Spam In Team Chat", Options::ChatSpamPositions::bUseTeamChat);

	std::shared_ptr<Checkbox> griefGoombaStompEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Goomba Stomp", Options::GoombaStomp::bEnabled);

	std::shared_ptr<Checkbox> hvhAntiAimEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "AntiAim", Options::AntiAim::bEnabled);
	std::shared_ptr<Checkbox> hvhFakeAnglesEnabled = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Fake AntiAim", Options::AntiAim::bFakeAnglesEnabled);
	std::shared_ptr<Checkbox> hvhShowAntiAimAngles = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Show AntiAim Angles", Options::AntiAim::bShowAngles);
	std::shared_ptr<Checkbox> hvhResolver = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Resolver Enabled", Options::Resolver::bEnabled);
	std::shared_ptr<Checkbox> hvhBodyAimUnresolvable = std::make_shared<Checkbox>(m_mainBody.m_elementColor, colorOfTabs, "Body-Aim Unresolvable", Options::Resolver::bBodyAimUnresolvable);

	/*
	INIT DROP DOWN BARS (maps are in global scope at top of file)
	*/

	std::shared_ptr<DropDownBar<const char*, int> > aimbotAimTarget = std::make_shared<DropDownBar<const char*, int>>(m_mainBody.m_elementColor, barFillColor, currentItemColor, "Aimbot Target", Options::Aimbot::iTargetBone, aimTargets);
	std::shared_ptr<DropDownBar<const char*, int> > hvhYawAntiAim = std::make_shared<DropDownBar<const char*, int>>(m_mainBody.m_elementColor, barFillColor, currentItemColor, "Yaw AntiAim", Options::AntiAim::iYawAntiAimMode, yawAntiAims);
	std::shared_ptr<DropDownBar<const char*, int> > hvhPitchAntiAim = std::make_shared<DropDownBar<const char*, int>>(m_mainBody.m_elementColor, barFillColor, currentItemColor, "Pitch AntiAim", Options::AntiAim::iPitchAntiAimMode, pitchAntiAims);
	std::shared_ptr<DropDownBar<const char*, int> > hvhFakeYawAntiAim = std::make_shared<DropDownBar<const char*, int>>(m_mainBody.m_elementColor, barFillColor, currentItemColor, "Fake Yaw", Options::AntiAim::iFakeYawAntiAimMode, yawAntiAims);
	std::shared_ptr<DropDownBar<const char*, int> > hvhFakePitchAntiAim = std::make_shared<DropDownBar<const char*, int>>(m_mainBody.m_elementColor, barFillColor, currentItemColor, "Fake Pitch", Options::AntiAim::iFakePitchAntiAimMode, pitchAntiAims);
	std::shared_ptr<DropDownBar<std::string, std::string> > cfgAvailableConfigs = std::make_shared<DropDownBar<std::string, std::string>>(m_mainBody.m_elementColor, barFillColor, currentItemColor, "Select Config", Options::Config::selectedConfig, Config::m_availableConfigs);

	/*
	INIT SLIDERS
	*/
	std::shared_ptr<Slider<float>> aimbotSmoothAmount = std::make_shared<Slider<float>>(colorOfTabs, m_mainBody.m_elementColor, "Smooth Amount", Options::Aimbot::flSmoothFactor, 0, 40);
	std::shared_ptr<Slider<float>> aimbotAimstepThreshold = std::make_shared<Slider<float>>(colorOfTabs, m_mainBody.m_elementColor, "Aimstep Threshold", Options::Aimbot::flAimstepAngleChange, 0, 100);
	std::shared_ptr<Slider<float>> aimbotGhettoAutowallModifier = std::make_shared<Slider<float>>(colorOfTabs, m_mainBody.m_elementColor, "Ghetto Autowall Modifier", Options::Aimbot::flGhettoAutowallModifier, 10, 95);

	std::shared_ptr<Slider<float>> miscNewFlashAlpha = std::make_shared<Slider<float>>(colorOfTabs, m_mainBody.m_elementColor, "Flash Brightness", Options::Misc::flNewFlashAlpha, 0, 255);
	std::shared_ptr<Slider<int>> miscFakeLagAmount = std::make_shared<Slider<int>>(colorOfTabs, m_mainBody.m_elementColor, "Fakelag Intensity", Options::Misc::iFakeLagChokedTicks, 0, 13);

	/*
	INIT BUTTONS
	*/
	std::shared_ptr<Button> cfgCreateNewConfig = std::make_shared<Button>(m_mainBody.m_elementColor, "New Config", &Config::CreateConfigTemplate);
	std::shared_ptr<Button> cfgLoadSelected = std::make_shared<Button>(m_mainBody.m_elementColor, "Load Selected", &Config::LoadSelectedConfig);
	std::shared_ptr<Button> cfgSaveSelected = std::make_shared<Button>(m_mainBody.m_elementColor, "Save Selected", &Config::SaveSelectedConfig);
	std::shared_ptr<Button> cfgRefreshList = std::make_shared<Button>(m_mainBody.m_elementColor, "Refresh List", &Config::RefreshConfigList);

	//Adds in the actual checkboxes using the pointers so their positions are set up and they can be drawn
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotEnabled);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotAutoAim);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotAutoCrouch);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotAutoStop);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotAutoShoot);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotControlRecoil);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotSmoothEnabled);
	m_aimbotTab->AddNewSlider(m_aimbotTab->m_column1, aimbotSmoothAmount);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotMultiAimspot);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column1, aimbotGhettoAutowall);
	m_aimbotTab->AddNewSlider(m_aimbotTab->m_column1, aimbotGhettoAutowallModifier);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotVischeck);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotAimstep);
	m_aimbotTab->AddNewSlider(m_aimbotTab->m_column2, aimbotAimstepThreshold);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotAutoScope);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotTargetEnemy);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotTargetTeam);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotSilentAim);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotDisableWhenNoGunOut);
	m_aimbotTab->AddNewCheckbox(m_aimbotTab->m_column2, aimbotDisableWhenReloading);
	m_aimbotTab->AddNewDropDownBar(m_aimbotTab->m_column2, aimbotAimTarget);


	m_espTab->AddNewCheckbox(m_espTab->m_column1, espEspEnabled);
	m_espTab->AddNewCheckbox(m_espTab->m_column1, espNameEsp);
	m_espTab->AddNewCheckbox(m_espTab->m_column1, espWeaponEsp);
	m_espTab->AddNewCheckbox(m_espTab->m_column1, espBoxEsp);
	m_espTab->AddNewCheckbox(m_espTab->m_column2, espDrawEnemy);
	m_espTab->AddNewCheckbox(m_espTab->m_column2, espDrawTeam);
	m_espTab->AddNewCheckbox(m_espTab->m_column2, espArmorBar);
	m_espTab->AddNewCheckbox(m_espTab->m_column2, espHealthBar);
	m_espTab->AddNewCheckbox(m_espTab->m_column2, espHealthBasedColor);

	m_visualTab->AddNewCheckbox(m_visualTab->m_column1, visualRemoveScope);

	m_miscTab->AddNewCheckbox(m_miscTab->m_column1, miscReduceFlash);
	m_miscTab->AddNewSlider(m_miscTab->m_column1, miscNewFlashAlpha);
	//m_miscTab->AddNewCheckbox(m_miscTab->m_column1, miscSlowFall); //temporarily removed cuz it seems to cause crash
	m_miscTab->AddNewCheckbox(m_miscTab->m_column1, miscBunnyHopEnabled);
	m_miscTab->AddNewCheckbox(m_miscTab->m_column1, miscBunnyHopAutoStrafe);
	m_miscTab->AddNewCheckbox(m_miscTab->m_column1, miscBunnyHopSilentStrafe);
	m_miscTab->AddNewCheckbox(m_miscTab->m_column1, miscChatSpamEnabled);
	//m_miscTab->AddNewCheckbox(m_miscTab->m_column2, miscFakeLag);
	//m_miscTab->AddNewSlider(m_miscTab->m_column2, miscFakeLagAmount);
	m_miscTab->AddNewCheckbox(m_miscTab->m_column2, miscPositionSpamEnabled);
	m_miscTab->AddNewCheckbox(m_miscTab->m_column2, miscPositionSpamTeam);
	m_miscTab->AddNewCheckbox(m_miscTab->m_column2, miscPositionSpamEnemy);
	m_miscTab->AddNewCheckbox(m_miscTab->m_column2, miscPositionSpamUseTeamChat);

	m_griefTab->AddNewCheckbox(m_griefTab->m_column1, griefGoombaStompEnabled);

	m_hvhTab->AddNewCheckbox(m_hvhTab->m_column1, hvhAntiAimEnabled);
	m_hvhTab->AddNewCheckbox(m_hvhTab->m_column1, hvhShowAntiAimAngles);
	//m_hvhTab->AddNewCheckbox(m_hvhTab->m_column2, hvhFakeAnglesEnabled);
	m_hvhTab->AddNewCheckbox(m_hvhTab->m_column2, hvhResolver);
	m_hvhTab->AddNewCheckbox(m_hvhTab->m_column2, hvhBodyAimUnresolvable);
	//m_hvhTab->AddNewDropDownBar(m_hvhTab->m_column2, hvhFakeYawAntiAim);
	//m_hvhTab->AddNewDropDownBar(m_hvhTab->m_column2, hvhFakePitchAntiAim, true);
	m_hvhTab->AddNewDropDownBar(m_hvhTab->m_column1, hvhYawAntiAim);
	m_hvhTab->AddNewDropDownBar(m_hvhTab->m_column1, hvhPitchAntiAim, true);

	m_configTab->AddNewDropDownBar(m_configTab->m_column1, cfgAvailableConfigs);

	m_configTab->AddNewButton(m_configTab->m_column2, cfgLoadSelected);
	m_configTab->AddNewButton(m_configTab->m_column2, cfgSaveSelected, true);
	m_configTab->AddNewButton(m_configTab->m_column2, cfgCreateNewConfig);
	m_configTab->AddNewButton(m_configTab->m_column2, cfgRefreshList, true);

	//active tab is aimbot tab by default
	m_activeTab = m_aimbotTab.get();
}

void TabManager::DrawTabs()
{
	for (Tab* tab : m_Tabs) // loop through all tabs in the vector
	{
		if (IsValidTabClick(tab)) //if tab is clicked:
		{
			m_activeTab = tab; // set active tab to clicked tab
		}
		if (tab == m_activeTab) //if the current tab is the active one:
		{
			tab->DrawContents(); //draw tab contents (meaning their elements)
		}
		tab->DrawTab(); //display the tabs themselves on the screen
	}
}
void TabManager::GetTabDimensions(Tab* tab, int& tabWidth, int& tabHeight)
{
	int fontWidth, fontHeight; 
	IFace::surface->GetTextSize(Fonts::fontMenu, tab->m_tabName, fontWidth, fontHeight);

	tab->m_textWidth = fontWidth;
	tab->m_textHeight = fontHeight;
	tabWidth = fontWidth + (28 * GMisc::scaleFactor); //tab is gonna be larger than just the bare minimum
	tabHeight = fontHeight + (12 * GMisc::scaleFactor);
	tab->m_tabWidth = tabWidth;
	tab->m_tabHeight = tabHeight;
}
void TabManager::AddNewTab(Tab* newTab)
{
	int numTabs = m_Tabs.size(); //get number of tabs in the vector
	if (!numTabs)
	{
		newTab->m_posX0 = m_mainBody.m_headerPosX0 + 1; //if first tab in the vector, just start at the very left + 1 px
	}
	else
	{
		int priorTabIndex = numTabs - 1; 
		newTab->m_posX0 = m_Tabs[priorTabIndex]->m_posX1 + (6 * GMisc::scaleFactor); //new tab starts at the end of last tab + 2 px (gap)
	}

	int tabWidth, tabHeight;
	GetTabDimensions(newTab, tabWidth, tabHeight); 

	newTab->m_posX1 = newTab->m_posX0 + tabWidth; //uses width to calculate size of tab
	newTab->m_posY1 = m_mainBody.m_headerPosY1; 
	newTab->m_posY0 = newTab->m_posY1 - tabHeight; //uses height to calculate size of tab

	//Column positioning and calculations
	int bodyLeftSide = m_mainBody.m_posX0 + (20 * GMisc::scaleFactor), bodyCenter = (m_mainBody.m_posX0 + m_mainBody.m_posX1) / 2;
	int bodyTopSide = m_mainBody.m_posY0 + (30 * GMisc::scaleFactor), bodyBottom = m_mainBody.m_posY1;
	int bodyRightSide = m_mainBody.m_posX1 - (20 * GMisc::scaleFactor);

	//Call the constructor (set the pos of) the tab's columns (note: i had to put the columns as a tab member var because otherwise 
	// the position of the tab's elements would be affected by other tabs if the columns were shared
	newTab->m_column1 = std::make_unique<Column>(bodyLeftSide, bodyTopSide, bodyCenter, bodyBottom);
	newTab->m_column2 = std::make_unique<Column>(bodyCenter, bodyTopSide, bodyRightSide, bodyBottom);

	//Add the tab into the tabs vector so they can be iterated through
	m_Tabs.push_back(newTab);
}
bool TabManager::IsValidTabClick(Tab* tab)
{
	return MenuUtil::IsValidClick(tab->m_posX0, tab->m_posY0, tab->m_posX1, tab->m_posY1);
}
#include "stdafx.h"
#include "MenuUtil.h"
#include "ButtonCode_t.h"
#include "Global Interfaces.h"

bool MenuUtil::IsBeingClicked(int elementX0, int elementY0, int elementX1, int elementY1)
{
	int mouseX, mouseY;
	IFace::surface->GetCursorPos(mouseX, mouseY);

	if (IFace::inputsystem->IsButtonDown(ButtonCode_t::MOUSE_LEFT) &&
		mouseX > elementX0 && mouseX < elementX1 && mouseY > elementY0 && mouseY < elementY1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MenuUtil::IsValidClick(int elementX0, int elementY0, int elementX1, int elementY1)
{
	if (!IsBeingClicked(elementX0, elementY0, elementX1, elementY1))
		return false;

	int clickTick = IFace::inputsystem->GetButtonPressedTick(ButtonCode_t::MOUSE_LEFT);
	static int oldClickTick = 0;

	if ((clickTick - oldClickTick) > 150)
	{
		oldClickTick = clickTick;
		return true;
	}
	else
	{
		return false;
	}
}
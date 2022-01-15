#include "stdafx.h"
#include "KeyToggle.h"

void KeyToggle::KeyPressToggle(unsigned int virtualKeyCode, bool& varToToggle)
{
	if (!m_keyDown && GetAsyncKeyState(virtualKeyCode) & 0x8000)
	{
		m_keyDown = true;
		varToToggle = !varToToggle;
	}
	else if (GetAsyncKeyState(virtualKeyCode) == 0)
	{
		m_keyDown = false;
	}
}
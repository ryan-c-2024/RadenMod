#pragma once

class KeyToggle
{
public:
	void KeyPressToggle(unsigned int virtualKeyCode, bool& varToToggle);
private:
	bool m_keyDown = false;
};
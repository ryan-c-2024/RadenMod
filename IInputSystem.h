#pragma once
#include "Util.h"

enum ButtonCode_t;

class IAppSystem
{
public:
	virtual ~IAppSystem() {};
};

class IInputSystem : public IAppSystem
{
public:
	virtual ~IInputSystem() {};

	// Is a button down? "Buttons" are binary-state input devices (mouse buttons, keyboard keys)
	inline bool IsButtonDown(ButtonCode_t code) 
	{
		typedef bool(__thiscall* tFunc) (void*, ButtonCode_t);
		return Util::CallVirtualFunction<tFunc>(this, 15)(this, code);
	}
	// Enables/disables input. PollInputState will not update current 
	// button/analog states when it is called if the system is disabled.
	inline void EnableInput(bool bEnable)
	{
		typedef void(__thiscall* tFunc) (void*, bool);
		Util::CallVirtualFunction<tFunc>(this, 11)(this, bEnable);
	}
	inline int GetPollTick()
	{
		typedef int(__thiscall* tFunc) (void*);
		return Util::CallVirtualFunction<tFunc>(this, 14)(this);
	}
	inline int GetButtonPressedTick(ButtonCode_t code)
	{
		typedef int(__thiscall* tFunc) (void*, ButtonCode_t);
		return Util::CallVirtualFunction<tFunc>(this, 16)(this, code);
	}
	inline int GetButtonReleasedTick(ButtonCode_t code)
	{
		typedef int(__thiscall* tFunc) (void*, ButtonCode_t);
		return Util::CallVirtualFunction<tFunc>(this, 17)(this, code);
	}

};
#pragma once
#include "Util.h"
//#include "ClientClass.h"

class ClientClass;

class IBaseClientDLL
{
public:

	// Request a pointer to the list of client datatable classes
	ClientClass		*GetAllClasses(void) //index 8
	{
		typedef ClientClass* (__thiscall* tFunc) (void*);
		return Util::CallVirtualFunction<tFunc>(this, 8)(this);
	}

	// Mouse Input Interfaces
	// Activate the mouse (hides the cursor and locks it to the center of the screen)
	inline void			IN_ActivateMouse(void) //index 15
	{
		typedef void (__thiscall* tFunc) (void*);
		Util::CallVirtualFunction<tFunc>(this, 15)(this);
	}
	// Deactivates the mouse (shows the cursor and unlocks it)
	inline void			IN_DeactivateMouse(void) //index 16
	{
		typedef void (__thiscall* tFunc) (void*);
		Util::CallVirtualFunction<tFunc>(this, 16)(this);
	}

	// If key is found by name, returns whether it's being held down in isdown, otherwise function returns false
	inline bool			IN_IsKeyDown(const char *name, bool& isdown) //index 19
	{
		typedef bool (__thiscall* tFunc) (void*, const char*, bool&);
		return Util::CallVirtualFunction<tFunc>(this, 19)(this, name, isdown);
	}

};
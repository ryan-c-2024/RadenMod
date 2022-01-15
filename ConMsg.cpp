#include "stdafx.h"
#include "ConMsg.h"

ConMsg Misc::con;

ConMsg::ConMsg()
{
	Msg = reinterpret_cast<MsgFn>(GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg"));
	ColorMsg = reinterpret_cast<ColorMsgFn>(GetProcAddress(GetModuleHandleA("tier0.dll"), "?ConColorMsg@@YAXABVColor@@PBDZZ")); //color doesn't seem to work
}

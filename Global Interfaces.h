#pragma once
#include "IBaseClientDLL.h"
#include "IClientMode.h"
#include "IVEngineClient.h"
#include "IClientEntityList.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IEngineTrace.h"
#include "IInputSystem.h"

namespace IFace
{
	extern IVEngineClient013* engineclient;
	extern IClientMode* clientmode;
	extern IBaseClientDLL* baseclient;
	extern IClientEntityList* entitylist;
	extern vgui::IPanel* panel;
	extern vgui::ISurface* surface;
	extern IEngineTrace* enginetrace;
	extern IInputSystem* inputsystem;
}

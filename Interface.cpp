#include "stdafx.h"
#include "Interface.h"
#include "Global Interfaces.h"
#include <exception>
#include "ConMsg.h"

IBaseClientDLL* IFace::baseclient = nullptr;
IVEngineClient013* IFace::engineclient = nullptr;
IClientMode* IFace::clientmode = nullptr;
IClientEntityList* IFace::entitylist = nullptr;
vgui::IPanel* IFace::panel = nullptr;
vgui::ISurface* IFace::surface = nullptr;
IEngineTrace* IFace::enginetrace = nullptr;
IInputSystem* IFace::inputsystem = nullptr;

CInterface GMisc::iface;

void CInterface::Init()
{
	try
	{
		IFace::baseclient = GetInterfaceAndVersion<IBaseClientDLL*>("VClient", "client.dll");
		IFace::engineclient = GetInterfaceAndVersion<IVEngineClient013*>("VEngineClient", "engine.dll");
		IFace::entitylist = GetInterfaceAndVersion<IClientEntityList*>("VClientEntityList", "client.dll");
		IFace::clientmode = **reinterpret_cast<IClientMode***>((*(uintptr_t**)IFace::baseclient)[10] + 0x5);
		IFace::panel = GetInterfaceAndVersion<vgui::IPanel*>("VGUI_Panel", "vgui2.dll");
		IFace::surface = GetInterfaceAndVersion<vgui::ISurface*>("VGUI_Surface", "vguimatsurface.dll");
		IFace::enginetrace = GetInterfaceAndVersion<IEngineTrace*>("EngineTraceClient", "engine.dll");
		IFace::inputsystem = GetInterfaceAndVersion<IInputSystem*>("InputSystemVersion", "inputsystem.dll");
	}
	catch (const std::string& exc)
	{
		ConMsg con;
		con.Msg("ERROR DURING JEBHOOK INITIALIZATION: %s", exc);
	}
	
	//VEngineCvar007
}


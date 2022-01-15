#include "stdafx.h"
#include "HookManager.h"
#include "HookedFunctions.h"
#include "Global Hooks.h"

CVFHook* GHook::clientmode = nullptr;
CVFHook* GHook::panel = nullptr;
CVFHook* GHook::baseclient = nullptr;

void HookManager::InitHooks()
{
	GHook::clientmode = new CVFHook(IFace::clientmode);
	GHook::panel = new CVFHook(IFace::panel);
	GHook::baseclient = new CVFHook(IFace::baseclient);

	GHook::clientmode->HookFunc(24, &HookedFunc::CreateMove);
	GHook::panel->HookFunc(41, &HookedFunc::PaintTraverse);
//	GHook::baseclient->HookFunc(36, &HookedFunc::FrameStageNotify);
	//GHook::baseclient->HookFunc(21, &HookedFunc::BaseClientCreateMoveNaked);
}

void HookManager::Reset()
{
	//delete GHook::clientmode;
	//delete GHook::panel;
	GHook::clientmode->UnhookFunc(24);
	GHook::panel->UnhookFunc(41);
	GHook::baseclient->UnhookFunc(36);
//	GHook::baseclient->UnhookFunc(21);
}


#include "stdafx.h"
#include "HookedFunctions.h"
#include "Global Hooks.h"
#include "CResolver.h"

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

typedef void(__stdcall* tFrameStageNotify) (ClientFrameStage_t);

void __stdcall HookedFunc::FrameStageNotify(ClientFrameStage_t curStage)
{
	GHook::baseclient->CallOriginalFunc<tFrameStageNotify>(36)(curStage);
	switch (curStage)
	{
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		GMisc::resolver.Run();
		break;
	}
}
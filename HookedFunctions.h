#pragma once

class CUserCmd;
typedef unsigned int VPANEL;
enum ClientFrameStage_t;

namespace HookedFunc
{
	bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* cmd);
	void __stdcall BaseClientCreateMoveNaked(int sequence_number, float input_sample_frametime, bool active);
	void __stdcall BaseClientCreateMove(int sequence_number, float input_sample_frametime, bool active);			// True if the player is active (not paused)
	void __fastcall PaintTraverse(void* pThis, void* EDX, VPANEL vguiPanel, bool forceRepaint, bool allowForce = true);
	void __stdcall FrameStageNotify(ClientFrameStage_t curStage);
}
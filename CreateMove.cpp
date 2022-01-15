
#include "stdafx.h"

#include "HookedFunctions.h"
#include "CBasePlayer.h"
#include "CUserCmd.h"
#include "Features.h"
#include "CBaseCombatWeapon.h"
#include "Global Hooks.h"

//CL_Move -> CHLClient::CreateMove -> CInput::CreateMove -> IClientMode::CreateMove -> CBasePlayer::CreateMove -> CBaseCombatWeapon::CreateMove

bool __stdcall HookedFunc::CreateMove(float flInputSampleTime, CUserCmd* cmd)
{
	try //hooray for error handling try-catch statements
	{
		GPtr::cmd = cmd;
		GPtr::pLocalPlayer = Util::GetLocalPlayerPointer();
		GPtr::pLocalWep = GPtr::pLocalPlayer->GetWeapon();

		GMisc::bhop.Run();
		GMisc::antiaim.Run();
		GMisc::aimbot.Run();
		GMisc::goombastomp.Run();
		GMisc::misc.RunAllMisc();
		
		//GPtr::pLocalPlayer->SetSendPacket(false);
		cmd->viewangles.ClampAndNormalizeAngles();
		cmd->ClampMovement();
	}
	catch (const std::exception& exc)
	{
		if (IFace::engineclient)
		{
			//IFace::engineclient->Con_NPrintf(1, "ISSUE IN CREATEMOVE: %s", exc.what());
		}
	}
	catch (...)
	{
		if (IFace::engineclient)
		{
			//IFace::engineclient->Con_NPrintf(1, "ISSUE IN CREATEMOVE");
		}
	}
	
	return false;
}

/*
void __declspec(naked) __stdcall HookedFunc::BaseClientCreateMoveNaked(int sequence_number, float input_sample_frametime, bool active)
{
__asm
{
// CreateMove stack frame hasn't been created yet
// which leaves us in CL_Move's stack frame, so we save it
MOV stackFrame, EBP

// initial stack pointer value of CreateMove
// we can use this as an additional frame of reference
MOV createMoveEsp, ESP

// save the return address of CreateMove
PUSH EAX
MOV EAX, [ESP + 0x4]
MOV createMoveReturn, EAX
POP EAX

// since the CreateMove args are currently at ESP + 0x4,
// we need to preemptively correct the stack pointer for when
// CALL pushes return address (thus decrementing the stack pointer)
ADD ESP, 0x4

// call the original function
CALL BaseClientCreateMove

// return execution to CL_Move
JMP createMoveReturn
};
}

typedef void(__stdcall* tBaseClientCreateMove) (int, float, bool);
void __stdcall HookedFunc::BaseClientCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
GHook::baseclient->CallOriginalFunc<tBaseClientCreateMove>(21)(sequence_number, input_sample_frametime, active);
IFace::engineclient->Con_NPrintf(2, "hh hello");
__asm
{
PUSHAD
};
__asm
{
POPAD
};
}
*/


CLocalPlayer* GPtr::pLocalPlayer = nullptr;
CUserCmd* GPtr::cmd = nullptr;
bool* GPtr::sendPacket = nullptr;
bool GMisc::sendPacket = true;

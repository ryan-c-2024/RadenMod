#pragma once
#include "QAngle.h"
#include "Vector.h"
//typedef char BYTE; //not sure if this is how it is in the Source SDK...

class CUserCmd //had to pad this myself because nothing else works
{
public:
	/*
	char _pad0[0x4];
	int command_number;
	int tick_count;
	QAngle viewangles;
	char _pad1[0xC];
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	char _pad2[0xC];
	//int random_seed;
	short	mousedx;		// mouse accum in x from create move
	short	mousedy;		// mouse accum in y from create move

	*/
	
	inline void ClampMovement();

	virtual ~CUserCmd() {};
	int command_number;
	int tick_count;
	QAngle viewangles;
	QAngle aimdirection;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	unsigned char impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
	QAngle headangles;
	Vector headoffset;
	

};

void CUserCmd::ClampMovement()
{
	if (this->forwardmove > 450.0)
	{
		this->forwardmove = 450.0;
	}
	else if (this->forwardmove < -450.0)
	{
		this->forwardmove = -450.0;
	}
	if (this->sidemove > 450.0)
	{
		this->sidemove = 450.0;
	}
	else if (this->sidemove < -450.0)
	{
		this->sidemove = -450.0;
	}
}

namespace GPtr
{
	extern CUserCmd* cmd;
	extern bool* sendPacket;
}

namespace GMisc
{
	extern bool sendPacket;
}

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_ATTACK3		(1 << 25)
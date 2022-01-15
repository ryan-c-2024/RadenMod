#pragma once
#include "QAngle.h"

class CAntiAim
{
public:
	void Run();
private:
	void PreFixMovement();
	void FixMovement();
	void DoPitchAntiAim();
	void DoYawAntiAim();
	void DoFakeYawAntiAim();
	void DoFakePitchAntiAim();
	//add jittering to an antiaim
	void AddJitter(int maxDifference);
	void PlaySong(const char* songName, int antiAimVar, int songAntiAim);
	inline bool HasGrenadeOut();
	float m_forwardmove, m_sidemove, m_upmove;
	bool m_shouldFake;

	float m_oldYaw = 0;
};

namespace GMisc
{
	extern CAntiAim antiaim;
}
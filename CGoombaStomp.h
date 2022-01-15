#pragma once
#include "Vector.h"
class CBasePlayer;

class CGoombaStomp
{
public:
	void Run();
private:
	void FindTarget();
	void TrackTarget();

	CBasePlayer* m_pTargetEntity;
	Vector m_vecTargetPos;
	Vector m_vecPlayerPos;
//	Vector m_vecDelta;
	float m_flBestDist;

	float m_flYawDeltaStep;
};

namespace GMisc
{
	extern CGoombaStomp goombastomp;
}

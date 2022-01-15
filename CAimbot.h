#pragma once
#include <vector>

class CBasePlayer;
class QAngle;

class CAimbot
{
public:
	void Run();
	CAimbot();

	bool m_bIsTargeting = false;
	bool m_bAimstepping = false;
private:
	void FindTarget();
	void CalculateAndAim();
	bool ShouldTarget();
	void CalculateAngles(QAngle& angOutput);
	void AimAtTarget(QAngle& angLocalPlayer, QAngle& angLocalPlayerOld);
	inline void SmoothAim(QAngle& angOld, QAngle& angOutput, float flSmoothSpeed);
	inline void DoRecoilControl(QAngle& angOutput, float flRCSFactor);
	inline void DoAutoStop(QAngle& angNew);
	inline void DoAutoShoot();
	inline void DoAutoCrouch();
	inline void DoAutoScope();
	inline void DoAimStep(QAngle& angNew, QAngle& angOld, const float angleChangePerStep);
	//Returns true if target bone is visible and false if not
	inline bool AimspotVisible(CBasePlayer* entity, int aimBone);
	//Loop through m_aimBones and use first visible bone found. If no bones visible, returns -1
	int FindBone(CBasePlayer* entity);

	__forceinline float GetDelta(float newYaw, float oldYaw) const;

	CBasePlayer* m_pEnt;
	CBasePlayer* m_pBestTarget;
	CBasePlayer* m_pLocalPlayer;
	
	int m_targetBone = 10;
	bool m_bSmoothing;

	std::vector<int> m_aimBones;
};

namespace GMisc
{
	extern CAimbot aimbot;
}

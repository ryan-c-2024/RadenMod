#pragma once
#include <set>

class CBasePlayer;

class CResolver
{
public:
	void Run();
	bool ShouldBodyAim(CBasePlayer* entity);
private:
	bool DidLowerBodyYawUpdate(CBasePlayer* entity);
	void ResolvePitch(CBasePlayer* entity);
	void ResolveYaw(CBasePlayer* entity);
	std::set<CBasePlayer*> m_BodyAimTargets;
};

struct LowerBodyYaw
{
	float m_flYaw;
};

namespace GMisc
{
	extern CResolver resolver;
}
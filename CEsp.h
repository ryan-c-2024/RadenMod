#pragma once
#include "Vector.h"

class CBasePlayer;
class Color;

class CEsp
{
public:
	void Run();
private:
	void FindEntities();
	bool ShouldDrawEntity();

	void CalculateEsp();
	void DrawEsp();

	void DrawBoxEsp(Color& boxcolor);
	void DrawHealthBar();
	void DrawArmorBar();
	void DrawNameEsp();
	void DrawWeaponEsp();
	
	Color GetHealthColor(int health);

	void DisplayBonePositions();

	CBasePlayer* m_pEntity = nullptr;
	Vector m_vecTargetOrigin;
	Vector m_vecTargetTop;

	float m_flTargetHeight;
	float m_flTargetWidth;

	bool m_bOnLocalPlayerTeam;

	int m_iNumTextEsps = 0;
};

namespace GMisc
{
	extern CEsp esp;
}

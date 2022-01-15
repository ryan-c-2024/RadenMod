#pragma once
#include <string>
struct FileWeaponInfo_t;

class CBaseCombatWeapon 
{
public:
	//void* GetOwnerHandle();
	int GetClip1();
	int GetPrimaryReserveAmmo();
	int GetSecondaryReserveAmmo();
	uintptr_t GetWorldModelHandle();
	int GetNumEmptyAttacks();
	int GetViewModelIndex();
	FileWeaponInfo_t& GetWpnData(void);

	float GetNextPrimaryAttack();
	float GetNextSecondaryAttack();

	int GetWeaponID();
	std::string GetWeaponName();
};

namespace GPtr
{
	extern CBaseCombatWeapon* pLocalWep;
}
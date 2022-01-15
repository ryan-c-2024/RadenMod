#include "stdafx.h"
#include "CBaseCombatWeapon.h"
#include "Offsets.h"
#include "WeaponID.h"
#include "Util.h"

CBaseCombatWeapon* GPtr::pLocalWep = nullptr;

float CBaseCombatWeapon::GetNextPrimaryAttack()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flNextPrimaryAttack);
}

float CBaseCombatWeapon::GetNextSecondaryAttack()
{
	return *(float*)((uintptr_t)this + GMisc::offset.m_flNextSecondaryAttack);
}

int CBaseCombatWeapon::GetClip1()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iClip1);
}

int CBaseCombatWeapon::GetPrimaryReserveAmmo()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iPrimaryReserveAmmoCount);
}

int CBaseCombatWeapon::GetSecondaryReserveAmmo()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iSecondaryReserveAmmoCount);
}

uintptr_t CBaseCombatWeapon::GetWorldModelHandle()
{
	return *(uintptr_t*)((uintptr_t)this + GMisc::offset.m_hWeaponWorldModel);
}

int CBaseCombatWeapon::GetNumEmptyAttacks()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iNumEmptyAttacks);
}

int CBaseCombatWeapon::GetViewModelIndex()
{
	return *(int*)((uintptr_t)this + GMisc::offset.m_iViewModelIndex);
}

int CBaseCombatWeapon::GetWeaponID()
{
	if (this)
	{
		return *(int*)((uintptr_t)this + GMisc::offset.m_AttributeManager + GMisc::offset.m_Item + GMisc::offset.m_iItemDefinitionIndex);
	}
}

std::string CBaseCombatWeapon::GetWeaponName()
{
	int weaponID = GetWeaponID();
	if (weaponID)
	{
		return WeaponIDToName.at(weaponID);
	}
	else
	{
		return "";
	}
}

struct FileWeaponInfo_t
{
	int hi;
};

FileWeaponInfo_t& CBaseCombatWeapon::GetWpnData()
{
	typedef FileWeaponInfo_t& (__thiscall* tFunc) ();
	return Util::CallVirtualFunction<tFunc>(this, 446)();
}
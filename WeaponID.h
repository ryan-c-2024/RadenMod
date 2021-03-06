#pragma once
#include <map>

enum WeaponID
{
	Weapon_None = 0,
	Weapon_Deagle,
	Weapon_Elite,
	Weapon_Fiveseven,
	Weapon_Glock,
	Weapon_P228,
	Weapon_Usp,
	Weapon_Ak47,
	Weapon_Aug,
	Weapon_Awp,
	Weapon_Famas,
	Weapon_G3sg1,
	Weapon_Galil,
	Weapon_Galilar,
	Weapon_M249,
	Weapon_M3,
	Weapon_M4a4,
	Weapon_Mac10,
	Weapon_Mp5navy,
	Weapon_P90,
	Weapon_Scout,
	Weapon_Sg550,
	Weapon_Sg552,
	Weapon_Tmp,
	Weapon_Ump45,
	Weapon_Xm1014,
	Weapon_Bizon,
	Weapon_Mag7,
	Weapon_Negev,
	Weapon_Sawedoff,
	Weapon_Tec9,
	Weapon_Taser,
	Weapon_Hkp2000,
	Weapon_Mp7,
	Weapon_Mp9,
	Weapon_Nova,
	Weapon_P250,
	Weapon_Scar17,
	Weapon_Scar20,
	Weapon_Sg556,
	Weapon_Ssg08,
	Weapon_Knifegg,
	Weapon_KnifeCT,
	Weapon_Flashbang,
	Weapon_Hegrenade,
	Weapon_Smokegrenade,
	Weapon_Molotov,
	Weapon_Decoy,
	Weapon_Incgrenade,
	Weapon_C4,
	Weapon_KnifeT = 59,
	Weapon_M4a1S
};

extern std::map<int, std::string> WeaponIDToName;
#pragma once
#include "Singleton.h"
#include <vector>
#include "Weapon.h"

class WeaponManager : public Singleton<WeaponManager>
{
public:
	WeaponManager();
	~WeaponManager();
	void ShowList(int type,Weapon *& weapon);
private:
	vector<Weapon*> m_Weapons;
};
//
//WEAPON_DAGGER = 0,
//WEAPON_GUN,
//WEAPON_SWORD,
//WEAPON_WAND,
//WEAPON_BOW,
//WEAPON_HAMMER,

#pragma once
#include "Singleton.h"
#include <list>
#include "Weapon.h"

class WeaponManager : public Singleton<WeaponManager>
{
public:
	WeaponManager();
	~WeaponManager();
	void ShowList(int type,Weapon *& weapon);
private:
	list<Weapon*> m_Weapons;
};

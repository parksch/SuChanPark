#pragma once
#include "Singleton.h"
#include <list>
#include "Weapon.h"


class Player;

class WeaponManager : public Singleton<WeaponManager>
{
public:
	WeaponManager();
	~WeaponManager();
	void ShowList(int type,Inventory *inventory);
private:
	list<Weapon*> m_Weapons;
};

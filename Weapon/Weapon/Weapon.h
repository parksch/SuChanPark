#pragma once
#include "Macro.h"
#include "Inventory.h"
enum WEAPON
{
	WEAPON_START,
	WEAPON_DAGGER = 0,
	WEAPON_GUN,
	WEAPON_SWORD,
	WEAPON_WAND,
	WEAPON_BOW,
	WEAPON_HAMMER,
	WEAPON_END,
};

class Weapon : public Item 
{
protected:
	WEAPON m_eType;
	int m_iDamage;
	int m_iGold;
public:
	void View();
	inline WEAPON GetType()
	{
		return m_eType;
	}
	inline int GetGold()
	{
		return m_iGold;
	}
	inline int GetAttack()
	{
		return m_iDamage;
	}
	void ShowShopInfo();
	Weapon(string name);
	virtual ~Weapon();
};

class Bow : public Weapon
{
public:
	Bow();
	Bow(Bow* bow);
	Bow(string Name, int Damage, int Gold);
	~Bow();
};

class Dagger : public Weapon
{
public:
	Dagger();
	Dagger(Dagger* dagger);
	Dagger(string Name, int Damage, int Gold);
	~Dagger();
};

class Gun : public Weapon
{
public:
	Gun();
	Gun(Gun* gun);
	Gun(string Name, int Damage, int Gold);
	~Gun();
};

class Sword : public Weapon
{
public:
	Sword();
	Sword(Sword* sword);
	Sword(string Name, int Damage, int Gold);
	~Sword();
};

class Wand : public Weapon
{
public:
	Wand();
	Wand(Wand* sword);
	Wand(string Name, int Damage, int Gold);
	~Wand();
};

class Hammer : public Weapon
{
public:
	Hammer();
	Hammer(Hammer* hammer);
	Hammer(string Name, int Damage, int Gold);
	~Hammer();
};
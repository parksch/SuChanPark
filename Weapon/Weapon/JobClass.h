#pragma once
#include "Macro.h"
#include "Weapon.h"

class Character
{
public:
	Character();
	 ~Character();
	virtual bool EquipCheck(Inventory* item) = 0;
	inline Inventory* GetInventory() { return bag; }
	void SetWeapon(Weapon* _weapon);
	void DisplayAll();
protected:
	Weapon* GetWeapon();
private:
	Weapon* weapon;
	Bag *bag;
};

class Knight : public Character
{
public:
	Knight() {};
	~Knight() {};
	virtual bool EquipCheck(Inventory* item);
};

class Archer : public Character
{
public:
	Archer() {};
	~Archer() {};
	virtual bool EquipCheck(Inventory* item);
};

class Wizard : public Character
{
public:
	Wizard() {};
	~Wizard() {};
	virtual bool EquipCheck(Inventory* item);
};

class Thiff : public Character
{
public:
	Thiff() {};
	~Thiff() {};
	virtual bool EquipCheck(Inventory* item);
};
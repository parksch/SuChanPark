#pragma once
#include "Macro.h"
#include "Weapon.h"

class JobClass
{
public:
	void SetWeapon(Weapon* _weapon);
	virtual bool EquipCheck(Inventory* item) = 0;
	void DisplayAll();
	inline Inventory* GetInventory() { return bag; }
private:
	Bag *bag;
protected:
	Weapon* GetWeapon();
private:
	Weapon * weapon;

};

class Knight : public JobClass
{
public:
	virtual bool EquipCheck(Inventory* item);
};

class Archer : public JobClass
{
public:
	virtual bool EquipCheck(Inventory* item);
};

class Wizard : public JobClass
{
public:
	virtual bool EquipCheck(Inventory* item);
};

class Thiff : public JobClass
{
public:
	virtual bool EquipCheck(Inventory* item);
};
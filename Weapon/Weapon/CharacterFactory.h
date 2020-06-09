#pragma once
#include "Macro.h"
#include "Weapon.h"
#include "JobClass.h"

class CharacterFactory
{
public:
	~CharacterFactory();

	virtual Weapon * CreateWeapon() = 0;
	virtual JobClass* CreateJobClass() = 0;
};

class KnightCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass* CreateJobClass();
};

class ArcherCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass* CreateJobClass();
};

class WizardCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass* CreateJobClass();
};

class ThiffCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual JobClass * CreateJobClass();
};
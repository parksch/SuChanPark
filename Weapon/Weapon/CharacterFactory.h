#pragma once
#include "Macro.h"
#include "Weapon.h"
#include "JobClass.h"

class CharacterFactory
{
public:
	~CharacterFactory();

	virtual Weapon * CreateWeapon() = 0;
	virtual Character* CreateJobClass() = 0;
};

class KnightCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Character* CreateJobClass();
};

class ArcherCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Character* CreateJobClass();
};

class WizardCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Character* CreateJobClass();
};

class ThiffCharacter : public CharacterFactory
{
public:
	virtual Weapon * CreateWeapon();
	virtual Character * CreateJobClass();
};
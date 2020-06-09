#include "CharacterFactory.h"

CharacterFactory::~CharacterFactory()
{
}

Weapon * KnightCharacter::CreateWeapon()
{
	return new Sword("맨손",1,0);
}

JobClass * KnightCharacter::CreateJobClass()
{
	return new Knight();
}

Weapon * ArcherCharacter::CreateWeapon()
{
	return new Bow("맨손", 1, 0);
}

JobClass * ArcherCharacter::CreateJobClass()
{
	return new Archer();
}

Weapon * WizardCharacter::CreateWeapon()
{
	return new Wand("맨손",1,0);
}

JobClass * WizardCharacter::CreateJobClass()
{
	return new Wizard();
}

Weapon * ThiffCharacter::CreateWeapon()
{
	return new Dagger("맨손", 1, 0);
}

JobClass * ThiffCharacter::CreateJobClass()
{
	return new Thiff();
}

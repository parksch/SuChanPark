#include "CharacterFactory.h"

CharacterFactory::~CharacterFactory()
{
}

Weapon* KnightCharacter::CreateWeapon()
{
	return new Sword("맨손",1,0);
}

Character* KnightCharacter::CreateJobClass()
{
	return new Knight();
}

Weapon* ArcherCharacter::CreateWeapon()
{
	return new Bow("맨손", 1, 0);
}

Character* ArcherCharacter::CreateJobClass()
{
	return new Archer();
}

Weapon* WizardCharacter::CreateWeapon()
{
	return new Wand("맨손",1,0);
}

Character* WizardCharacter::CreateJobClass()
{
	return new Wizard();
}

Weapon* ThiffCharacter::CreateWeapon()
{
	return new Dagger("맨손", 1, 0);
}

Character* ThiffCharacter::CreateJobClass()
{
	return new Thiff();
}

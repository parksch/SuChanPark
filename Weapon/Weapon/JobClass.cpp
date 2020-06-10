#include "JobClass.h"

Character::Character(): bag(new Bag("Main"))
{
	weapon = NULL;
}

Character::~Character()
{
	if (bag != NULL)
	{
		delete bag;
	}
	if (weapon != NULL)
	{
		delete weapon;
	}
}

void Character::SetWeapon(Weapon * _weapon)
{
	if (weapon != NULL)
	{
		delete weapon;
	}

	weapon =  _weapon;
}

void Character::DisplayAll()
{
	int input;

	while (1)
	{
		system("cls");
		weapon->View();
		bag->View();
		cout << to_string(bag->GetSize() + 1) + ". 나가기" << endl;
		cin >> input;

		if (input < bag->GetSize() + 1)
		{
			if (EquipCheck(bag->FindInventory(input - 1)))
			{
				Weapon*temp = new Weapon(*(Weapon*)bag->FindInventory(input - 1));
				SetWeapon(temp);
				bag->RemoveInventory(bag->FindInventory(input - 1));
			}
			else
			{
			cout << "그 아이템은 장비 할수 없습니다" << endl;
			system("pause");
			}
		}
		else
		{
			return;
		}
	}
}

Weapon * Character::GetWeapon()
{
	return weapon;
}

/* Knight */
bool Knight::EquipCheck(Inventory* item)
{
	Sword* sword = dynamic_cast<Sword*>(item);

	if (sword == NULL)
		return false;

	cout << "검 착용!" << endl;

	return true;
}

/* Archer */
bool Archer::EquipCheck(Inventory* item)
{
	Bow* bow = dynamic_cast<Bow*>(item);

	if (bow == NULL)
		return false;

	cout << "활 착용!" << endl;

	return true;
}

/* Wizard */
bool Wizard::EquipCheck(Inventory* item)
{
	Wand* wand = dynamic_cast<Wand*>(item);

	if (wand == NULL)
		return false;

	cout << "지팡이 착용!" << endl;

	return true;
}

bool Thiff::EquipCheck(Inventory* item)
{
	Dagger* dagger = dynamic_cast<Dagger*>(item);

	if (dagger == NULL) return false;

	cout << "단검 착용!" << endl;

	return true;
}

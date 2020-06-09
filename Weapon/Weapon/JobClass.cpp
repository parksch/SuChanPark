#include "JobClass.h"

void JobClass::SetWeapon(Weapon * _weapon)
{
	weapon = new Weapon(*_weapon);
}

void JobClass::DisplayAll()
{
	int input;

	while (1)
	{
		system("cls");
		bag->View();
		cin >> input;

		if (input < bag->GetSize())
		{
			if (EquipCheck(bag->FindInventory(input - 1)))
			{
				cout << "그 아이템은 장비 할수 없습니다" << endl;
			}
			else
			{
				SetWeapon((Weapon*)bag->FindInventory(input - 1));
				bag->RemoveInventory(bag->FindInventory(input - 1));
			}
		}
		else
		{
			return;
		}
	}
}

Weapon * JobClass::GetWeapon()
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

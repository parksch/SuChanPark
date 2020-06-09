#include "Player.h"

Player::Player(): bag(new Bag("Main"))
{
}

Player::~Player()
{
	delete bag;
}

void Player::DisplayAll()
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


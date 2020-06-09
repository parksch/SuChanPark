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
				cout << "�� �������� ��� �Ҽ� �����ϴ�" << endl;
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


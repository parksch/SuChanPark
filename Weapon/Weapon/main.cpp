#pragma once
#include "WeaponManager.h"
#include "Player.h"

void Shop(Player *player);
void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	int input;
	Player player;

	while (1)
	{
		system("cls");
		cout << "♧ ♣ S H O P ♣ ♧" << endl;
		cout << "1.Inventory" << endl;
		cout << "2.Shop" << endl;
		cout << "3. 종료" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			player.DisplayAll();
			break;
		case 2:
			Shop(&player);
			break;
		default:
			WeaponManager::DestoryInstance();
			return;
		}
	}
}

void Shop(Player * player)
{
	int input;

	while (1)
	{
		system("cls");
		cout << "♧ ♣ S H O P ♣ ♧" << endl;
		cout << "1.Dagger" << endl;
		cout << "2.Gun" << endl;
		cout << "3.Sword" << endl;
		cout << "4.Wand" << endl;
		cout << "5.Bow" << endl;
		cout << "6.Hammer" << endl;
		cout << "7. 종료" << endl;
		cin >> input;

		if (input < 7)
		{
			WeaponManager::GetInstance()->ShowList(input - 1,player->GetInventory());
		}
		else
		{
			return;
		}
	}
}

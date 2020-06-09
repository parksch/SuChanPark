#pragma once
#include "WeaponManager.h"
#include "CharacterFactory.h"
#include "Player.h"
#include<crtdbg.h>

void Shop(JobClass *&player);
void Init(JobClass *&player);
void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	JobClass *player;
	Init(player);
	int input;

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
			player->DisplayAll();
			break;
		case 2:
			Shop(player);
			break;
		default:
			WeaponManager::DestoryInstance();
			return;
		}
	}
}

void Shop(Player *&player)
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

void Init(Player *&player)
{
	int input;
	while (1)
	{
		system("cls");
		cout << "당신의 직업을 선택 하세요" << endl;
		cout << "1.Knight" << endl;
		cout << "2.Archer" << endl;
		cout << "3.Thiff" << endl;
		cout << "4.Wizard" << endl;
		cin >> input;
		switch (input)
		{
		case 1:
			player = (Player*)KnightCharacter().CreateJobClass();
			player->SetWeapon(KnightCharacter().CreateWeapon());
			return;
		case 2:
			player = (Player*)ArcherCharacter().CreateJobClass();
			player->SetWeapon(ArcherCharacter().CreateWeapon());
			return;
		case 3:
			player = (Player*)ThiffCharacter().CreateJobClass();
			player->SetWeapon(ArcherCharacter().CreateWeapon());
			return;
		case 4:
			player = (Player*)WizardCharacter().CreateJobClass();
			player->SetWeapon(ArcherCharacter().CreateWeapon());
			return;
		default:
			break;
		}
	}
}

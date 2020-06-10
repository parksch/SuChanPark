#pragma once
#include "WeaponManager.h"
#include "CharacterFactory.h"
#include<crtdbg.h>

void Shop(Character *&player);
void Init(Character *&player);
void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	Character *player;
	Init(player);
	int input;

	//while (1)
	//{
	//	system("cls");
	//	cout << "♧ ♣ S H O P ♣ ♧" << endl;
	//	cout << "1.Inventory" << endl;
	//	cout << "2.Shop" << endl;
	//	cout << "3. 종료" << endl;
	//	cin >> input;

	//	switch (input)
	//	{
	//	case 1:
	//		player->DisplayAll();
	//		break;
	//	case 2:
	//		Shop(player);
	//		break;
	//	default:
	//		WeaponManager::DestoryInstance();
	//		return;
	//	}
	//}

	delete player;
}

void Shop(Character *&player)
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

void Init(Character *&player)
{
	int input;
	vector<CharacterFactory*> characterlist;
	characterlist.push_back(new KnightCharacter());
	characterlist.push_back(new ArcherCharacter());
	characterlist.push_back(new ThiffCharacter());
	characterlist.push_back(new WizardCharacter());

	while (1)
	{
		system("cls");
		cout << "당신의 직업을 선택 하세요" << endl;
		cout << "1.Knight" << endl;
		cout << "2.Archer" << endl;
		cout << "3.Thiff" << endl;
		cout << "4.Wizard" << endl;
		cin >> input;

		if (input < characterlist.size() + 1)
		{
			player = characterlist[input - 1]->CreateJobClass();
			player->SetWeapon(characterlist[input - 1]->CreateWeapon());

			for (vector<CharacterFactory*>::iterator i = characterlist.begin(); i != characterlist.end(); i++)
			{
				delete *i;
			}

			vector<CharacterFactory*>().swap(characterlist);
			return;
		}
	}
}

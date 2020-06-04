#pragma once
#include "WeaponManager.h"

void main()
{
	int input;
	Weapon* curWeapon = NULL;

	while (1)
	{
		system("cls");

		if (curWeapon == NULL)
		{
			cout << "���� ���� : ����" << endl;
		}
		else
		{
			cout << "���� ���� :";
			curWeapon->ShowInfo();
		}

		cout << "�� �� S H O P �� ��" << endl;
		cout << "1.Dagger" << endl;
		cout << "2.Gun" << endl;
		cout << "3.Sword" << endl;
		cout << "4.Wand" << endl;
		cout << "5.Bow" << endl;
		cout << "6.Hammer" << endl;
		cout << "7. ����" << endl;
		cin >> input;

		if (input < 7)
		{
			WeaponManager::GetInstance()->ShowList(input - 1,curWeapon);
		}
		else
		{
			WeaponManager::DestoryInstance();
			delete curWeapon;
			return;
		}
	}
}
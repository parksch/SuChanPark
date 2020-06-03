#include "WeaponManager.h"

WeaponManager* WeaponManager::m_This = NULL;

WeaponManager::WeaponManager()
{
	ifstream Load;
	Weapon* temp;
	string strName;
	string strType;
	int iDamage;
	int iGold;
	Load.open("WeaponList.txt");

	if (!Load.is_open())
	{
		return;
	}

	while (!Load.eof())
	{
		Load >> strType;
		Load >> strName;
		Load >> iDamage;
		Load >> iGold;
		if (strType == "Bow")
			m_Weapons.push_back(new Bow(strName, iDamage, iGold));
		else if (strType == "Hammer")
			m_Weapons.push_back(new Hammer(strName, iDamage, iGold));
		else if (strType == "Dagger")
			m_Weapons.push_back(new Dagger(strName, iDamage, iGold));
		else if (strType == "Gun")
			m_Weapons.push_back(new Gun(strName, iDamage, iGold));
		else if (strType == "Sword")
			m_Weapons.push_back(new Sword(strName, iDamage, iGold));
		else if (strType == "Wand")
			m_Weapons.push_back(new Wand(strName, iDamage, iGold));
	}

	Load.close();
}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::ShowList(int type, Weapon *& weapon)
{
	int input;
	int max = 1;
	vector<Weapon*> temp;
	while (1)
	{
		system("cls");

		for (vector<Weapon*>::iterator iter = m_Weapons.begin(); iter != m_Weapons.end(); iter++)
		{
			if ((*iter)->GetType() == (WEAPON)type)
			{
				cout << to_string(max) + ". ";
				(*iter)->ShowShopInfo();
				temp.push_back((*iter));
				max++;
			}
		}

		cin >> input;

		if (input < max)
		{
			if (weapon != NULL)
			{
				delete weapon;
				weapon = NULL;
			}
			if ((WEAPON)type == WEAPON_BOW)
				weapon = new Bow((Bow*)temp[input - 1]);
			else if ((WEAPON)type == WEAPON_HAMMER)
				weapon = new Hammer((Hammer*)temp[input - 1]);
			else if ((WEAPON)type == WEAPON_DAGGER)
				weapon = new Dagger((Dagger*)temp[input - 1]);
			else if ((WEAPON)type == WEAPON_GUN)
				weapon = new Gun((Gun*)temp[input - 1]);
			else if ((WEAPON)type == WEAPON_SWORD)
				weapon = new Sword((Sword*)temp[input - 1]);
			else if ((WEAPON)type == WEAPON_WAND)
				weapon = new Wand((Wand*)temp[input - 1]);
			return;
		}
		else
		{
			return;
		}
	}
}

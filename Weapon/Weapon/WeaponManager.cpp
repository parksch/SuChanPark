#include "WeaponManager.h"

WeaponManager* WeaponManager::m_This = NULL;

bool GoldSort(Weapon* object, Weapon* object2) { return object->GetGold() > object2->GetGold(); }
bool AttackSort(Weapon *object, Weapon *object2) { return object->GetAttack() < object2->GetAttack(); }

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
	int input = 0;
	int max = 1;
	list<Weapon*> temp;

	for (list<Weapon*>::iterator iter = m_Weapons.begin(); iter != m_Weapons.end(); iter++)
	{
		if ((*iter)->GetType() == (WEAPON)type)
		{
			temp.push_back((*iter));
		}
	}

	while (1)
	{
		system("cls");

		for (list<Weapon*>::iterator iter = temp.begin(); iter != temp.end(); iter++)
		{
			cout << to_string(max) + ". ";
			(*iter)->ShowShopInfo();
			max++;
		}

		cout << to_string(temp.size() + 1) + " : 금액 순으로 정렬 " +
			to_string(temp.size() + 2) + " : 공격력 순으로 정렬 " << endl;
		cin >> input;

		if (input < temp.size())
		{
			list<Weapon*>::iterator f = temp.begin();
			for (int i = 0; i < input - 1; i++)
			{
				f++;
			}

			if (type == WEAPON_BOW)
				weapon = new Bow((Bow*)(*f));
			else if (type == WEAPON_HAMMER)
				weapon = new Hammer((Hammer*)(*f));
			else if (type == WEAPON_DAGGER)
				weapon = new Dagger((Dagger*)(*f));
			else if (type == WEAPON_GUN)
				weapon = new Gun((Gun*)(*f));
			else if (type == WEAPON_SWORD)
				weapon = new Sword((Sword*)(*f));
			else if (type == WEAPON_WAND)
				weapon = new Wand((Wand*)(*f));
			return;
		}
		else if (input == temp.size()+1)
		{
			max = 1;
			temp.sort(GoldSort);
		}
		else if (input == temp.size()+2)
		{
			max = 1;
			temp.sort(AttackSort);
		}
		else
		{
			return;
		}
	}
}
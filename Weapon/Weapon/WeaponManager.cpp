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
	for (list<Weapon*>::iterator i = m_Weapons.begin(); i != m_Weapons.end(); i++)
	{
		delete (*i);
	}

	m_Weapons.clear();
}

void WeaponManager::ShowList(int type, Inventory * inventory)
{
	int input = 0;
	int max = 1;
	list<Weapon*> temp;

	for (list<Weapon*>::iterator iter = m_Weapons.begin(); iter != m_Weapons.end(); iter++)
	{
		if ((*iter)->GetType() == (WEAPON)type)
		{
			if (type == WEAPON_BOW)
				temp.push_back(new Bow((Bow*)(*iter)));
			else if (type == WEAPON_HAMMER)
				temp.push_back(new Hammer((Hammer*)(*iter)));
			else if (type == WEAPON_DAGGER)
				temp.push_back(new Dagger((Dagger*)(*iter)));
			else if (type == WEAPON_GUN)
				temp.push_back(new Gun((Gun*)(*iter)));
			else if (type == WEAPON_SWORD)
				temp.push_back(new Sword((Sword*)(*iter)));
			else if (type == WEAPON_WAND)
				temp.push_back(new Wand((Wand*)(*iter)));
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
		cout << to_string(temp.size() + 3) + " : 나가기 " << endl;
		cin >> input;

		if (input < temp.size())
		{
			list<Weapon*>::iterator f = temp.begin();
			for (int i = 0; i < input - 1; i++)
			{
				f++;
			}

			if (type == WEAPON_BOW)
				inventory->FindInventory("Bow")->AddInventory(new Bow((Bow*)(*f)));
			else if (type == WEAPON_HAMMER)
				inventory->FindInventory("Hammer")->AddInventory(new Hammer((Hammer*)(*f)));
			else if (type == WEAPON_DAGGER)
				inventory->FindInventory("Dagger")->AddInventory(new Dagger((Dagger*)(*f)));
			else if (type == WEAPON_GUN)
				inventory->FindInventory("Gun")->AddInventory(new Gun((Gun*)(*f)));
			else if (type == WEAPON_SWORD)
				inventory->FindInventory("Sword")->AddInventory(new Sword((Sword*)(*f)));
			else if (type == WEAPON_WAND)
				inventory->FindInventory("Wand")->AddInventory(new Wand((Wand*)(*f)));

			for (list<Weapon*>::iterator i = temp.begin(); i != temp.end(); i++)
			{
				delete (*i);
			}
			temp.clear();
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

			for (list<Weapon*>::iterator i = temp.begin(); i != temp.end(); i++)
			{
				delete (*i);
			}
			temp.clear();
			return;
		}
	}
}
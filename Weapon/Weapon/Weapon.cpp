#include "Weapon.h"



Weapon::Weapon()
{

}

void Weapon::ShowShopInfo()
{
	string Type;
	switch (m_eType)
	{
	case WEAPON_DAGGER:
		Type = "���";
		break;
	case WEAPON_GUN:
		Type = "��";
		break;
	case WEAPON_SWORD:
		Type = "���";
		break;
	case WEAPON_WAND:
		Type = "������";
		break;
	case WEAPON_BOW:
		Type = "Ȱ";
		break;
	case WEAPON_HAMMER:
		Type = "��ġ";
		break;
	}

	cout << "���� : " + to_string(m_iGold) + " ����Ÿ�� : " + Type << endl;
	cout << " �����̸� : " + m_strName + " ���ݷ� : " + to_string(m_iDamage) << endl;
}

void Weapon::ShowInfo()
{
	string Type;
	switch (m_eType)
	{
	case WEAPON_DAGGER:
		Type = "���";
		break;
	case WEAPON_GUN:
		Type = "��";
		break;
	case WEAPON_SWORD:
		Type = "���";
		break;
	case WEAPON_WAND:
		Type = "������";
		break;
	case WEAPON_BOW:
		Type = "Ȱ";
		break;
	case WEAPON_HAMMER:
		Type = "��ġ";
		break;
	}

	cout << "����Ÿ�� : " + Type + " �����̸� : " + m_strName + " ���ݷ� : " + to_string(m_iDamage) << endl;
}

Weapon::~Weapon()
{

}

Bow::Bow()
{

}
Bow::Bow(Bow* bow)
{
	m_strName = bow->m_strName;
	m_iDamage = bow->m_iDamage;
	m_iGold = bow->m_iGold;
	m_eType = bow->m_eType;
}

Bow::Bow(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iGold = Gold;
	m_eType = WEAPON_BOW;
}
Bow::~Bow()
{

}


Dagger::Dagger()
{

}
Dagger::Dagger(Dagger* dagger)
{
	m_strName = dagger->m_strName;
	m_iDamage = dagger->m_iDamage;
	m_iGold = dagger->m_iGold;
	m_eType = dagger->m_eType;
}

void Save(ofstream& Save)
{

}
Dagger::Dagger(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iGold = Gold;
	m_eType = WEAPON_DAGGER;
}
Dagger::~Dagger()
{

}


Gun::Gun()
{

}
Gun::Gun(Gun* gun)
{
	m_strName = gun->m_strName;
	m_iDamage = gun->m_iDamage;
	m_iGold = gun->m_iGold;
	m_eType = gun->m_eType;
}
Gun::Gun(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iGold = Gold;
	m_eType = WEAPON_GUN;
}
Gun::~Gun()
{

}

Sword::Sword()
{

}
Sword::Sword(Sword* sword)
{
	m_strName = sword->m_strName;
	m_iDamage = sword->m_iDamage;
	m_iGold = sword->m_iGold;
	m_eType = sword->m_eType;
}

Sword::Sword(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iGold = Gold;
	m_eType = WEAPON_SWORD;
}

Sword::~Sword()
{

}



Wand::Wand()
{

}

Wand::Wand(Wand* wand)
{
	m_strName = wand->m_strName;
	m_iDamage = wand->m_iDamage;
	m_iGold = wand->m_iGold;
	m_eType = wand->m_eType;
}

Wand::Wand(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iGold = Gold;
	m_eType = WEAPON_WAND;
}

Wand::~Wand()
{

}


Hammer::Hammer()
{

}

Hammer::Hammer(Hammer* hammer)
{
	m_strName = hammer->m_strName;
	m_iDamage = hammer->m_iDamage;
	m_iGold = hammer->m_iGold;
	m_eType = hammer->m_eType;
}

Hammer::Hammer(string Name, int Damage, int Gold)
{
	m_strName = Name;
	m_iDamage = Damage;
	m_iGold = Gold;
	m_eType = WEAPON_WAND;
}

Hammer::~Hammer()
{

}
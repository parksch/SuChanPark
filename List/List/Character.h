#pragma once
#include <iostream>
#include <string>
using namespace std;

class Character
{
public:
	Character() {}
	Character(string name, int attack): m_Name(name),m_Attack(attack) {};
	~Character();
	friend ostream& operator<< (ostream& os, Character &character) { os << character.m_Name + " " + to_string(character.m_Attack); return os; }
	bool Name(Character &character) { return this->m_Name > character.m_Name; };
	bool Attack(Character &character) { return this->m_Attack > character.m_Attack;}
	bool operator >(Character &character) { return Name(character); }
private:
	string m_Name;
	int m_Attack;
};


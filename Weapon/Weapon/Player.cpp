#include "Player.h"

Player::Player(): bag(new Bag("Main"))
{
	bag->AddInventory(new Bag("Bow"));
	bag->AddInventory(new Bag("Gun"));
	bag->AddInventory(new Bag("Sword"));
	bag->AddInventory(new Bag("Hammer"));
	bag->AddInventory(new Bag("Dagger"));
	bag->AddInventory(new Bag("Wand"));
}

Player::~Player()
{
	delete bag;
}

void Player::DisplayAll()
{
	system("cls");
	bag->View();
	system("pause");
}

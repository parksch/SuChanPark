#pragma once
#include "Inventory.h"

class Player
{
public:
	Player();
	~Player();
	void DisplayAll();
	inline Inventory* GetInventory() { return bag; }
private:
	Inventory *bag;
};


#pragma once
#include "Inventory.h"
#include "JobClass.h"
class Player : public JobClass
{
public:
	Player();
	~Player();
	void DisplayAll();
	inline Inventory* GetInventory() { return bag; }
private:
};


#pragma once
#include "Tank.h"

class Player : public Tank
{
public:
	Player();
	~Player();
	bool Input();
	void GameOver();
	void Update(float eTime);
	void InitAni();
private:
	bool isInput;
};


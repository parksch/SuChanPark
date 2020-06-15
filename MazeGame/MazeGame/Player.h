#pragma once
#include "GameManager.h"
#include "Object.h"

class Player : public Object
{
public:
	Player(int code, int x, int y);
	~Player();
	void Update();
	void Move(char input);
	void Collision_Handle(int Code);
private:
};

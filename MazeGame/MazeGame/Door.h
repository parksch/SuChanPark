#pragma once
#include "GameManager.h"
#include "Object.h"

class Door :public Object
{
public:
	Door(int code, int x, int y);
	~Door();
	void Update() {};
	void Collision_Handle(int Code) {};
private:
};


#pragma once
#include "Object.h"
#include <time.h>
#define DELAY 300
class Trap:public Object
{
public:
	Trap(int code, int x, int y);
	~Trap();
	void Collision_Handle(Object *object, PLAYER_STATE &state);
	void Update(Object**objects, int size, PLAYER_STATE &state);
private:
	int m_OldTime;
	int m_OffsetX;
};


#pragma once
#include "EngineHeader.h"
#define SPAWN_DELAY 5.0f

enum MOVE_STATE
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

enum TYPE
{
	PLAYER = 0,
	ENEMY,
	FLAG
};
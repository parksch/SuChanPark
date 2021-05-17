#pragma once
#include "EngineHeader.h"
#define SPAWN_DELAY 5.0f

enum MOVE_STATE
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

enum GAME_STATE
{
	NOMAL = 0,
	FEVER,
	SUPER_FEVER,
	OVER,
	SCORE_UP,
	SCORE_DOWN
};

enum STAR
{
	YELLOW = 0,
	GREEN,
	BLUE
};


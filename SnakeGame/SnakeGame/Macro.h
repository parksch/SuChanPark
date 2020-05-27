#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define WALL_MAX 30
#define FOOD_MAX 10

using namespace std;

enum TYPE
{
	TYPE_WALL,
	TYPE_FOOD,
	TYPE_SNAKE_HEAD,
	TYPE_SNAKE_BODY,
	TYPE_BROKEN,
	TYPE_NON
};

enum COLLISION
{
	COLLISION_WALL,
	COLLISION_FOOD
};

enum STATE
{
	STATE_WAIT,
	STATE_COLLISION,
	STATE_NON
};

struct Pos
{
	Pos(int x, int y) : m_X(x), m_Y(y) {};
	Pos() {};
	int m_X;
	int m_Y;
};


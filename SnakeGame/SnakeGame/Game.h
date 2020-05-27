#pragma once
#include "Macro.h"
#include "Block.h"
#include "Snake.h"

#define WIDTH 50
#define HEIGHT 30
#define WALL_MAX 30
#define FOOD_MAX 10
#define UPDATETIME 500

enum MENU
{
	MENU_START = 1,
	MENU_EXIT = 2
};

class Game
{
public:
	Game();
	~Game();
private:
	static void ObjectCheck(Block ObjectArray[], int Size, void (Game::*Event)(int), Game* temp);
	inline Snake GetSnake() { return m_Snake; }
	void Menu();
	void Play_Enter();
	void Play_Excute();
	void Play_Exit();
	void CreateFood();
	void CreateWalls();
	void EatFood(int index);
	void CollisionWall(int index);
	int Check(Block *block, Pos pos, int size);
	bool m_Play;
	Pos RandomPos();
	int m_OldTime;
	int m_Score;
	Draw m_Draw;
	Snake m_Snake;
	Block m_WallBlocks[WALL_MAX];
	Block m_FoodBlocks[FOOD_MAX];
};


#pragma once
#include "Macro.h"
#include "Draw.h"
#include "FieldManager.h"

struct Point
{
	int X;
	int Y;
};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void Start();
private:
	void Map_SizeChange();
	void Map_DisPlay(int width,int height);
	void Game_Menu();
	void Game_Enter();
	void Game_Excute();
	void Game_Exit();
	bool Input();
	void Move(int offSetX, int offSetY);
private:
	Draw m_Draw;
	FieldManager m_FieldManager;
	int m_MineSize;
	int m_FlagSize;
	int m_Width;
	int m_Height;
	Point m_Pos;
};


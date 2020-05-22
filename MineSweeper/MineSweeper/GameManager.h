#pragma once
#include "Macro.h"
#include "Draw.h"
#include "MineManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void Start();
private:
	void Game_Menu();
	void Game_Enter();
	void Game_Excute();
	Draw m_Draw;
	MineManager m_MineManager;
};


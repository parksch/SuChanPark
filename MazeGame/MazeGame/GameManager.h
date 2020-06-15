#pragma once
#include "ObjectFactory.h"
#include "Interface.h"

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	void Start();
	int CollisionCheck(Point pos,int code);
	void Stage_Clear();
private:
	void Start_Menu();
	void Game_Enter();
	void Game_Excute();
	void Game_Exit();
	void Stage_Load();
	void Create(int code, int x, int y, int &count);
private:
	int m_CurStage;
	bool isPlay;
	Point MapSize;
	Interface m_Interface;
	list<Point>  m_MovingPoints;
	list<Object*> objects;
};


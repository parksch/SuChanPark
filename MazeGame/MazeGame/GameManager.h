#pragma once
#include "ObjectFactory.h"
#include "Interface.h"
#include <math.h>

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	void Start();
	int CollisionCheck(Point pos,int code);
	int ObjectLength(Point pos, int code);
	void Game_Fail();
	Point ObjectPos(int code);
	void Stage_Clear();
	inline const Point Getsize() { return MapSize; };
private:
	void Start_Menu();
	void Game_Enter();
	void Game_Excute();
	void Game_Exit();
	void Stage_Load();
private:
	int m_CurStage;
	bool isPlay;
	Point MapSize;
	Interface m_Interface;
	list<Point>  m_MovingPoints;
	list<Object*> objects;
};


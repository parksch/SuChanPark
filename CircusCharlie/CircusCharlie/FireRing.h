#pragma once
#include "EngineHeader.h"
#include "Cash.h"

class FireRing : public EnvironmentObject
{
public:
	FireRing();
	~FireRing();
	void Init(int width, int height, int multiple);
	void Release();
	void Draw(HDC hdc);
	string CollisionCheck(RECT rect);
	bool Update(float eTime);
	void Move(int offset);
	void Set();
	int getX() { return pos.x; }
protected:
	bool isMove;
	bool leftDraw;
	bool isLoad;
	bool isScoreColl;
	bool isCash;
	int map_Size;
	float m_Multiple;
	float setTime;
	float curTime;
	Cash cash;
	Animation* leftRing;
	Animation* rightRing;
	SIZE size;
	RECT scoreBox;
	RECT box;
	POINT pos;
};

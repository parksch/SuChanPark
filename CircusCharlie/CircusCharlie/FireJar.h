#pragma once
#include "EngineHeader.h"
#include "Cash.h"

class FireJar : public EnvironmentObject
{
public:
	FireJar();
	~FireJar();
	void Init(int width, int height,int multiple);
	bool Update(float eTime);
	void Release();
	void Draw(HDC hdc);
	void Move(int offset);
	string CollisionCheck(RECT rect);
private:
	Cash cash;
	int map_Size;
	int m_Multiple;
	bool isLoad;
	float curTime;
	Animation* fireJar;
	SIZE size;
	RECT box;
	POINT pos;
};


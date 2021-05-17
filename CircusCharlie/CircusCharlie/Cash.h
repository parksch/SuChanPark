#pragma once
#include "EngineHeader.h"

class Cash : EnvironmentObject
{
public:
	Cash();
	~Cash();
	void Init(int width, int height,int multiple);
	bool Update(float eTime);
	void Release();
	void Draw(HDC hdc);
	void Move(int offset);
	void Set(int width);
	string CollisionCheck(RECT rect);
private:
	bool isActive;
	bool isLoad;
	int m_Multiple;
	int map_Size;
	float curTime;
	Animation* cash;
	SIZE size;
	RECT box;
	POINT pos;
};


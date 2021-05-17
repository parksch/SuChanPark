#pragma once
#include "EngineHeader.h"

class GameMap : public Map
{
public:
	GameMap();
	~GameMap();
	void Init(HWND hWnd, int width, int height);
	void Update(float curTime);
	void Release();
	bool MovingMap(int offset);
	void Draw(HDC hdc);
	void MapEvent();
private:
	void Draw(HDC hdc, int x, int y);
private:
	float time;
	bool isLoad;
	int focus;
	POINT m_MapSize;
	Animation* back;
	Animation* back_deco;
	Animation* back_normal;
	Animation* miter;
};
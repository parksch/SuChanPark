#pragma once
#include "ResourceManager.h"

class Map
{
public:
	Map() {};
	virtual ~Map() {};
	virtual void Init(HWND hWnd, int width, int height) = 0;
	virtual void Update(float curTime) = 0;
	virtual bool MovingMap(int offset) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Release() = 0;
	virtual void MapEvent() = 0;
protected:
	virtual void Draw(HDC hdc, int x, int y) = 0;
	BitMap* game_Map;
};
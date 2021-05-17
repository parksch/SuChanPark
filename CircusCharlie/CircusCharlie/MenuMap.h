#pragma once
#include "EngineHeader.h"

class MenuMap : public Map
{
public:
	MenuMap();
	~MenuMap();
	void Init(HWND hWnd, int width, int height);
	void Update(float curTime);
	void Release();
	bool MovingMap(int keyCode) { return false; }
	void Draw(HDC hdc);
	void MapEvent() {};
	SIZE GetSize() { return SIZE(); };
private:
	void Draw(HDC hdc, int x, int y);
private:
	bool isLoad;
	POINT mapSize;
	Animation* blackBack;
	Animation* menuName;
	Animation* menuBar;
	Animation* stars;
};

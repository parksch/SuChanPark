#pragma once
#include "EngineHeader.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	void Init(HWND hWnd, int width, int height);
	void Update(float ETime);
	bool Input(float ETime);
	void Draw(HDC hdc);
	void Release();
	bool Moving(int keyCode) { return false; }
private:
	bool isLoad;
	float curTime;
	int m_Width, m_Height;
	Map* map;
};


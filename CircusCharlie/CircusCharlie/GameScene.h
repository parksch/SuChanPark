#pragma once
#include "EngineHeader.h"
#include "Charlie.h"
#include "FireJar.h"
#include "FireRing.h"
#include "End.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void Init(HWND hWnd, int width, int height);
	void Update(float ETime);
	bool Moving(int keyCode);
	void EndScene();
	bool Input(float ETime);
	void Draw(HDC hdc);
	void Release();
private:
	void Retry();
	bool isLoad;
	bool isOver;
	float endTime;
	float spawnTime;
	float curTime;
	int camFocus;
	int ringsize;
	int m_Width, m_Height;
	End end;
	FireRing rings[4];
	FireJar fireJar[9];
	Charlie charlie;
	Map* map;
};


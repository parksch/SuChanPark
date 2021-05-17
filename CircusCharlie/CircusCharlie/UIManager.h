#pragma once
#include "Singleton.h"
#include "ResourceManager.h"
#include <string>
using namespace std;

class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();
	void Init(HWND hWnd,int width,int height);
	void Update(float eTime);
	void UpScore(int result);
	void Set();
	void Ready();
	void End();
	void DownLife();
	int getLife() { return lifeScore; }
	bool isUIEventDone() { return !(bonus > 0); }
	void Draw(HDC hdc);
private:
	float curTime;
	bool isLoad;
	bool isEnd;
	bool isAcetive;
	POINT map_Size;
	int bonus;
	int score;
	int lifeScore;
	Animation *life;
};



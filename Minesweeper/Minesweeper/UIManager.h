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
	void Init(HWND hWnd,int width,int height,int difficulty = 1);
	void Update(float eTime);
	void Draw(HDC hdc);
	void Change(int offset);
	void Reset(int difficulty);
	void Pause() { pause = true; }
	int getTime() { return time; }
private:
	bool pause;
	POINT timePos;
	POINT minePos;
	float curtime;
	int time;
	int mine;
};



#pragma once
#include <Windows.h>
#include "Singleton.h"
#include <string>
using namespace std;

class GameManager :public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	void CollisionCheck(HWND hWnd,int x,int y);
private:
};


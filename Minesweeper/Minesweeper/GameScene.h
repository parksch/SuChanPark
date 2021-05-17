#pragma once
#include <vector>
#include <Windows.h>
#include "Block.h"
using namespace std;

int Random(int min, int max);

class GameScene 
{
public:
	GameScene();
	 ~GameScene();
	void Init(HWND hWnd,int difficulty = 1);
	bool Input(float fETime);
	void Draw(HDC hdc);
	void Release();
private:
	void ReStart();
	void ClickEvent(int x,int y);
	void Shuffle();
	void Numbering();
	bool WinChecker();
	bool isGamePause;
	int max_Mine;
	int m_Difficulty;
	HWND m_hWnd;
	BitMap *map;
	POINT max_Block;
	POINT offset;
	vector<vector<Block> > m_Blocks;
	SIZE map_Size;
	
};


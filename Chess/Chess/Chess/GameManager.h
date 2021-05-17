#pragma once
#include <Windows.h>
#include "ResourceManager.h"
#include "Player.h"
#define BLACK 11
#define WHITE 22

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	void Reset();
	void init(HWND hWnd);
	void Display(HWND hWnd);
	void Recv(std::string str);
	void LButtonDown(HWND hWnd, int x, int y);
	void Check(HWND hWnd);
	void GameOver(std::string str,HWND hWnd);
private:
	int code;
	bool isGameOn;
	bool turn;
	HWND m_hWnd;
	Player *curP;
	Player p1, p2;
	POINT board;
};


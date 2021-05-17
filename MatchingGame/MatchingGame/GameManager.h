#pragma once
#include <Windows.h>
#include <vector>
#include "Deck.h"
#include "Singleton.h"
#define MAXCARD 20
#define SELECT_FAIL_DELAY 1000
#define CARDSIZE 1
enum STATE
{
	STATE_HIDE,
	STATE_SELECT,
	STATE_OPEN_FAIL,
	STATE_OPEN_SUCCESS
};

struct Card
{
	STATE state;
	int index;
	POINT pos;
};

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	void Init(HWND hWnd,HINSTANCE hInstance);
	void Draw(HWND hWnd);
	void Update(HWND hWnd);
	void Click(HWND hWnd,int mouseX,int mouseY);
	void Set();
private:
	int score;
	int curIndex;
	bool isClickFail;
	vector<Card> cards;
};


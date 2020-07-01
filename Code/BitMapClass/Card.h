#pragma once
#include "resource.h"
#include "BitMap.h"

#define CARDMAX 10

class Card
{
private:
	BitMap dog;
	BitMap tiger;
	BitMap duck;
	BitMap elephant;
	BitMap cow;
	BitMap horse;
	BitMap cat;
	BitMap monkey;
	BitMap frog;
	BitMap chicken;

public:
	Card();
	
	void Init(HWND hWnd, HINSTANCE hInst);
	void drawAll(HDC hdc);
	void clickMessage(HWND hWnd, int mouseX, int mouseY);

	~Card();
};


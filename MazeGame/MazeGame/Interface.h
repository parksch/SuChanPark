#pragma once
#include "Macro.h"
#define UP 'w'
#define DOWN 's'
#define ENTER 13

class Interface
{
public:
	Interface();
	~Interface();
	void DrawMidText(string str, int x, int y);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	void DrawPoint(string str, int x, int y);
	void ErasePoint(int x, int y);
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};


#pragma once
#include "Macro.h"
#define UP 'w'
#define DOWN 's'
#define ENTER 13

class Draw
{
public:
	int Game_Menu(int width,int height);
	int Game_Select_Difficulty(int width, int height);
	int Game_Select_Size(int width, int height);
	void Game_UI(int width,int height,int mine,int flag);
	void Game_Win(int width,int height);
	void GameOver(int width, int height);
	void DrawGameField(int width, int height);
	void DrawPoint(string str, int x, int y);
private:
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void BoxErase(int Width, int Heightint, int Start_X = 2, int Start_Y = 1);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void TextErase(int size, int Start_X, int Start_Y);
	void ErasePoint(int x, int y);
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

};


#include "Draw.h"

int Draw::Game_Menu()
{
	DrawMidText("1.Start", WIDTH, HEIGHT * 0.5f - 2);
	DrawMidText("2.Exit", WIDTH, HEIGHT * 0.5f );
	return MenuSelectCursor(2, 2, WIDTH * 0.5f - (strlen("1.Start")/2) - 1, HEIGHT * 0.5f -2);
}

int Draw::Game_Select_Difficulty()
{
	DrawMidText("1.Easy", WIDTH, HEIGHT * 0.5f - 4);
	DrawMidText("2.Nomal", WIDTH, HEIGHT * 0.5f - 2);
	DrawMidText("3.Hard", WIDTH, HEIGHT * 0.5f );
	DrawMidText("4.Exit", WIDTH, HEIGHT * 0.5f + 2);
	return MenuSelectCursor(4, 2, WIDTH * 0.5f - (strlen("1.Start") / 2) - 1, HEIGHT * 0.5f - 4);
}

void Draw::DrawGameField()
{
	for (int y = 0; y < HEIGHT -1; y++)
	{
		for (int x = 0; x < WIDTH -1; x++)
		{
			DrawPoint("¡á",x,y);
		}
	}
}

void Draw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;

	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "¦£";
			for (int x = 1; x < Width - 1; x++)
				cout << "¦¡";
			cout << "¦¤";
		}
		else if (y == Height - 1)
		{
			cout << "¦¦";
			for (int x = 1; x < Width - 1; x++)
				cout << "¦¡";
			cout << "¦¥";
		}
		else
		{
			cout << "¦¢";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "¦¢";
		}
	}
	return;
}

int Draw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		DrawPoint("¢¹", x, y);
	ORIGINAL

		while (1)
		{
			switch (getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:

				return Select;
			}

			RED
				DrawPoint("¢¹", x, y);
			ORIGINAL
		}
}

void Draw::BoxErase(int Width, int Height, int Start_X, int Start_Y)
{
	for (int y = Start_Y; y < Start_Y + Height - 2; y++)
	{
		gotoxy(Start_X, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}


void Draw::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	//gotoxy(-1, -1);
	return;
}

void Draw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void Draw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void Draw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void Draw::TextErase(int size, int Start_X, int Start_Y)
{
	for (int i = 0; i < size; i++)
	{
		gotoxy(Start_X + i - size / 2, Start_Y);
		cout << "  ";
	}
}
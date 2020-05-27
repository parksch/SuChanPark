#include "Draw.h"

Draw::Draw()
{
}

Draw::~Draw()
{
}

void Draw::ObjectDraw(string str,int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
}

void Draw::BoxDraw(int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width * 2; x += 2)
		{
			gotoxy(x, y);
			if (y == 0)
			{
				cout << "¢Æ";
			}
			else if (y != height - 1 && x == 0 || x == width * 2 - 2)
			{
				cout << "¢Æ";
			}
			else if (y == height - 1)
			{
				cout << "¢Æ";
			}
		}
	}
}

void Draw::StrDraw(string text,int x, int y)
{
	gotoxy(x - (text.size()/2), y);
	cout << text;
}

void Draw::Erase(int x, int y)
{
	gotoxy( x * 2, y);
	cout << "  ";
}

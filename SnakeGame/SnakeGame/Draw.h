#include "Macro.h"

class Draw
{
public:
	Draw();
	~Draw();
	void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	void ObjectDraw(string str,int x,int y);
	void BoxDraw(int width, int height);
	void StrDraw(string text, int x, int y);
	void Erase(int x, int y);
private:

};


#include "Door.h"



Door::Door(int code, int x, int y)
{
	m_Code = code;
	X = x;
	Y = y;
	m_Icon = "��";
	m_MapDraw.DrawPoint(m_Icon, x, y);
}

Door::~Door()
{
}

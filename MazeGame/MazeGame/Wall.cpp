#include "Wall.h"

Wall::Wall(int code, int x, int y)
{
	m_Code = code;
	X = x;
	Y = y;
	m_Icon = "бс";
	m_MapDraw.DrawPoint(m_Icon, x, y);
}

Wall::~Wall()
{
}



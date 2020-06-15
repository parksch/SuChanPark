#include "Trap.h"

Trap::Trap(int code, int x, int y)
{
	m_Code = code;
	X = x;
	Y = y;
	m_Icon = "¡Ø";
	m_OldTime = clock();
	m_OffsetX = 1;
}

Trap::~Trap()
{
}

void Trap::Collision_Handle(Object *object, PLAYER_STATE &state)
{
}

void Trap::Update(Object**objects, int size, PLAYER_STATE &state)
{
	if (clock() - m_OldTime >= DELAY)
	{
		if (m_OffsetX < 0)
		{
			if (X + m_OffsetX== 0)
			{
				m_OffsetX = 1;
			}
		}
		else
		{
			if (X + m_OffsetX == DEFAULT_WIDTH -1)
			{
				m_OffsetX = -1;
			}
		}

		m_MapDraw.ErasePoint(X, Y);
		X = X + m_OffsetX;
		m_MapDraw.DrawPoint(m_Icon, X, Y);
		
		for (int i = 0; i < size; i++)
		{
			if (X  == (*objects[i]).getX() && Y  == (*objects[i]).getY() && (*objects[i]).getCode() == 2)
			{
				(*objects[i]).Collision_Handle(this, state);
				return;
			}
		}

		m_OldTime = clock();
	}
}

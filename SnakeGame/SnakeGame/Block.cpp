#include "Block.h"

Block::Block()
{
	m_Display[TYPE_WALL] = "¢Ã";
	m_Display[TYPE_FOOD] = "¢½";
	m_Display[TYPE_SNAKE_HEAD] = "¢Á";
	m_Display[TYPE_SNAKE_BODY] = "¡Û";
	m_Display[TYPE_BROKEN] = "¡Ø";
	m_Type = TYPE_NON;
	isLive = false;
}

Block::~Block()
{
}

void Block::Create(TYPE type, Pos pos)
{
	isLive = true;
	m_Type = type;
	m_Pos = pos;
	m_Draw.ObjectDraw(m_Display[type], m_Pos.m_X,m_Pos.m_Y);
}

void Block::Reset()
{
	isLive = false;
	m_Type = TYPE_NON;
	m_Pos = Pos(0, 0);
}

void Block::Move(Pos pos)
{
	m_Draw.Erase(m_Pos.m_X, m_Pos.m_Y);
	m_Pos = pos;
	m_Draw.ObjectDraw(m_Display[m_Type], m_Pos.m_X, m_Pos.m_Y);
}

void Block::Lose()
{
	m_Draw.ObjectDraw(m_Display[TYPE_BROKEN], m_Pos.m_X, m_Pos.m_Y);
}

void Block::Collision()
{
	isLive = false;
}

bool Block::Check(Pos pos)
{
	if (!isLive)
	{
		return false;
	}

	if (m_Pos.m_X == pos.m_X && m_Pos.m_Y == pos.m_Y)
	{
		return true;
	}

	return false;
}

#include "Monster.h"

Boss::Boss(int code,int x,int y)
{
	m_Code = code;
	X = x;
	Y = y;
	m_Icon = "¢Ã";
	m_CurState = STATE_SLEEP;
	offset = 1;
}

Boss::~Boss()
{
}

void Boss::Collision_Handle(int Code)
{
	if (Code == PLAYER)
	{
		GameManager::GetInstacne()->Game_Fail();
	}
}

void Boss::Update()
{
	switch (m_CurState)
	{
	case STATE_SLEEP:
		if (GameManager::GetInstacne()->CollisionCheck(Point(7, 3), BOSS) == PLAYER)
		{
			m_MapDraw.DrawPoint(m_Icon, X, Y);
			SpawnBoss();
			m_CurState = STATE_PARTROL;
			time = clock();
		}
		break;
	case STATE_PARTROL:
		if (clock() - time >= MOVEDELAY)
		{
			int code;

			if (GameManager::GetInstacne()->ObjectLength(Point(X,Y),PLAYER) < 4)
			{
				m_CurState = STATE_TRACKING;
				return;
			}

			if (X + offset == 0 || Y == 0 || X + offset == DEFAULT_WIDTH - 1 || Y  == DEFAULT_HEIGHT - 1)
			{
				offset *= -1;
			}

			code = GameManager::GetInstacne()->CollisionCheck(Point(X + offset, Y ), m_Code);

			if (code == WALL)
			{
				offset *= -1;
			}
			else if (code != 0)
			{
				Collision_Handle(code);
			}

			m_MapDraw.ErasePoint(X, Y);
			X = X + offset;
			m_MapDraw.DrawPoint(m_Icon, X, Y);
			time = clock();
		}
		break;
	case STATE_TRACKING:
		if (clock() - time >= MOVEDELAY)
		{
		int offsetx = 0, offsety = 0;
		Point pos = GameManager::GetInstacne()->ObjectPos(PLAYER);
		int code;

		if (X > pos.X)
		{
			offsetx = -1;
		}
		else if(X < pos.X)
		{
			offsetx = 1;
		}

		if (Y > pos.Y)
		{
			offsety = -1;
		}
		else if(Y < pos.Y)
		{
			offsety = 1;
		}

		if (X + offsetx == 0 || Y + offsety == 0 || X + offsetx == DEFAULT_WIDTH - 1 || Y + offsety == DEFAULT_HEIGHT - 1)
		{
			return;
		}

		code = GameManager::GetInstacne()->CollisionCheck(Point(X + offsetx, Y + offsety), m_Code);

		if (code == WALL)
		{
			return;
		}
		else if (code != 0)
		{
			Collision_Handle(code);
		}

		m_MapDraw.ErasePoint(X, Y);
		X = X + offsetx;
		Y = Y + offsety;
		m_MapDraw.DrawPoint(m_Icon, X, Y);
		time = clock();
		}
		break;
	}
}

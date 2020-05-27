#include "Snake.h"

Snake::Snake() 
{

}

Snake::~Snake()
{
}

void Snake::Set(int width, int height)
{
	m_CurrentKey = KEY_NON;
	m_StagePos.m_X = width;
	m_StagePos.m_Y = height;
	m_CurrentPos.m_X = m_StagePos.m_X / 2;
	m_CurrentPos.m_Y = m_StagePos.m_Y / 2;
	m_Body = NULL;
	m_Move_UpdateTime = UPDATETIME_MOVE;
}

void Snake::Reset()
{
	m_CurrentKey = KEY_NON;
	m_CurrentPos.m_X = m_StagePos.m_X / 2;
	m_CurrentPos.m_Y = m_StagePos.m_Y / 2;
	Delete();
	m_Body = NULL;
	m_Move_UpdateTime = UPDATETIME_MOVE;
}

void Snake::Input()
{
	if (clock() - m_input_OldTime < UPDATETIME_INPUT)
	{
		return;
	}

	if (kbhit())
	{
		m_input_OldTime = clock();
		char get = getch();

		switch ((KEY)get)
		{
		case KEY_W:
			if (m_CurrentKey != KEY_S)
			{
				m_CurrentKey = (KEY)get;
			}
			break;
		case KEY_A:
			if (m_CurrentKey != KEY_D)
			{
				m_CurrentKey = (KEY)get;
			}
			break;
		case KEY_S:
			if (m_CurrentKey != KEY_W)
			{
				m_CurrentKey = (KEY)get;
			}
			break;
		case KEY_D:
			if (m_CurrentKey != KEY_A)
			{
				m_CurrentKey = (KEY)get;
			}
			break;
		default:
			break;
		}
	}
}

STATE Snake::Move()
{
	if (clock() - m_Move_OldTime < m_Move_UpdateTime)
	{
		return STATE_WAIT;
	}

	Pos tmp = m_CurrentPos;

	switch (m_CurrentKey)
	{
	case KEY_W:
		m_CurrentPos.m_Y--;
		break;
	case KEY_A:
		m_CurrentPos.m_X--;
		break;
	case KEY_S:
		m_CurrentPos.m_Y++;
		break;
	case KEY_D:
		m_CurrentPos.m_X++;
		break;
	default:
		break;
	}

	m_Head.Move(m_CurrentPos);

	if (m_Body != NULL)
	{
		m_LastPos = m_Body->Move(tmp);
	}
	else
	{
		m_LastPos = tmp;
	}

	if (m_CurrentPos.m_X < 1 || m_CurrentPos.m_X > m_StagePos.m_X - 2 || m_CurrentPos.m_Y < 1 || m_CurrentPos.m_Y > m_StagePos.m_Y - 2)
	{
		BrokenHead();
		return STATE_COLLISION;
	}

	if (BodyCollisionCheck())
	{
		BrokenHead();
		return STATE_COLLISION;
	}

	else
	{
		m_Move_OldTime = clock();
		return STATE_NON;
	}
}

void Snake::BodyCreate()
{
	m_Move_UpdateTime -= 50;

	if (m_Move_UpdateTime < 100)
	{
		m_Move_UpdateTime = 100;
	}

	if (m_Body == NULL)
	{
		m_Body = new Body(m_LastPos);
	}
	else
	{
		m_Body->Create(m_LastPos);
	}
}

bool Snake::BodyCollisionCheck()
{
	if (m_Body == NULL)
	{
		return false;
	}

	return m_Body->Check(m_CurrentPos);
}

void Snake::BrokenHead()
{
	m_Head.Lose();
}

void Snake::Create()
{
	m_Head.Create(TYPE_SNAKE_HEAD, m_CurrentPos);
	m_Move_OldTime = clock();
}

void Snake::Delete()
{
	if (m_Body != NULL)
	{
		m_Body->DeleteNode();
		delete m_Body;
	}
}


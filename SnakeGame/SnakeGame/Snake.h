#pragma once
#include "Macro.h"
#include "Block.h"

#define UPDATETIME_MOVE 500
#define UPDATETIME_INPUT 100

enum KEY
{
	KEY_NON = 0,
	KEY_W = 'w',
	KEY_A = 'a',
	KEY_S = 's',
	KEY_D = 'd'
};

struct Body 
{
	Body(Pos pos)
	{
		m_block.Create(TYPE_SNAKE_BODY, pos);
		m_Next = NULL;
	};

	~Body()
	{
	}

	void DeleteNode()
	{
		Body *tmp;

		while (m_Next != NULL)
		{
			tmp = m_Next->m_Next;
			delete m_Next;
			m_Next = tmp;
		}
	}

	void Create(Pos pos)
	{
		if (m_Next != NULL)
		{
			m_Next->Create(pos);
		}
		else
		{
			m_Next = new Body(pos);
		}
	}

	Pos Move(Pos pos)
	{
		Pos tmp = m_block.getPos();
		m_block.Move(pos);

		if (m_Next != NULL)
		{
			return	m_Next->Move(tmp);
		}
		else
		{
			return tmp;
		}
	}

	bool Check(Pos pos)
	{
		if (m_block.Check(pos))
		{
			return true;
		}
		else if (m_Next != NULL)
		{
			return m_Next->Check(pos);
		}
		else
		{
			return false;
		}
	}

	Block m_block;
	Body *m_Next;
};

class Snake
{
public:
	Snake();
	~Snake();
	void Set(int width, int height);
	void Reset();
	void Input();
	STATE Move();
	void BodyCreate();
	bool BodyCollisionCheck();
	void BrokenHead();
	void Create();
	void Delete();
	inline Pos getPos() { return m_CurrentPos; }
private:
	KEY m_CurrentKey;
	Pos m_StagePos;
	Pos m_CurrentPos;
	Pos m_LastPos;
	Block m_Head;
	Body *m_Body;
	int m_input_OldTime;
	int m_Move_OldTime;
	int m_Move_UpdateTime;
};

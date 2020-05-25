#include "FieldManager.h"

FieldManager::FieldManager()
{
}

FieldManager::~FieldManager()
{
}

void FieldManager::CreateMine(int size,int width, int height)
{
	int randX;
	int randY;

	m_Objects.reserve(height);
	for (int i = 0; i < height; i++)
	{
		vector<Field> temp(width,Field());
		m_Objects.push_back(temp);
	}

	for (int i = 0; i < size; i++)
	{
		while (1)
		{
			randY = rand() % (height);
			randX = rand() % (width);

			if (m_Objects[randY][randX].State == EMPTY)
			{
				m_Objects[randY][randX].State = MINE;
				break;
			}
		}
	}
}

void FieldManager::DrawPoint(int x, int y)
{
	if (m_Objects[y][x].isFlag)
	{
		m_Draw.DrawPoint("в╠", x, y);
	}
	else if (m_Objects[y][x].isHide)
	{
		m_Draw.DrawPoint("бс",x,y);
	}
	else
	{
		switch (m_Objects[y][x].State)
		{
		case EMPTY:
			m_Draw.DrawPoint("бр", x, y);
			break;
		default:
			break;
		}
	}
}

int FieldManager::SetFlag(int x, int y)
{
	if (m_Objects[y][x].isHide)
	{
		m_Objects[y][x].isFlag = !m_Objects[y][x].isFlag;

		if (m_Objects[y][x].isFlag)
		{
			m_Draw.DrawPoint("в╠", x, y);
			return 1;
		}
		else
		{
			m_Draw.DrawPoint("бс", x, y);
			return -1;
		}
	}

	return 0;
}

bool FieldManager::Check(int x, int y)
{
	if (m_Objects[y][x].isFlag)
	{
		return false;
	}
	else if (m_Objects[y][x].isHide)
	{
		m_Objects[y][x].isHide = false;

		switch (m_Objects[y][x].State)
		{
		case EMPTY:
			m_Draw.DrawPoint("бр", x, y);
			return false;
		case MINE:
			for (int y = 0; y < m_Objects.size(); y++)
			{
				for (int x = 0; x < m_Objects[y].size(); x++)
				{
					if (m_Objects[y][x].State == MINE)
					{
						PUPPLE
						m_Draw.DrawPoint("б╪", x, y);
						ORIGINAL
					}
				}
			}

			RED
			m_Draw.DrawPoint("б╪", x, y);
			ORIGINAL
			return true;
		default:
			break;
		}
	}
	else
	{
		return false;
	}
}

void FieldManager::Reset()
{
	vector<vector<Field>>().swap(m_Objects);
}

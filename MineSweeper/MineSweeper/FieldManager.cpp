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
	m_Width = width;
	m_Height = height;

	m_Objects.reserve(m_Height);
	for (int i = 0; i < m_Height; i++)
	{
		vector<Field> temp(m_Width,Field());
		m_Objects.push_back(temp);
	}

	for (int i = 0; i < size; i++)
	{
		while (1)
		{
			randY = rand() % (m_Height);
			randX = rand() % (m_Width);

			if (m_Objects[randY][randX].Value == 0)
			{
				m_Objects[randY][randX].Value = 9;
				break;
			}
		}
	}
}

void FieldManager::FocusPoint(int x, int y)
{
	if (m_Objects[y][x].isFlag)
	{
		m_Draw.DrawPoint("��", x, y);
	}
	else if (m_Objects[y][x].isHide)
	{
		m_Draw.DrawPoint("��", x, y);
	}
	else
	{
		switch (m_Objects[y][x].Value)
		{
		case 0:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 1:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 2:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 3:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 4:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 5:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 6:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 7:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 8:
			m_Draw.DrawPoint("��", x, y);
			break;
		default:
			break;
		}
	}

}

void FieldManager::DrawPoint(int x, int y)
{
	if (m_Objects[y][x].isFlag)
	{
		m_Draw.DrawPoint("��", x, y);
	}
	else if (m_Objects[y][x].isHide)
	{
		m_Draw.DrawPoint("��", x, y);
	}
	else
	{
		switch (m_Objects[y][x].Value)
		{
		case 0:
			m_Draw.DrawPoint("��", x, y);
			break;
		case 1:
			RED
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
				break;
		case 2:
			BLOOD
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
				break;
		case 3:
			YELLOW
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
				break;
		case 4:
			GOLD
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
				break;
		case 5:
			GREEN
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
				break;
		case 6:
			BLUE_GREEN
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
				break;
		case 7:
			BLUE
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
				break;
		case 8:
			DARK_BLUE
				m_Draw.DrawPoint("��", x, y);
			ORIGINAL
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
			m_Draw.DrawPoint("��", x, y);
			return 1;
		}
		else
		{
			m_Draw.DrawPoint("��", x, y);
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
	else if (m_Objects[y][x].Value == 9)
	{
		for (int y = 0; y < m_Objects.size(); y++)
		{
			for (int x = 0; x < m_Objects[y].size(); x++)
			{
				if (m_Objects[y][x].Value == 9)
				{
					PUPPLE
						m_Draw.DrawPoint("��", x, y);
					ORIGINAL
				}
			}
		}

		RED
		m_Draw.DrawPoint("��", x, y);
		ORIGINAL
		return true;
	}
	else
	{
		if (m_Objects[y][x].isHide)
		{
			OctagonCheck(x, y);
		}
		return false;
	}
}

bool FieldManager::FlagCheck(int mine)
{
	int count = 0;

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			if (m_Objects[y][x].Value == 9 && m_Objects[y][x].isFlag)
			{
				count++;
			}
		}
	}

	if (count == mine)
	{
		return true;
	}

	return false;
}

void FieldManager::OctagonCheck(int x, int y)
{
	int count = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (x + j >= 0 && x + j < m_Width && y + i >= 0 && y + i < m_Height)
			{
				if (m_Objects[y + i][x + j].Value == 9)
				{
					count++;
				}
			}
		}
	}

	if (count != 0)
	{
		m_Objects[y][x].Value = count;
		m_Objects[y][x].isHide = false;
		DrawPoint(x, y);
		return;
	}

	m_Objects[y][x].isHide = false;
	DrawPoint(x, y);

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i ==0 && j ==0 )
			{
				continue;
			}
			else if (x + j >= 0 && x + j < m_Width && y + i >= 0 && y + i < m_Height)
			{
				if (m_Objects[y + i][x + j].isHide)
				{
					OctagonCheck(x + j, y + i);
				}
			}
		}
	}
}

void FieldManager::Reset()
{
	vector<vector<Field>>().swap(m_Objects);
}

#include "GameManager.h"

GameManager::GameManager()
{
	m_Width = WIDTH;
	m_Height = HEIGHT;
	Map_DisPlay(m_Width, m_Height);
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	Game_Menu();
}

void GameManager::Map_SizeChange()
{
	int input;
	system("cls");
	input = m_Draw.Game_Select_Size(m_Width,m_Height);

	switch (input)
	{
	case 1:
		m_Width = WIDTH;
		m_Height = HEIGHT;
		break;
	case 2:
		m_Width = WIDTH * 1.5f;
		m_Height = HEIGHT * 1.5f;
		break;
	case 3:
		m_Width = WIDTH * 2;
		m_Height = HEIGHT * 2;
		break;
	case 4:
		return;
	default:
		break;
	}

	Map_DisPlay(m_Width, m_Height);
}

void GameManager::Map_DisPlay(int width, int height)
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", width + 5, (height * 2) + 1);
	system(buf);
}

void GameManager::Game_Menu()
{
	int input;
	while (1)
	{
		system("cls");
		input = m_Draw.Game_Menu(m_Width,m_Height);

		switch (input)
		{
		case 1:
			Game_Enter();
			break;
		case 2:
			Map_SizeChange();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

void GameManager::Game_Enter()
{
	int input;
	m_Pos.X = m_Width * 0.5f;
	m_Pos.Y = m_Height * 0.5f;
	m_FlagSize = 0;
	system("cls");
	input = m_Draw.Game_Select_Difficulty(m_Width, m_Height);

	switch ((DIFFICULTY)input)
	{
	case EASY:
		m_MineSize = (m_Width * m_Height)* 0.3f;
		break;
	case NOMAL:
		m_MineSize = (m_Width * m_Height)* 0.5f;
		break;
	case HARD:
		m_MineSize = (m_Width * m_Height)* 0.7f;
		break;
	default:
		return;
	}

	m_FieldManager.CreateMine(m_MineSize,m_Width,m_Height);
	Game_Excute();
}

void GameManager::Game_Excute()
{

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			m_Draw.DrawPoint("бс", y, x);
		}
	}

	YELLOW
	m_FieldManager.DrawPoint(m_Pos.X, m_Pos.Y);
	ORIGINAL
	m_Draw.Game_UI(m_Width, m_Height, m_MineSize, m_FlagSize);
	
	while (1)
	{
		if (Input())
		{
			if (m_FieldManager.Check(m_Pos.X, m_Pos.Y))
			{
				m_Draw.GameOver(m_Width, m_Height);
				Game_Exit();
				return;
			}
		}
	}
}

void GameManager::Game_Exit()
{
	m_FieldManager.Reset();
}

bool GameManager::Input()
{
	if (kbhit())
	{
		char get = getch();

		if (get == 'w')
		{
			Move(0, -1);
		}

		if (get == 's')
		{
			Move(0, 1);
		}

		if (get == 'a')
		{
			Move(-1, 0);
		}

		if (get == 'd')
		{
			Move(1, 0);
		}

		if (get == 'x')
		{
			m_FlagSize += m_FieldManager.SetFlag(m_Pos.X, m_Pos.Y);
			m_Draw.Game_UI(m_Width, m_Height, m_MineSize, m_FlagSize);
		}

		if (get == 13)
		{
			return true;
		}
	}

	return false;
}

void GameManager::Move(int offSetX, int offSetY)
{
	if (m_Pos.X + offSetX >= 0 && m_Pos.X + offSetX < m_Width && m_Pos.Y + offSetY >= 0 && m_Pos.Y + offSetY < m_Height)
	{
		m_FieldManager.DrawPoint(m_Pos.X, m_Pos.Y);
		m_Pos.X += offSetX;
		m_Pos.Y += offSetY;
		YELLOW
		m_FieldManager.DrawPoint(m_Pos.X, m_Pos.Y);
		ORIGINAL
	}
}

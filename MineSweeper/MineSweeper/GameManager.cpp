#include "GameManager.h"

GameManager::GameManager()
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", HEIGHT + 1, WIDTH * 2);
	system(buf);
	srand((unsigned)time(NULL));
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	Game_Menu();
}

void GameManager::Game_Menu()
{
	int input;
	while (1)
	{
		system("cls");
		input = m_Draw.Game_Menu();
		switch (input)
		{
		case 1:
			Game_Enter();
			break;
		case 2:
			return;
		default:
			break;
		}
	}
}

void GameManager::Game_Enter()
{
	int input;
	system("cls");
	input = m_Draw.Game_Select_Difficulty();

	switch ((DIFFICULTY)input)
	{
	case EASY:
		m_MineManager.CreateMine((WIDTH * HEIGHT) * 0.3f);
		break;
	case NOMAL:
		m_MineManager.CreateMine((WIDTH * HEIGHT) * 0.5f);
		break;
	case HARD:
		m_MineManager.CreateMine((WIDTH * HEIGHT) * 0.7f);
		break;
	default:
		return;
	}
}

#include "Game.h"

Game::Game()
{
	char ch[255];
	srand((unsigned int)time(NULL));
	sprintf(ch, "mode con cols=%d lines=%d", WIDTH * 2 + 1, HEIGHT + 5);
	system(ch);
	m_Score = 0;
	m_Snake.Set(WIDTH, HEIGHT);
	Menu();
}

Game::~Game()
{
	m_Snake.Delete();
}

void Game::ObjectCheck(Block ObjectArray[], int Size, void(Game::* Event)(int), Game * temp)
{
	int Index = temp->Check(ObjectArray, temp->GetSnake().getPos(), Size);
	if (Index != -1)
		(temp->*Event)(Index);
}

void Game::Menu()
{
	int input;

	while (1)
	{
		system("cls");
		m_Draw.BoxDraw(WIDTH, HEIGHT);
		m_Draw.StrDraw("Score : " + to_string(m_Score), WIDTH, HEIGHT + 2);
		m_Draw.StrDraw("★ ☆ ★ Snake Game ★ ☆ ★", WIDTH, HEIGHT * 0.2f);
		m_Draw.StrDraw("1.게임 시작", WIDTH, HEIGHT * 0.3f);
		m_Draw.StrDraw("2.게임 종료", WIDTH, HEIGHT * 0.4f);
		m_Draw.StrDraw("선택 : ", WIDTH, HEIGHT * 0.5f);
		cin >> input;

		switch ((MENU)input)
		{
		case MENU_START:
			Play_Enter();
			break;
		case MENU_EXIT:
			return;
		default:
			return;
		}
	}

}

void Game::Play_Enter()
{
	system("cls");
	m_Draw.BoxDraw(WIDTH, HEIGHT);
	m_Snake.Create();
	m_Draw.StrDraw("Score : " + to_string(m_Score), WIDTH, HEIGHT + 2);
	CreateWalls();
	m_Play = true;
	Play_Excute();
}

void Game::Play_Excute()
{
	int tmp;
	m_OldTime = clock();

	while (m_Play)
	{
		m_Snake.Input();

		switch (m_Snake.Move())
		{
		case STATE_COLLISION:
			Play_Exit();
			m_Draw.gotoxy(0, HEIGHT);
			system("pause");
			return;
		case STATE_NON:
			ObjectCheck(m_WallBlocks, WALL_MAX, &Game::CollisionWall, this);
			ObjectCheck(m_FoodBlocks, FOOD_MAX, &Game::EatFood, this);
			break;
		default:
			break;
		}

		if (clock() - m_OldTime > UPDATETIME)
		{
			CreateFood();
			m_OldTime = clock();
		}
	}
}

void Game::Play_Exit()
{
	m_Snake.Reset();

	for (int i = 0; i < WALL_MAX; i++)
	{
		m_WallBlocks[i].Reset();
	}

	for (int i = 0; i < FOOD_MAX; i++)
	{
		m_FoodBlocks[i].Reset();
	}

	m_Score = 0;
}

void Game::CreateFood()
{
	for (int i = 0; i < FOOD_MAX; i++)
	{
		if (!m_FoodBlocks[i].isAlive())
		{
			m_FoodBlocks[i].Create(TYPE_FOOD, RandomPos());
			return;
		}
	}
}

void Game::CreateWalls()
{
	for (int i = 0; i < WALL_MAX; i++)
	{
		m_WallBlocks[i].Create(TYPE_WALL, RandomPos());
	}
}

void Game::EatFood(int index)
{
	m_Snake.BodyCreate();
	m_FoodBlocks[index].Collision();
	m_Score += 1;
	m_Draw.StrDraw("Score : " + to_string(m_Score), WIDTH, HEIGHT + 2);
}

void Game::CollisionWall(int index)
{
	m_Play = false;
	m_Snake.BrokenHead();
	system("pause");
	Play_Exit();
}

Pos Game::RandomPos()
{
	Pos rand_Pos;
	bool isEmpty;

	while (1)
	{
		isEmpty = true;
		rand_Pos.m_X = 1 + (rand() % (WIDTH - 2));
		rand_Pos.m_Y = 1 + (rand() % (HEIGHT - 2));

		if (rand_Pos.m_X == m_Snake.getPos().m_X && rand_Pos.m_Y == m_Snake.getPos().m_Y )
		{
			isEmpty = false;
		}

		for (int i = 0; i < WALL_MAX; i++)
		{
			if (m_WallBlocks[i].Check(rand_Pos))
			{
				isEmpty = false;
				break;
			}
		}

		for (int i = 0; i < FOOD_MAX; i++)
		{
			if (m_FoodBlocks[i].Check(rand_Pos))
			{
				isEmpty = false;
				break;
			}
		}

		if (isEmpty)
		{
			return rand_Pos;
		}
	}
}

int Game::Check(Block *block, Pos pos, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (block[i].Check(pos))
		{
			return i;
		}
	}

	return -1;
}




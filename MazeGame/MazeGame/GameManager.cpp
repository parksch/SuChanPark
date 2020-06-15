#include "GameManager.h"

GameManager* GameManager::m_Instance = NULL;

GameManager::GameManager() :MapSize(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", MapSize.Y + 1, MapSize.X * 2);
	system(buf);
	m_CurStage = 0;
}

GameManager::~GameManager()
{
	ObjectFactory::DestoryInstance();
	for (list<Object*>::iterator i = objects.begin(); i != objects.end(); i++)
	{
		delete *i;
	}
	objects.clear();
	m_MovingPoints.clear();
}

void GameManager::Start()
{
	Start_Menu();
}

int GameManager::CollisionCheck(Point pos, int code)
{
	for (list<Point>::iterator i = m_MovingPoints.begin(); i != m_MovingPoints.end() ; i++)
	{
		if ((*i)== pos)
		{
			return 1;
		}
	}

	for (list<Object*>::iterator i = objects.begin(); i != objects.end(); i++)
	{
		if ((*i)->Comp(pos) && (*i)->getCode()!= code)
		{
			return (*i)->getCode();
		}
	}

	return 0;
}

void GameManager::Start_Menu()
{

	while (1)
	{
		system("cls");
		m_Interface.DrawMidText("Start", MapSize.X, MapSize.Y * 0.5f - 1);
		m_Interface.DrawMidText("Exit", MapSize.X, MapSize.Y *0.5f + 1);

		switch (m_Interface.MenuSelectCursor(2, 2, MapSize.X * 0.5f - (strlen("start")/2) - 1, MapSize.Y * 0.5f - 1))
		{
		case 1:
			Stage_Load();
			break;
		case 2:
			return;
		default:
			break;
		}
	}
}


void GameManager::Stage_Load()
{
	while (m_CurStage < MAXSTAGE)
	{
		Game_Enter();
		Game_Excute();
		Game_Exit();
	}
}

void GameManager::Stage_Clear()
{
	isPlay = false;
}

void GameManager::Game_Enter()
{
	fstream file;
	string name = "Stage" + to_string(m_CurStage) + ".txt";
	int code;
	file.open(name);

	if (!file.is_open())
	{
		system("cls");
		m_Interface.DrawMidText("파일이 없습니다",MapSize.X,MapSize.Y * 0.5f);
		m_Interface.gotoxy(MapSize.X, MapSize.Y);
		system("pause");
		file.close();
		return;
	}
	
	Point temp;

	file >> temp.X;
	file >> temp.Y;

	if (MapSize != temp)
	{
		MapSize = temp;
		char buf[256];
		sprintf(buf, "mode con: lines=%d cols=%d", MapSize.Y + 1, MapSize.X * 2);
		system(buf);
	}

	system("cls");

	for (int y = 0; y < MapSize.Y; y++)
	{
		for (int x = 0; x < MapSize.X; x++)
		{
			file >> code;

			if (y > 0  && y < MapSize.Y - 1)
			{
				if (x > 0  && x < MapSize.X - 1)
				{

					if (code == WALL)
					{
						m_MovingPoints.push_back(Point(x, y));
						m_Interface.DrawPoint("■", x, y);
					}
					else if (code == 0)
					{
						m_Interface.DrawPoint("  ", x, y);
					}
					else
					{
						objects.push_back(ObjectFactory::GetInstacne()->Create(code,x,y));
					}
				}
				else
				{
					m_Interface.DrawPoint("■", x, y);
				}
			}
			else
			{
				m_Interface.DrawPoint("■", x, y);
			}
		}
	}
	
	file.close();
	getch();
}

void GameManager::Game_Excute()
{
	isPlay = true;

	while (isPlay)
	{
		for (list<Object*>::iterator i = objects.begin(); i != objects.end() ; i++)
		{
			(*i)->Update();
		}
	}
}

void GameManager::Game_Exit()
{
	m_MovingPoints.clear();

	for (list<Object*>::iterator i = objects.begin(); i != objects.end(); i++)
	{
		delete *i;
	}

	objects.clear();
	m_CurStage++;
}


void GameManager::Create(int code, int x, int y, int & count)
{

}


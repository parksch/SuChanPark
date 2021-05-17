#include "GameScene.h"
#include <iostream>
#include <random>
#include "ResourceManager.h"
#include "InputManager.h"
#include "UIManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(HWND hWnd, int difficulty)
{
	map = ResourceManager::GetInstance()->GetBitmap("back.bmp");
	m_hWnd = hWnd;
	for (int y = 0; y < max_Block.y; y++)
	{
		vector<Block>().swap(m_Blocks[y]);
	}

	vector<vector<Block> >().swap(m_Blocks);
	m_Difficulty = difficulty;
	isGamePause = false;

	if (difficulty == 1)
	{
		map_Size.cx = 260;
		map_Size.cy = 286;
		max_Block.x = 9;
		max_Block.y = 9;
		max_Mine = 1;
		offset.x = 12;
		offset.y = 24;

	}

	if (difficulty == 2)
	{
		map_Size.cx = 463;
		map_Size.cy = 505;
		max_Block.x = 16;
		max_Block.y = 16;
		max_Mine = 40;
		offset.x = 22;
		offset.y = 42;
	}

	if (difficulty == 3)
	{
		map_Size.cx = 864;
		map_Size.cy = 505;
		max_Block.x = 30;
		max_Block.y = 16;
		max_Mine = 99;
		offset.x = 39;
		offset.y = 42;

	}


	UIManager::GetInstance()->Init(hWnd, map_Size.cx, map_Size.cy, difficulty);
	RECT rt = { 0,0,map_Size.cx,map_Size.cy };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, NULL, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	HDC hdc = GetDC(hWnd);
	ResourceManager::GetInstance()->initBack(hdc, map_Size.cx, map_Size.cy);
	ReleaseDC(hWnd, hdc);

	for (int y = 0; y < max_Block.y; y++)
	{
		m_Blocks.push_back(vector<Block>());

		for (int x = 0; x < max_Block.x; x++)
		{
			Block block;
			block.Init( x, y);
			m_Blocks[y].push_back(block);
		}
	}

	Shuffle();
	Numbering();

	InputManager::GetInstance()->RegistKeyCode(MK_LBUTTON);
	InputManager::GetInstance()->RegistKeyCode(MK_RBUTTON);
}

bool GameScene::Input(float fETime)
{

	if (InputManager::GetInstance()->isKeyDown(MK_LBUTTON))
	{
		if (isGamePause)
		{
			if (MessageBox(m_hWnd,TEXT("Play again?"),TEXT("Play again?"),MB_YESNO) == IDYES)
			{
				ReStart();
			}
			return false;
		}

		string tag;

		for (int y = 0; y < max_Block.y; y++)
		{
			for (int x = 0; x < max_Block.x; x++)
			{
				tag = m_Blocks[y][x].CollisionCheck(InputManager::GetInstance()->GetMouse(), offset, MK_LBUTTON);
				
				if (tag == "Mine")
				{
					for (int yy = 0; yy < max_Block.y; yy++)
					{
						for (int xx = 0; xx < max_Block.x; xx++)
						{
							m_Blocks[yy][xx].ChanageState("MineOpen");
						}
					}
					isGamePause = true;
					UIManager::GetInstance()->Pause();
					return false ;
				}

				if (tag == "NonBlock" && m_Blocks[y][x].getHide())
				{
					ClickEvent(x,y);
				}

				if (tag == "NumBlock" && m_Blocks[y][x].getHide())
				{
					m_Blocks[y][x].ChanageState("BlockOpen");
				}
			}
		}

		if(WinChecker())
			return true;
	}

	if (InputManager::GetInstance()->isKeyDown(MK_RBUTTON))
	{
		if (isGamePause)
		{
			return false;
		}

		for (int y = 0; y < max_Block.y; y++)
		{
			for (int x = 0; x < max_Block.x; x++)
			{
				m_Blocks[y][x].CollisionCheck(InputManager::GetInstance()->GetMouse(), offset, MK_RBUTTON);
			}
		}

		if (WinChecker())
			return true;
	}

	return false;
}

void GameScene::Draw(HDC hdc)
{
	map->Draw(hdc,0,0,map_Size.cx,map_Size.cy);

	for (int y = 0; y < max_Block.y; y++)
	{
		for (int x = 0; x < max_Block.x; x++)
		{
			m_Blocks[y][x].Draw(hdc,offset.x,offset.y);
		}
	}
}

void GameScene::Release()
{
	for (int y = 0; y < max_Block.y; y++)
	{
		vector<Block>().swap(m_Blocks[y]);
	}

	vector<vector<Block> >().swap(m_Blocks);
}


void GameScene::ReStart()
{
	if (m_Difficulty == 1)
	{
		map_Size.cx = 260;
		map_Size.cy = 286;
		max_Block.x = 9;
		max_Block.y = 9;
		max_Mine = 1;
		offset.x = 12;
		offset.y = 24;
	}

	if (m_Difficulty == 2)
	{
		map_Size.cx = 463;
		map_Size.cy = 505;
		max_Block.x = 16;
		max_Block.y = 16;
		max_Mine = 40;
		offset.x = 22;
		offset.y = 42;
	}

	if (m_Difficulty == 3)
	{
		map_Size.cx = 864;
		map_Size.cy = 505;
		max_Block.x = 30;
		max_Block.y = 16;
		max_Mine = 99;
		offset.x = 39;
		offset.y = 42;
	}

	for (int y = 0; y < max_Block.y; y++)
	{
		for (int x = 0; x < max_Block.x; x++)
		{
			m_Blocks[y][x].Init(x,y);
		}
	}

	Shuffle();
	Numbering();
	UIManager::GetInstance()->Reset(m_Difficulty);
	isGamePause = false;
}

void GameScene::ClickEvent(int x, int y)
{
	m_Blocks[y][x].ChanageState("BlockOpen");

	if (y - 1 >= 0)
	{
		if (!m_Blocks[y - 1][x].getMine())
		{

			if (m_Blocks[y - 1][x].getNonBlock() && m_Blocks[y-1][x].getHide())
			{
				ClickEvent(x, y - 1);
			}
			else if(m_Blocks[y - 1][x].getHide())
			{
				m_Blocks[y - 1][x].ChanageState("BlockOpen");
			}
		}
	}

	if (y + 1 < max_Block.y)
	{
		if (!m_Blocks[y  + 1][x].getMine())
		{

			if (m_Blocks[y + 1][x].getNonBlock() && m_Blocks[y + 1][x].getHide())
			{
				ClickEvent(x, y + 1);
			}
			else if (m_Blocks[y + 1][x].getHide())
			{
				m_Blocks[y + 1][x].ChanageState("BlockOpen");
			}
		}
	}

	if (x - 1 >= 0)
	{
		if (!m_Blocks[y][x - 1].getMine())
		{
			if (m_Blocks[y][x - 1].getNonBlock() && m_Blocks[y][x - 1].getHide())
			{
				ClickEvent(x - 1, y);
			}
			else if (m_Blocks[y][x - 1].getHide())
			{
				m_Blocks[y][x - 1].ChanageState("BlockOpen");
			}
		}
	}

	if (x + 1 < max_Block.x)
	{
		if (!m_Blocks[y][x + 1].getMine())
		{
			if (m_Blocks[y][x + 1].getNonBlock() && m_Blocks[y][x + 1].getHide())
			{
				ClickEvent(x + 1,y);
			}
			else if (m_Blocks[y][x + 1].getHide())
			{
				m_Blocks[y][x + 1].ChanageState("BlockOpen");
			}
		}
	}

}

void GameScene::Shuffle()
{
	int max = max_Block.x * max_Block.y;
	int rand;
	int x;
	int y;
	vector<int> randIndex;

	for (int i = 0; i < max; i++)
	{
		randIndex.push_back(i);
	}

	for (int i = 0; i < max; i++)
	{
		swap(randIndex[Random(0, max)], randIndex[--max]);
	}

	max = max_Block.x * max_Block.y;

	for (int i = 0; i < max; i++)
	{
		swap(randIndex[Random(0, max)], randIndex[--max]);
	}

	for (int i = 0; i < max_Mine; i++)
	{
		rand = randIndex.front();
		randIndex.erase(randIndex.begin());
		y = rand / max_Block.x;
		x = rand % max_Block.x;
		m_Blocks[y][x].SetMine();
	}

}

void GameScene::Numbering()
{
	int count;

	for (int y = 0; y < max_Block.y; y++)
	{
		for (int x = 0; x < max_Block.x; x++)
		{
			count = 0;

			if (!m_Blocks[y][x].getMine())
			{
				for (int yy = y -1; yy < y + 2; yy++)
				{
					if (yy >= 0 && yy < max_Block.y )
					{
						for (int xx = x -1; xx < x + 2; xx++)
						{
							if (xx >= 0 && xx < max_Block.x )
							{
								if (m_Blocks[yy][xx].getMine())
								{
									count++;
								}
							}
						}
					}
				}

				m_Blocks[y][x].Numbering(count);
			}
		}
	}
}

bool GameScene::WinChecker()
{
	int count = 0;
	int flag = 0;

	flag = 0;
	count = 0;

	for (int y = 0; y < max_Block.y; y++)
	{
		for (int x = 0; x < max_Block.x; x++)
		{
			if (!m_Blocks[y][x].getMine() && !m_Blocks[y][x].getHide())
			{
				count++;
			}
		}
	}

	if (count == (max_Block.x * max_Block.y) - max_Mine)
	{
		for (int y = 0; y < max_Block.y; y++)
		{
			for (int x = 0; x < max_Block.x; x++)
			{
				if (m_Blocks[y][x].getMine())
				{
					m_Blocks[y][x].ChanageState("Flag");
				}
			}
		}

		UIManager::GetInstance()->Pause();
		UIManager::GetInstance()->Change(0);

		isGamePause = true;
		return true;
	}

	return false;
}

int Random(int min, int max)
{
	random_device rn;
	mt19937 rnd(rn());
	uniform_int_distribution<int> range(min, (max - 1));

	return range(rnd);
}

#include "GameMap.h"

GameMap::GameMap()
{
	isLoad = false;
}

GameMap::~GameMap()
{
}

void GameMap::Init(HWND hWnd, int width, int height)
{
	if (!isLoad)
	{
		back = new Animation();
		back_deco = new Animation();
		back_normal = new Animation();
		miter = new Animation();
		back->images.push_back(ResourceManager::GetInstance()->GetBitmap("back.bmp"));
		back_deco->images.push_back(ResourceManager::GetInstance()->GetBitmap("back_deco.bmp"));
		back_normal->images.push_back(ResourceManager::GetInstance()->GetBitmap("back_normal.bmp"));
		back_normal->images.push_back(ResourceManager::GetInstance()->GetBitmap("back_normal2.bmp"));
		miter->images.push_back(ResourceManager::GetInstance()->GetBitmap("miter.bmp"));
		HDC hdc = GetDC(hWnd);
		game_Map = ResourceManager::GetInstance()->CreateBack(hdc, width *11, height);
		ReleaseDC(hWnd, hdc);
	}

	back_normal->offset = 0;

	for (int j = 0; j < 11; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			back->images[back->offset]->Draw(game_Map->GetMapDC(), (((width - 6)*j)) + (i * (width / 9)), (height*0.2f) + (height - (height*0.2f)) / 5, (width / 9), ((height - (height*0.2f)) / 5) * 4 - 40);

			if (i == 3 && j != 10)
			{
				back_deco->images[back_deco->offset]->Draw(game_Map->GetMapDC(), ((width - 6)*j) + (i*(width / 9)), height*0.2f, (width / 9), (height - (height*0.2f)) / 5);
			}
			else
			{
				back_normal->images[back_normal->offset]->Draw(game_Map->GetMapDC(), ((width - 6)*j) + (i*(width / 9)), height*0.2f, (width / 9), (height - (height*0.2f)) / 5);
			}

		}

		miter->images[miter->offset]->Draw(game_Map->GetMapDC(), (width*j) + 30, height * 0.86f, 2);
		TextOut(game_Map->GetMapDC(), (width*j) + 80, height * 0.88f, TEXT(to_string(100 - (j * 10)).c_str()), strlen(to_string(100 - (j * 10)).c_str()));
	}

	back_normal->delayTime = 0.2f;
	back_normal->max = back_normal->images.size();
	focus = 20;
	m_MapSize.x = width;
	m_MapSize.y = height;
	isLoad = true;
	time = 0;
}

void GameMap::Update(float curTime)
{
	time += curTime;

	if (time >= 0.1f)
	{
		time = 0;

		back_normal->offset = (back_normal->offset + 1) % back_normal->images.size();

		for (int j = 9; j < 11; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				if (i != 3)
				{
					back_normal->images[back_normal->offset]->Draw(game_Map->GetMapDC(), ((m_MapSize.x - 6)*j) + (i*(m_MapSize.x / 9)), m_MapSize.y*0.2f, (m_MapSize.x / 9), (m_MapSize.y - (m_MapSize.y*0.2f)) / 5);
				}
			}
		}
	}
}

void GameMap::Release()
{
	if (isLoad)
	{
		delete back;
		delete back_deco;
		delete back_normal;
		delete miter;
		delete game_Map;
		isLoad = false;
	}
}

bool GameMap::MovingMap(int offset)
{
	focus += offset;

	return false;
}

void GameMap::Draw(HDC hdc)
{
	game_Map->Draw(hdc, 0, 0,1,focus,m_MapSize);
}

void GameMap::MapEvent()
{
}

void GameMap::Draw(HDC hdc, int x, int y)
{
}

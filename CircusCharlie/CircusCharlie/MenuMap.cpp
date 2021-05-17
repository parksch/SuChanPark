#include "MenuMap.h"

MenuMap::MenuMap()
{
	isLoad = false;
}

MenuMap::~MenuMap()
{
}

void MenuMap::Init(HWND hWnd, int width, int height)
{
	if (!isLoad)
	{
		blackBack = new Animation();
		menuName = new Animation();
		menuBar = new Animation();
		stars = new Animation();
		blackBack->images.push_back(ResourceManager::GetInstance()->GetBitmap("Black_Back.bmp"));
		menuName->images.push_back( ResourceManager::GetInstance()->GetBitmap("CircusCharlie.bmp"));
		menuBar->images.push_back( ResourceManager::GetInstance()->GetBitmap("Bar.bmp"));
		stars->images.push_back(ResourceManager::GetInstance()->GetBitmap("star.bmp"));
		stars->images.push_back(ResourceManager::GetInstance()->GetBitmap("star1.bmp"));
		stars->images.push_back(ResourceManager::GetInstance()->GetBitmap("star2.bmp"));
		HDC hdc = GetDC(hWnd);
		game_Map = ResourceManager::GetInstance()->CreateBack(hdc, width, height);
		ReleaseDC(hWnd, hdc);
	}

	UIManager::GetInstance()->Set();

	mapSize.x = width;
	mapSize.y = height;

	stars->delayTime = 0.2f;
	stars->max = stars->images.size();
	stars->oldTime = 0;

	menuBar->delayTime = 0.5f;
	menuBar->max = 2;
	menuBar->oldTime = 0;

	Draw(game_Map->GetMapDC(), width, height);
	isLoad = true;
}

void MenuMap::Update(float curTime)
{
	if (curTime - stars->oldTime >= stars->delayTime)
	{
		stars->oldTime = curTime;
		stars->offset = (stars->offset + 1) % stars->max;
		Draw(game_Map->GetMapDC(), mapSize.x, mapSize.y);
	}

	if (curTime - menuBar->oldTime >= menuBar->delayTime)
	{
		menuBar->oldTime = curTime;
		menuBar->offset = (menuBar->offset + 1) % menuBar->max;
		Draw(game_Map->GetMapDC(), mapSize.x, mapSize.y);
	}

}

void MenuMap::Release()
{
	if (isLoad)
	{
		delete blackBack;
		delete menuName ;
		delete menuBar  ;
		delete stars    ;
		delete game_Map ;
		isLoad = false;
	}
}

void MenuMap::Draw(HDC hdc)
{
	game_Map->Draw(hdc, 0, 0);
}

void MenuMap::Draw(HDC hdc, int x, int y)
{
	int count = 0;
	int m_Width = x;
	int m_Height = y;

	blackBack->images[blackBack->offset]->DrawBack(hdc);

	menuName->images[menuName->offset]->DrawBitBlt(hdc, x / 2 - 150, y *0.25f);

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			if (!(x == 0 && y == 0 || y == 0 && x == 17 || y == 7 && x == 0 || y == 7 && x == 17 || x > 0 && x < 17 && y >0 && y < 7))
			{
				stars->images[(stars->offset + count) % stars->max]->Draw(hdc, (m_Width / 2) + ((x - 9) * 15), (m_Height * 0.3f) + ((y - 4) * 15));
				count++;
			}
		}
	}

	if (menuBar->offset == 0)
	{
		menuBar->images[menuBar->offset]->DrawBitBlt(hdc, (x / 2.0f) - 245, y * 0.5f);
	}

}
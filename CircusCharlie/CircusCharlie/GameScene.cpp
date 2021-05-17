#include "GameScene.h"

GameScene::GameScene()
{
	isLoad = false;
}

GameScene::~GameScene()
{
}

void GameScene::Init(HWND hWnd, int width, int height)
{
	map = MapManager::GetInstance()->GetMap("Game");
	map->Init(hWnd, width, height);
	end.Init(width * 10, height,2);
	charlie.Init(width, height,2);
	
	for (int i = 0; i < 4; i++)
	{
		rings[i].Init(width, height, 2);
	}
	
	for (int i = 0; i < 9; i++)
	{
		fireJar[i].Init(width*(i+2), height,2);
	}

	InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	UIManager::GetInstance()->Ready();

	isLoad = true;
	isOver = false;
	m_Width = width;
	m_Height = height;
	endTime = 0;
	spawnTime = 0;
	ringsize = 0;
	camFocus = 0;
}

void GameScene::Update(float ETime)
{
	if (isOver)
	{
		if (charlie.Win())
		{
			map->Update(ETime);
			charlie.Update(ETime);

			if (UIManager::GetInstance()->isUIEventDone())
				endTime += ETime;

			if (endTime >= 3)
			{
				endTime = 0;
				SceneManager::GetInstance()->LoadScene(MAIN);
				return;
			}

		}
		else
		{
			endTime += ETime;

			if (endTime >= 3)
			{
				endTime = 0;
				if (UIManager::GetInstance()->getLife() <= 0)
				{
					SceneManager::GetInstance()->LoadScene(MAIN);
					return;
				}
				Retry();
			}
		}

		return;
	}

	spawnTime += ETime;

	if (spawnTime >= 4)
	{
		spawnTime = 0;
		rings[ringsize].Set();
		ringsize = (ringsize + 1) % 4;
	}
	
	for (int i = 0; i < 9; i++)
	{
		fireJar[i].Update(ETime);
	}

	for (int i = 0; i < 4; i++)
	{
		rings[i].Update(ETime);
	}
	
	if (!charlie.Update(ETime))
	{
		isOver = true;
	}
}

bool GameScene::Moving(int keyCode)
{
	if (camFocus - 5 > 0 && keyCode == VK_LEFT)
	{
		camFocus -= 5;
		map->MovingMap(-5);
		end.Move(5);

		for (int i = 0; i < 4; i++)
		{
			rings[i].Move(5);
		}

		for (int i = 0; i < 9; i++)
		{
			fireJar[i].Move(5);
		}

		return true;
	}

	if (camFocus + 5 < m_Width * 9 + m_Width *0.2f && keyCode == VK_RIGHT)
	{
		camFocus += 5;
		map->MovingMap(5);
		end.Move(-5);

		for (int i = 0; i < 4; i++)
		{
			rings[i].Move(-5);
		}

		for (int i = 0; i < 9; i++)
		{
			fireJar[i].Move(-5);
		}

		return true;
	}

	return false;
}

void GameScene::EndScene()
{

}

bool GameScene::Input(float ETime)
{
	charlie.Input(ETime);
	return false;
}

void GameScene::Draw(HDC hdc)
{
	map->Draw(hdc);
	end.Draw(hdc);

	for (int i = 0; i < 9; i++)
	{
		fireJar[i].Draw(hdc);
	}

	for (int i = 0; i < 4; i++)
	{
		rings[i].Draw(hdc);
	}

	charlie.Draw(hdc);

	for (int i = 0; i < 4; i++)
	{
		rings[i].Draw(hdc);
	}
}

void GameScene::Release()
{
	if (isLoad)
	{
		end.Release();
		map->Release();
		charlie.Release();
		
		for (int i = 0; i < 9; i++)
		{
			fireJar[i].Release();
		}

		for (int i = 0; i < 4; i++)
		{
			rings[i].Release();
		}

		isLoad = false;
	}
}

void GameScene::Retry()
{
	int offset;
	
	isOver = false;
	charlie.Init(m_Width, m_Height, 2);
	for (int i = 0; i < 4; i++)
	{
		rings[i].Init(m_Width, m_Height, 2);
	}

	offset = m_Width * ((camFocus / m_Width));

	if (offset <= 0)
	{
		offset = camFocus;
	}
	else
	{
		offset = camFocus - offset;
	}

	camFocus -= offset;
	map->MovingMap(-offset);
	end.Move(offset);

	for (int i = 0; i < 9; i++)
	{
		fireJar[i].Move(offset);
	}

	UIManager::GetInstance()->Ready();
}

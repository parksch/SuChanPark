#include "MenuScene.h"

MenuScene::MenuScene()
{
	isLoad = false;
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init(HWND hWnd, int width, int height)
{
	m_Width = width;
	m_Height = height;
	curTime = 0;
	map = MapManager::GetInstance()->GetMap("Menu");
	map->Init(hWnd, width, height);
	UIManager::GetInstance()->Set();
	InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	isLoad = true;
}

void MenuScene::Update(float ETime)
{
	curTime += ETime;
	map->Update(curTime);
}

bool MenuScene::Input(float ETime)
{
	if (InputManager::GetInstance()->isKeyUp(VK_SPACE))
	{
		SceneManager::GetInstance()->LoadScene(GAME);
		return true;
	}
}

void MenuScene::Draw(HDC hdc)
{
	map->Draw(hdc);
}

void MenuScene::Release()
{
	if (isLoad)
	{
		map->Release();
		isLoad = false;
	}
}

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
	m_CursorY = 0.6f;

	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_StartBar = new Animation();
	m_StartBar->Init(0);
	m_StartBar->Push(ResourceManager::GetInstance()->GetBitmap("Start.bmp"));

	m_EditBar = new Animation();
	m_EditBar->Init(0);
	m_EditBar->Push(ResourceManager::GetInstance()->GetBitmap("EditMode.bmp"));
	
	m_Menu = new Animation();
	m_Menu->Init(0);
	m_Menu->Push(ResourceManager::GetInstance()->GetBitmap("BattleCity.bmp"), m_MapSize.cx *0.8f, m_MapSize.cy *0.4f);

	m_Tank = new Animation();
	m_Tank->Init(0.2f);
	m_Tank->Push(ResourceManager::GetInstance()->GetBitmap("tank_right_00.bmp"), m_MapSize.cx / 13, m_MapSize.cy / 13);
	m_Tank->Push(ResourceManager::GetInstance()->GetBitmap("tank_right_01.bmp"), m_MapSize.cx / 13, m_MapSize.cy / 13);

	InputManager::GetInstance()->RegistKeyCode(VK_UP);
	InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	InputManager::GetInstance()->RegistKeyCode(VK_SPACE);

	isLoad = true;
}

bool MenuScene::Input(float fETime)
{
	if (InputManager::GetInstance()->isKeyDown(VK_SPACE))
	{
		if (m_CursorY == 0.6f)
		{
			SceneManager::GetInstance()->ChangeScene("Game");
			return true;
		}

		if (m_CursorY == 0.7f)
		{
			SceneManager::GetInstance()->ChangeScene("Edit");
			return true;
		}
	}

	if (InputManager::GetInstance()->isKeyDown(VK_UP))
	{
		if (m_CursorY != 0.6f)
		{
			m_CursorY = 0.6f;
		}
	}

	if (InputManager::GetInstance()->isKeyDown(VK_DOWN))
	{
		if (m_CursorY != 0.7f)
		{
			m_CursorY = 0.7f;
		}
	}

	return false;
}

void MenuScene::Update(float fETime)
{
	m_Tank->Update(fETime);
}

void MenuScene::Draw(HDC hdc)
{
	HBRUSH myBroush;
	HBRUSH oldBroush;
	myBroush = CreateSolidBrush(RGB(0, 0, 0));
	oldBroush = (HBRUSH)SelectObject(hdc, myBroush);
	Rectangle(hdc, 0, 0, m_MapSize.cx, m_MapSize.cy);
	SelectObject(hdc, oldBroush);
	DeleteObject(myBroush);

	m_Menu->Draw(hdc, m_MapSize.cx *0.5f - m_MapSize.cx *0.4f, m_MapSize.cy * 0.1f);

	m_StartBar->Draw(hdc, m_MapSize.cx * 0.6f - m_StartBar->GetSize().cx * 0.5f, m_MapSize.cy *0.6f);
	m_EditBar->Draw(hdc, m_MapSize.cx * 0.6f - m_EditBar->GetSize().cx * 0.5f, m_MapSize.cy *0.7f);
	m_Tank->Draw(hdc, m_MapSize.cx * 0.4f, m_MapSize.cy * m_CursorY);
}

void MenuScene::Release()
{
	if (isLoad)
	{
		delete m_StartBar;
		delete m_EditBar;
		delete m_Tank;
		delete m_Menu;
		isLoad = false;
	}
}

#include "MenuScene.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init(HWND hWnd, int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Menu = new Animation();
	m_Menu->Push(ResourceManager::GetInstance()->GetBitmap("Title.bmp"),m_MapSize.cx ,m_MapSize.cy );


	InputManager::GetInstance()->RegistKeyCode(MK_LBUTTON);

	isLoad = true;
}

void MenuScene::Recive(int code)
{
}

bool MenuScene::Input(float fETime)
{
	if (InputManager::GetInstance()->isKeyDown(MK_LBUTTON))
	{
		SceneManager::GetInstance()->ChangeScene("Select");
		return true;
	}
	return false;
}

void MenuScene::Update(float fETime)
{
}

void MenuScene::Draw(HDC hdc)
{
	m_Menu->Draw(hdc);
}

void MenuScene::Release()
{
	if (isLoad)
	{
		delete m_Menu;
		InputManager::GetInstance()->Clear();
		isLoad = false;
	}
}

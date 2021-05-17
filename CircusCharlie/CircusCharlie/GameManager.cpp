#include "GameManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "InputManager.h"
#include "MapManager.h"
#include "CollisionManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	SceneManager::DestoryInstance();
	TimeManager::DestoryInstance();
	ResourceManager::DestoryInstance();
	UIManager::DestoryInstance();
	InputManager::DestoryInstance();
	MapManager::DestoryInstance();
	CollisionManager::DestoryInstance();
}

int GameManager::Init(HINSTANCE hInstance, int width, int height)
{
	MSG Message;
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("CircusCharlie");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	HWND hWnd = CreateWindow(TEXT("CircusCharlie"), TEXT("CircusCharlie"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	SceneManager::GetInstance()->Init(hWnd, width, height);

	while (true)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			SceneManager::GetInstance()->Update();
		}
	}

	SceneManager::GetInstance()->Relase();
	return (int)Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

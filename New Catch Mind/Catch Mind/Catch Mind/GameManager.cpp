#include "ServerManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
	ServerManager::DestoryInstance();
	SceneManager::DestoryInstance();
	ResourceManager::DestoryInstance();
	TimeManager::DestoryInstance();
	InputManager::DestoryInstance();
}

int GameManager::Init(HINSTANCE hInstance, int width, int height)
{
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("Catch Mind");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	RECT rect = { 0,0,width,height };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);

	HWND hWnd = CreateWindow(TEXT("Catch Mind"), TEXT("Catch Mind"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	SceneManager::GetInstance()->Init(hWnd, hInstance, width, height);

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

	SceneManager::GetInstance()->Release();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static std::string str = "";

	switch (iMessage)
	{
	case WM_CHAR:

		if (VK_BACK != wParam && wParam != '\r')
		{
			str += wParam;
			SceneManager::GetInstance()->SendObjectMessage(GAME_CHAT, (char*)str.c_str());
		}

		return 0;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_BACK:
			if (str != "")
			{
				str = str.substr(0, str.size() - 1);
				SceneManager::GetInstance()->SendObjectMessage(GAME_CHAT, (char*)str.c_str());
			}
			break;
		case VK_RETURN:
			SceneManager::GetInstance()->SendObjectMessage(GAME_TEXT, (LPVOID)str.c_str());
			str.clear();
			break;
		default:
			break;
		}

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}


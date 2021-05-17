#include "ServerManager.h"
#include <Windows.h>
#include "GameManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

HINSTANCE g_hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	WNDCLASS wndClass;
	MSG Message;
	HWND hWnd;
	g_hInst = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = TEXT("Animation");
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	hWnd = CreateWindow
	(
		TEXT("Animation"),
		TEXT("Animation"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);

	if (ServerManager::GetInstance()->Init(hWnd) != -1)
	{
		while (GetMessage(&Message, NULL, 0, 0))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		ServerManager::GetInstance()->Release();
	}



	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		GameManager::GetInstance()->init(hWnd);
		ResourceManager::GetInstance()->Init(hWnd, g_hInst);
		return 0;
	case WM_LBUTTONDOWN:
		GameManager::GetInstance()->LButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam));
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_LBUTTONUP:
		GameManager::GetInstance()->Check(hWnd);
		return 0;
	case WM_PAINT:
		GameManager::GetInstance()->Display(hWnd);
		return 0;
	case WM_SOCKET:
		ServerManager::GetInstance()->ProcessSocketMessage(hWnd, iMessage, wParam, lParam);
		return 0;
	case WM_DESTROY:
		GameManager::DestoryInstance();
		ResourceManager::DestoryInstance();
		CollisionManager::DestoryInstance();
		ServerManager::GetInstance()->Release();
		ServerManager::DestoryInstance();
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
#include <Windows.h>
#include "GameManager.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_Inst;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE iPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	MSG Message;
	WNDCLASS WndClass;
	HWND hWnd;
	g_Inst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("Â¦ ¸ÂÃß±â");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	hWnd = CreateWindow(
		TEXT("Â¦ ¸ÂÃß±â"),
		TEXT("Â¦ ¸ÂÃß±â"),
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

	while (GetMessage(&Message,NULL,0,0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		GameManager::GetInstance()->Init(hWnd,g_Inst);
		return 0;
	case WM_PAINT:
		GameManager::GetInstance()->Draw(hWnd);
		return 0;
	case WM_LBUTTONDOWN:
		GameManager::GetInstance()->Click(hWnd,LOWORD(lParam), HIWORD(lParam));
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_TIMER:
		GameManager::GetInstance()->Update(hWnd);
		KillTimer(hWnd, 1);
		return 0;
	case WM_DESTROY:
		GameManager::DestoryInstance();
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

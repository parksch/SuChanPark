#include <Windows.h>
#include "ResourceManager.h"
#include "GameManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_Inst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int ncmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_Inst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("Hello");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	
	hWnd = CreateWindow(
		TEXT("Hello"), 
		TEXT("Hello"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		NULL, 
		(HMENU)NULL, 
		hInstance, 
		NULL);

	ShowWindow(hWnd, ncmdShow);

	while (GetMessage(&Message,NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		ResourceManager::GetInstance()->Init(hdc, g_Inst);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_PAINT:
		hdc = GetDC(hWnd);
		ResourceManager::GetInstance()->Draw(hdc, 1280, 1024);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_LBUTTONDOWN:
		GameManager::GetInstance()->CollisionCheck(hWnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		ResourceManager::GetInstance()->DestoryInstance();
		GameManager::GetInstance()->DestoryInstance();
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

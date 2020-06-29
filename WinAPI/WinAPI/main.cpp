#include <Windows.h>
#include "ResourceManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_Inst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int ncmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
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

	switch (iMessage)
	{
	case WM_CREATE:
		ResourceManager::GetInstance()->Init(hWnd, g_Inst);
		return 0;
	case WM_PAINT:
		ResourceManager::GetInstance()->Draw(hWnd, 1280, 1024);
		return 0;
	case WM_LBUTTONDOWN:
		ResourceManager::GetInstance()->CollisonCheck(hWnd,LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		ResourceManager::GetInstance()->DestoryInstance();
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

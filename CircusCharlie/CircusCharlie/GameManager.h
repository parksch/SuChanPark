#pragma once
#include <Windows.h>

using namespace std;

class GameManager
{
public:
	GameManager();
	~GameManager();
	int Init(HINSTANCE hInstance, int width, int height);
private:
	MSG Message;
	WNDCLASS WndClass;
	HINSTANCE hInstance;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


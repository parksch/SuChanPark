#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();
	int Init(HINSTANCE hInstance, int width, int height);
private:
	MSG Message;
	WNDCLASS WndClass;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
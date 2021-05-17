#pragma once
#include "ServerManager.h"
#include <Windows.h>

class Manager
{
public:
	int Init(HINSTANCE hInstance, int width, int height);
private:
	HWND m_hWnd;
	MSG m_Message;
	WNDCLASS m_WndClass;
	WSADATA m_wsa;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "SceneManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void Init(int width, int height);
	int Run();
private:
	RECT rt;
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pd3dDevice;
	MSG msg;
	WNDCLASSEX wc;
	HWND hWnd;
};

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


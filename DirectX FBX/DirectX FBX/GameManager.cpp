#include "GameManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "FBXModelLoader.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	SceneManager::DestoryInstance();
	TimeManager::DestoryInstance();
	InputManager::DestoryInstance();
	FBXModelLoader::DestoryInstance();

	if (m_pd3dDevice != NULL)
		m_pd3dDevice->Release();

	if (m_pD3D != NULL)
		m_pD3D->Release();

	UnregisterClass(TEXT("Game"), wc.hInstance);
}

void GameManager::Init(int width, int height)
{
	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,
	   0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
	   TEXT("Game"), NULL };

	RegisterClassEx(&wc);

	rt = { 0, 0, width, height };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, 0); //


	hWnd = CreateWindow("Game", "Game", WS_OVERLAPPEDWINDOW,
		100, 5, rt.right - rt.left, rt.bottom - rt.top, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

int GameManager::Run()
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice)))
	{
		return 0;
	}

	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);


	if (SceneManager::GetInstance()->Init(m_pd3dDevice, hWnd))
	{
		ZeroMemory(&msg, sizeof(msg));

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				SceneManager::GetInstance()->Update();
			}
		}

		SceneManager::GetInstance()->Release();
	}

	return 0;
}

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0L);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
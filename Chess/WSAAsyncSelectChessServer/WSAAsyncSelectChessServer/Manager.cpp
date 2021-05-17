#include "Manager.h"

int Manager::Init(HINSTANCE hInstance, int width, int height)
{
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WndClass.hInstance = hInstance;
	m_WndClass.lpfnWndProc = WndProc;
	m_WndClass.lpszClassName = TEXT("WSAAsyncSelect");
	m_WndClass.lpszMenuName = NULL;
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&m_WndClass);

	m_hWnd = CreateWindow(TEXT("WSAAsyncSelect"), TEXT("WSAAsyncSelect"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);

	if (ServerManager::GetInstance()->Init(m_hWnd) != -1)
	{
		while (GetMessage(&m_Message, NULL, 0, 0))
		{
			TranslateMessage(&m_Message);
			DispatchMessage(&m_Message);
		}

		ServerManager::GetInstance()->Release();
	}


	return (int)m_Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static bool isOn = false;

	switch (iMessage)
	{
	case WM_SOCKET:
		ServerManager::GetInstance()->ProcessSocketMessage(hWnd, iMessage, wParam, lParam,&isOn);
		break;
	case WM_DESTROY:
		ServerManager::GetInstance()->DestoryInstance();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

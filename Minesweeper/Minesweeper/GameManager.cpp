#include "GameManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "InputManager.h"
#include "resource.h"
HINSTANCE g_hInst;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	SceneManager::DestoryInstance();
	TimeManager::DestoryInstance();
	ResourceManager::DestoryInstance();
	UIManager::DestoryInstance();
	InputManager::DestoryInstance();
}

int GameManager::Init(HINSTANCE hInstance, int width, int height)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("Minesweeper");
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	HWND hWnd = CreateWindow(TEXT("Minesweeper"), TEXT("Minesweeper"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_DEFAULT,CW_DEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	SceneManager::GetInstance()->Init(hWnd);

	while (true)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			SceneManager::GetInstance()->Update();
		}
	}

	SceneManager::GetInstance()->Relase();
	return (int)Message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_GAME_DIFFICULTY:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutDlgProc);
			break;
		case ID_SCORE_VIEW:
			SceneManager::GetInstance()->Load();
			break;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}


BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static int result = 1;

	switch (iMessage)
	{
	case WM_INITDIALOG:
		CreateWindow(TEXT("button"), TEXT("Easy"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			50, 20, 100, 30, hDlg, (HMENU)3, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Nomal"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			50, 50, 100, 30, hDlg, (HMENU)4, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Hard"),
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			50, 80, 100, 30, hDlg, (HMENU)5, g_hInst, NULL);
		SendMessage(hDlg, BM_SETCHECK, BST_CHECKED, 3);
		result = 1;
		CheckRadioButton(hDlg, 3, 4, 3);

		return TRUE;
	case WM_COMMAND:

		switch (wParam)
		{
		case 3:
			result = 1;
			break;
		case 4:
			result = 2;
			break;
		case 5:
			result = 3;
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		case IDOK:
			SceneManager::GetInstance()->ReStart(result);
			EndDialog(hDlg, 0);
			return TRUE;
		}


		break;
	}

	return false;
}

BOOL CALLBACK ScoreDialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND hRadio;
	static int result = 1;

	switch (iMessage)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:

		switch (wParam)
		{
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		case IDOK:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}

	return false;
}

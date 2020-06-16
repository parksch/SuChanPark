#include <Windows.h>
#include <vector>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR szClassName = "ÅÊÅ©¸ÊÅø";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
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
	WndClass.lpszClassName = szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	int			nWidth, nHeight;//À©µµ¿ì Å©±â 
	nWidth = 1024 + GetSystemMetrics(SM_CXFRAME) * 2; 
	nHeight = 768 + GetSystemMetrics(SM_CYFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);

	hWnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, 0, 0, nWidth, nHeight, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

#define WIDTH 33
#define HEIGHT 25

int Width = 13;
int Height = 15;

int g_map[13][15];
int cur_select = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow("button", "0", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 800, 0 , 100, 30 , hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 40, 100, 30, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 80, 100, 30, hWnd, (HMENU)2, g_hInst, NULL);
		CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 800, 120, 100, 30, hWnd, (HMENU)3, g_hInst, NULL);

		CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 400, 100, 30, hWnd, (HMENU)100, g_hInst, NULL);
		CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 450, 100, 30, hWnd, (HMENU)101, g_hInst, NULL);
		CreateWindow("button", "LoadJson", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 300, 100, 30, hWnd, (HMENU)102, g_hInst, NULL);

		memset(g_map, 0, sizeof(int) * Width * Height);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		g_map[0][3] = 4;
		g_map[0][4] = 4;
		g_map[0][5] = 4;
		g_map[1][3] = 4;
		g_map[1][4] = 4;
		g_map[1][5] = 4;

		g_map[2][4] = 4;
		g_map[2][5] = 4;
		g_map[2][6] = 4;
		g_map[3][4] = 4;
		g_map[3][5] = 4;
		g_map[3][6] = 4;

		g_map[4][5] = 4;
		g_map[4][6] = 4;
		g_map[4][7] = 4;
		g_map[5][5] = 4;
		g_map[5][6] = 4;
		g_map[5][7] = 4;

		g_map[6][6] = 4;
		g_map[6][7] = 4;
		g_map[6][8] = 4;
		g_map[7][6] = 4;
		g_map[7][7] = 4;
		g_map[7][8] = 4;

		g_map[8][7] = 4;
		g_map[8][8] = 4;
		g_map[8][9] = 4;
		g_map[9][7] = 4;
		g_map[9][8] = 4;
		g_map[9][9] = 4;

		g_map[10][8] = 4;
		g_map[10][9] = 4;
		g_map[10][10] = 4;
		g_map[11][8] = 4;
		g_map[11][9] = 4;
		g_map[11][10] = 4;

		g_map[12][9] = 4;
		g_map[12][10] = 4;
		g_map[12][11] = 4;

		/*g_map[3][5] = 4;
		g_map[3][6] = 4;
		g_map[4][6] = 4;
		g_map[5][6] = 4;
		g_map[6][6] = 4;
		g_map[7][6] = 4;
		g_map[8][6] = 4;
		g_map[9][6] = 4;
		g_map[9][5] = 4;

		g_map[3][7] = 4;
		g_map[4][7] = 4;
		g_map[5][7] = 4;
		g_map[6][7] = 4;
		g_map[7][7] = 4;
		g_map[8][7] = 4;
		g_map[9][7] = 4;

		g_map[3][9] = 4;
		g_map[3][8] = 4;
		g_map[4][8] = 4;
		g_map[5][8] = 4;
		g_map[6][8] = 4;
		g_map[7][8] = 4;
		g_map[8][8] = 4;
		g_map[9][8] = 4;
		g_map[9][9] = 4;*/





		//test¿ë
		//for (int i = 2; i <= 5; i++)
		//{
		//	g_map[1][i] = 1;
		//}
		//for (int i = 2; i <= 5; i++)
		//{
		//	g_map[3][i] = 1;
		//}
		//for (int i = 2; i <= 5; i++)
		//{
		//	g_map[9][i] = 1;
		//}
		//for (int i = 2; i <= 5; i++)
		//{
		//	g_map[11][i] = 1;
		//}

		//for (int i = 9; i <= 12; i++)
		//{
		//	g_map[1][i] = 1;
		//}
		//for (int i = 9; i <= 12; i++)
		//{
		//	g_map[3][i] = 1;
		//}
		//for (int i = 9; i <= 12; i++)
		//{
		//	g_map[9][i] = 1;
		//}
		//for (int i = 9; i <= 12; i++)
		//{
		//	g_map[11][i] = 1;
		//}

		/*g_map[0][10] = 3;
		g_map[1][10] = 3;
		g_map[2][10] = 3;
		g_map[3][10] = 3;

		g_map[5][10] = 3;
		g_map[6][10] = 3;
		g_map[7][10] = 3;
		g_map[8][10] = 3;
		g_map[9][10] = 3;
		g_map[10][10] = 3;
		g_map[12][10] = 3;

		g_map[0][9] = 4;
		g_map[0][11] = 4;
		g_map[0][12] = 4;
		g_map[1][11] = 4;
		g_map[1][12] = 4;
		g_map[2][12] = 4;

		g_map[1][5] = 3;
		g_map[2][5] = 3;
		g_map[3][5] = 3;
		g_map[4][5] = 3;
		g_map[5][5] = 3;
		g_map[6][5] = 3;
		g_map[7][5] = 3;
		g_map[9][5] = 3;
		g_map[10][5] = 3;
		g_map[11][5] = 3;
		g_map[12][5] = 3;

		g_map[0][4] = 4;
		g_map[0][5] = 4;
		g_map[0][6] = 4;
		g_map[1][4] = 4;
		g_map[1][6] = 4;

		g_map[7][4] = 4;
		g_map[8][4] = 4;
		g_map[9][4] = 4;
		g_map[8][5] = 4;
		g_map[7][6] = 4;

		g_map[8][6] = 4;
		g_map[9][6] = 4;
		g_map[8][7] = 4;
		g_map[9][7] = 4;
		g_map[10][7] = 4;*/

		//g_map[1][7] = 1;
		//g_map[11][7] = 1;

		//g_map[5][6] = 1;
		//g_map[7][6] = 1;

		//g_map[6][1] = 1;
		//g_map[6][2] = 1;
		//g_map[6][3] = 1;
		//g_map[5][2] = 1;
		//g_map[7][2] = 1;

		//g_map[6][8] = 1;
		//g_map[6][9] = 1;
		//g_map[6][10] = 1;
		//g_map[5][9] = 1;
		//g_map[7][9] = 1;


		//g_map[5][13] = 1;
		//g_map[6][13] = 1;
		//g_map[7][13] = 1;
		//g_map[5][14] = 1;
		//g_map[7][14] = 1;





		for (int i = 0; i < Width; i++)
		{
			for (int j = 0; j < Height; j++)
			{
				if (g_map[i][j] == 0)
				{
					HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					Rectangle(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);
				}
				else if (g_map[i][j] == 1)
				{
					HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					Ellipse(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);
				}
					
				else if (g_map[i][j] == 2)
				{
					HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					HBRUSH hBlack = (HBRUSH)GetStockObject(BLACK_BRUSH);
					HBRUSH old = (HBRUSH)SelectObject(hdc, hBlack);
					Ellipse(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);
					SelectObject(hdc, old);
				}

				else if (g_map[i][j] == 3)
				{
					HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					HBRUSH hBlack = (HBRUSH)GetStockObject(BLACK_BRUSH);
					HBRUSH old = (HBRUSH)SelectObject(hdc, hBlack);
					Ellipse(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);
					SelectObject(hdc, old);
					DeleteObject(m_oldCollider);
				}
				else if (g_map[i][j] == 4)
				{
					HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					HBRUSH hBlack = (HBRUSH)GetStockObject(BLACK_BRUSH);
					HBRUSH old = (HBRUSH)SelectObject(hdc, hBlack);
					Ellipse(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);
					SelectObject(hdc, old);
					DeleteObject(m_oldCollider);
				}
			}
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 0:
		case 1:
		case 2:
			cur_select = LOWORD(wParam);
			break;
		case 100: //SAVE
			{
				OPENFILENAME OFN;
				char str[300];
				char lpstrFile[MAX_PATH] = "";
				char lpstrPath[MAX_PATH] = "";

				memset(&OFN, 0, sizeof(OPENFILENAME));
				OFN.lStructSize = sizeof(OPENFILENAME);
				OFN.hwndOwner = hWnd;
				OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
				OFN.lpstrFile = lpstrFile;
				OFN.nMaxFile = 256;
				GetCurrentDirectory(MAX_PATH, lpstrPath);
				OFN.lpstrInitialDir = lpstrPath;
				if (GetSaveFileName(&OFN) == 0)
				{
					DWORD err = CommDlgExtendedError();
					break;	
				}

				HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
				for (int i = 0; i < Width; i++)
				{
					for (int j = 0; j < Height; j++)
					{
						DWORD writeB;
						WriteFile(hFile, &g_map[i][j], sizeof(int), &writeB, NULL);
					}
				}
				CloseHandle(hFile);
				InvalidateRect(hWnd, NULL, false);
			}
			break;
		case 101://load
			{
				HANDLE hFile = CreateFile("Stage5.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				for (int i = 0; i < Width; i++)
				{
					for (int j = 0; j < Height; j++)
					{
						DWORD readB;
						ReadFile(hFile, &g_map[i][j], sizeof(int), &readB, NULL);
					}
				}
				CloseHandle(hFile);
				InvalidateRect(hWnd, NULL, false);
			}
			break;
		}
		return 0;
	}
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			if ((pt.x < WIDTH * Width && pt.x > 0) && (pt.y < HEIGHT * Height && pt.y > 0))
			{
				g_map[pt.x / WIDTH][pt.y / HEIGHT] = cur_select;
				InvalidateRect(hWnd, NULL, false);
			}
		}
		return 0;
	case WM_RBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
		}
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

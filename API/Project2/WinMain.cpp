#include <Windows.h>
#include <tchar.h>
#include <math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("HELLO");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, PSTR szCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass,
		lpszClass,
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL 
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message,NULL,0,0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

int x = 0;
int y = 0;
int mx = 0;
int my = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect = {200,200,800,400};
	switch (iMessage)
	{ 
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			x -= 5;
			break;
		case VK_RIGHT:
			x += 5;
			break;
		case VK_UP:
			y -= 5;
			break;
		case VK_DOWN:
			y += 5;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc =BeginPaint(hWnd, &ps);
		Ellipse(hdc, 100 + x, 100 + y, 200 + x, 200 + y);
		Rectangle(hdc, rect.left, rect.top, rect.right,rect.bottom);
		if (mx - 50 < rect.left)
		{
			mx -= 50 + (mx - 100 - rect.left);
		}
		if (mx + 50 > rect.right)
		{
			mx += 50 - (mx + 100 - rect.right );
		}
		if (my - 50 < rect.top)
		{
			my -= 50 + (my - 100 - rect.top);
		}
		if (my + 50 > rect.bottom)
		{
			my += 50 - (my + 100 - rect.bottom);
		}
		Ellipse(hdc,  mx - 50, my - 50, mx + 50 , 50 +my);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
			return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}



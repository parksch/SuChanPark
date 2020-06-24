#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimeProc(HWND hwnd, UINT uMsg, UINT IdEvent, DWORD DwTime);
HINSTANCE g_hinst;
LPCTSTR lpszClass = TEXT("¾È³ç");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, PSTR szCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

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
		200, 
		300, 
		1000, 
		1000,
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect = { 300,10,800,300 };
	SYSTEMTIME st;
	string str;
	static int offsetX = 10;
	static int offsetY = 10;
	static RECT ellipse = { 310, 20, 350, 60 };

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		break;
	case WM_TIMER:
		if (ellipse.left + offsetX < rect.left)
		{
			offsetX = 10;
		}
		if (ellipse.right + offsetX > rect.right)
		{
			offsetX = -10;
		}

		if (ellipse.top + offsetY < rect.top)
		{
			offsetY = 10;
		}
		if (ellipse.bottom + offsetY > rect.bottom)
		{
			offsetY = -10;
		}

		ellipse.left += offsetX;
		ellipse.right += offsetX;
		ellipse.top += offsetY;
		ellipse.bottom += offsetY;

		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		GetLocalTime(&st);
		hdc = BeginPaint(hWnd, &ps);
		str = to_string(st.wHour) + "½Ã " + to_string(st.wMinute) + "ºÐ " + to_string(st.wSecond);
		TextOut(hdc, 100, 260, TEXT( str.c_str()), strlen(str.c_str()));
		Ellipse(hdc, 10, 10, 250, 250);

		for (int i = 1; i < 13; i++)
		{
			TextOut(hdc, 
				125 + sin(i * M_PI / 6) * 100,
				125 - cos(i * M_PI / 6) * 100,
				TEXT(to_string(i).c_str()), 
				strlen(to_string(i).c_str()));
		}

		MoveToEx(hdc, 125, 125, NULL);
		LineTo(hdc, 125 + sin(st.wSecond / 60.0f * (2 * M_PI)) * 100, 125 - cos(st.wSecond / 60.0f * (2 * M_PI)) * 100);
		MoveToEx(hdc, 125, 125, NULL);
		LineTo(hdc, 125 + sin(st.wMinute / 60.0f * (2 * M_PI)) * 80, 125 - cos(st.wMinute / 60.0f * (2 * M_PI)) * 80);
		MoveToEx(hdc, 125, 125, NULL);
		LineTo(hdc, 125 + sin(st.wHour / 12.0f * (2 * M_PI)) * 40, 125 - cos(st.wHour / 12.0f * (2 * M_PI)) * 40);


		Rectangle(hdc, rect.left,rect.top, rect.right, rect.bottom);
		Ellipse(hdc, ellipse.left, ellipse.top, ellipse.right, ellipse.bottom);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

}
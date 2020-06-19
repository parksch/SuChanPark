#include <Windows.h>
#include <tchar.h>
#include <math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("HELLO");

typedef struct Pos
{
	struct Pos(int X, int Y) : x(X), y(Y) {}
	struct Pos() : x(0), y(0) {}
	int x;
	int y;
}POS;

POS Lerp(POS st, POS end, float r);
POS Bezier(POS p1, POS p2, POS p3, POS p4, float r);

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POS p1;
	POS p2;
	POS p3;
	POS u;
	switch (iMessage)
	{ 
	case WM_PAINT: 
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 360; i++) 
			SetPixel(hdc, 300 + (sin(i) * 135), 300 + (cos(i) * 90), RGB(255, 0, 0));

		for (int i = 1; i < 91; i++)
		{   
			p1.x = 0;
			p1.y = -90;
			p2.x = 90;
			p2.y = -90;
			p3.x = 90;
			p3.y = 0;
			u = Bezier(p1, Lerp(p1, p2, 0.5f), Lerp(p2, p3, 0.5f), p3, i / 90.0f);
			SetPixel(hdc, 300 + (u.x), 100 + (u.y), RGB(0, 255, 0));
		}

		for (int i = 1; i < 91; i++)
		{
			p1.x = 90;
			p1.y = 0;
			p2.x = 90;
			p2.y = 90;
			p3.x = 0;
			p3.y = 90;
			u = Bezier(p1, Lerp(p1, p2, 0.5f), Lerp(p2, p3, 0.5f), p3, i / 90.0f);
			SetPixel(hdc, 300 + (u.x), 100 + (u.y), RGB(0, 255, 0));
		}

		for (int i = 1; i < 91; i++)
		{
			p1.x = 0;
			p1.y = 90;
			p2.x = -90;
			p2.y = 90;
			p3.x = -90;
			p3.y = 0;
			u = Bezier(p1, Lerp(p1, p2, 0.5f), Lerp(p2, p3, 0.5f), p3, i / 90.0f);
			SetPixel(hdc, 300 + (u.x), 100 + (u.y), RGB(0, 255, 0));
		}

		for (int i = 1; i < 91; i++)
		{
			p1.x = -90;
			p1.y = 0;
			p2.x = -90;
			p2.y = -90;
			p3.x = 0;
			p3.y = -90;
			u = Bezier(p1, Lerp(p1, p2, 0.5f), Lerp(p2, p3, 0.5f), p3, i / 90.0f);
			SetPixel(hdc, 300 + (u.x), 100 + (u.y), RGB(0, 255, 0));
		}

	/*	Rectangle(hdc, 50, 100, 200, 180); 
		Ellipse(hdc, 220, 100, 400, 200); */
		EndPaint(hWnd, &ps);
		return 0; 
	case WM_DESTROY:
		PostQuitMessage(0);
			return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}

POS Lerp(POS st, POS end, float r)
{
	POS result;
	result = POS(st.x + ((end.x - st.x) * r), st.y + ((end.y - st.y) * r));
	return result;
}

POS Bezier(POS p1, POS p2, POS p3, POS p4, float r)
{
	POS a = Lerp(p1,p2,r);
	POS b = Lerp(p2, p3, r);
	POS c = Lerp(p3, p4, r);
	POS d = Lerp(a,b,r);
	POS e = Lerp(b,c,r);
	return Lerp(d,e,r);
}


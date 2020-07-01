#pragma once
#include <windows.h>

class BitMap
{
private:
	HDC		MemDC;
	HBITMAP	pBitMap;
	HBITMAP pBitOld;
	SIZE	size;
public:
	BitMap();
	
	void Init(HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);

	~BitMap();
};


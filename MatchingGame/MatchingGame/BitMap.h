#pragma once
#include <Windows.h>
class BitMap
{
public:
	BitMap();
	~BitMap();
	void Init(HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, int x, int y, float spX, float spY);
	SIZE GetSize() { return size; }
private:
	HDC		MemDC;
	HBITMAP	pBitMap;
	HBITMAP pBitOld;
	SIZE	size;
	POINT	startPos;
};


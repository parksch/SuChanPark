#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, HINSTANCE hInst, int id)
{
	MemDC = CreateCompatibleDC(hdc);
	pBitMap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(id));
	pBitOld = (HBITMAP)SelectObject(MemDC, pBitMap);

	BITMAP BitMap_Info;

	GetObject(pBitMap, sizeof(BitMap_Info), &BitMap_Info);
	size.cx = BitMap_Info.bmWidth;
	size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y, int spX, int spY)
{
	StretchBlt(hdc, x, y, size.cx * spX, size.cy * spY, MemDC, 0, 0, size.cx, size.cy, SRCCOPY);
}

BitMap::~BitMap()
{
	SelectObject(MemDC, pBitOld);
	DeleteObject(pBitMap);
	DeleteDC(MemDC);
}

#include "BitMap.h"

BitMap::BitMap()
{

}

BitMap::~BitMap()
{
	SelectObject(MemDC, pBitOld);
	DeleteObject(pBitMap);
	DeleteDC(MemDC);
}

void BitMap::Init(HDC hdc, HINSTANCE hInst, int id,std::string path)
{
	MemDC = CreateCompatibleDC(hdc);
	pBitMap = (HBITMAP)LoadImage(hInst,TEXT(path.c_str()),IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	pBitOld = (HBITMAP)SelectObject(MemDC, pBitMap);
	m_ID = id;
	BITMAP BitMap_Info;

	GetObject(pBitMap, sizeof(BitMap_Info), &BitMap_Info);
	size.cx = BitMap_Info.bmWidth;
	size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y, bool invisible)
{
	if (invisible)
	{
		TransparentBlt(hdc, x * size.cx * 0.5f, y * size.cy * 0.5f, size.cx * 0.5f, size.cy * 0.5f, MemDC, 0, 0, size.cx, size.cy, RGB(255, 0, 255));
	}
	else
	{
		StretchBlt(hdc, x * size.cy * 0.5f, y * size.cy * 0.5f, size.cx * 0.5f, size.cy * 0.5f, MemDC, 0, 0, size.cx, size.cy, SRCCOPY);
	}
}

#include "BitMap.h"
#include "ResourceManager.h"

BitMap::BitMap()
{
}

BitMap::~BitMap()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}

void BitMap::Init(HDC hdc, string path)
{
	BITMAP info;
	string image = "image/" + path;
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitMap = (HBITMAP)LoadImage(NULL, TEXT(image.c_str()), IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	GetObject(m_hBitMap, sizeof(BITMAP), &info);

	size.cx = info.bmWidth;
	size.cy = info.bmHeight;
}

void BitMap::InitBack(HDC hdc, int width, int height)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitMap = CreateCompatibleBitmap(hdc, width, height);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	size.cx = width;
	size.cy = height;
}

void BitMap::DrawBack(HDC hdc)
{
	BitBlt(hdc, 0, 0, size.cx, size.cy, m_hMemDC, 0, 0, SRCCOPY);
}

void BitMap::DrawBitBlt(HDC hdc, int x, int y)
{
	BitBlt(hdc, x, y, size.cx, size.cy, m_hMemDC, 0, 0, SRCCOPY);
}

void BitMap::Draw(HDC hdc, int x, int y, float multiple)
{
	TransparentBlt(hdc, x, y, size.cx * multiple, size.cy * multiple, m_hMemDC, 0, 0, size.cx, size.cy, RGB(255, 0, 255));
}

void BitMap::Draw(HDC hdc, int x, int y, float sizeX,float sizeY)
{
	TransparentBlt(hdc, x, y, sizeX, sizeY, m_hMemDC, 0, 0, size.cx, size.cy, RGB(255, 0, 255));
}

void BitMap::Draw(HDC hdc, int x, int y, float multiple, int focus, POINT map_size)
{
	TransparentBlt(hdc, x, y, map_size.x, size.cy * multiple, m_hMemDC, focus, 0, map_size.x, size.cy, RGB(255, 0, 255));
}



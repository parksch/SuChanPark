#include "BitMap.h"

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
	m_MapSize.cx = info.bmWidth;
	m_MapSize.cy = info.bmHeight;
}

void BitMap::InitBack(HDC hdc, int width, int height)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitMap = CreateCompatibleBitmap(hdc, width, height);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	m_MapSize.cx = width;
	m_MapSize.cy = height;
}

void BitMap::DrawBack(HDC hdc)
{
	BitBlt(hdc, 0, 0, m_MapSize.cx, m_MapSize.cy, m_hMemDC, 0, 0, SRCCOPY);
}

void BitMap::Draw(HDC hdc, int x, int y, float sizeX, float sizeY)
{
	TransparentBlt(hdc, x, y, sizeX, sizeY, m_hMemDC, 0, 0, m_MapSize.cx, m_MapSize.cy, RGB(255, 0, 255));
}

void BitMap::Draw(HDC hdc, int x, int y, SIZE size, RECT *rect)
{
	TransparentBlt(hdc, x, y, size.cx, size.cy, m_hMemDC, rect->left, rect->top, rect->right, rect->bottom, RGB(255, 0, 255));
}

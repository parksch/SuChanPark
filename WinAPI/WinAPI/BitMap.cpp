#include "BitMap.h"

BitMap::BitMap()
{
}

BitMap::~BitMap()
{
	SelectObject(MemDC, m_pOldBitMap);
	DeleteObject(m_pMyBitMap);
	DeleteDC(MemDC);
}

void BitMap::Init(HDC hdc, HINSTANCE hInst,int code)
{
	MemDC = CreateCompatibleDC(hdc);
	m_pMyBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(code));
	m_pOldBitMap = (HBITMAP)SelectObject(MemDC, m_pMyBitMap);
	BITMAP Bit_Info;
	GetObject(m_pMyBitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y)
{
	m_StartX = x;
	m_StartY = y;
	BitBlt(hdc, m_StartX, m_StartY, m_size.cx, m_size.cy, MemDC, 0, 0, SRCCOPY);
}

bool BitMap::CollisionCheck(int x, int y)
{
	if ((x >= m_StartX && x <= m_StartX +  m_size.cx) &&  (y >= m_StartY && y <= m_StartY + m_size.cy))
	{
		return true;
	}

	return false;
}


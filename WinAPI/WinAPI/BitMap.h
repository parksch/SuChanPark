#pragma once
#include <Windows.h>

class BitMap
{
public:
	BitMap();
	~BitMap();
	void Init(HDC hdc,HINSTANCE hInstance,int code);
	void Draw(HDC hdc, int x, int y);
	bool CollisionCheck(int x,int y);
private:
	HDC		MemDC;
	HBITMAP	m_pMyBitMap;
	HBITMAP	m_pOldBitMap;
	SIZE	m_size;
	int m_StartX;
	int m_StartY;
};


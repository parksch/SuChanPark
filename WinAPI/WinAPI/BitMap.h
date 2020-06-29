#pragma once
#include <Windows.h>

class BitMap
{
public:
	BitMap();
	~BitMap();
	void Init(HDC hdc,HINSTANCE hInstance,int code);
	void Point(int x, int y);
	bool CollisionCheck(int x,int y);
	HDC GetMemDC(){ return MemDC; }
	SIZE GetSize() { return m_size; }
private:
	HDC		MemDC;
	HBITMAP	m_pMyBitMap;
	HBITMAP	m_pOldBitMap;
	SIZE	m_size;
	int m_StartX;
	int m_StartY;
};


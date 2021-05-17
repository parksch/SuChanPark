#pragma once
#include <Windows.h>
#include <vector>
#pragma comment(lib, "msimg32.lib")

class BitMap
{
public:
	BitMap();
	~BitMap();
	void Init(HDC hdc, HINSTANCE hInst, int id,std::string path);
	void Draw(HDC hdc, int x, int y, bool invisible);
	SIZE GetSize() { return size; }
	int Getid() { return m_ID; }
private:
	int m_ID;
	HDC		MemDC;
	HBITMAP	pBitMap;
	HBITMAP pBitOld;
	SIZE	size;
};


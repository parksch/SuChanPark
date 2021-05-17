#pragma comment(lib,"Msimg32.lib")
#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class BitMap
{
public:
	BitMap();
	~BitMap();
	void Init(HDC hdc, string path);
	void InitBack(HDC hdc, int width, int height);
	void DrawBack(HDC hdc);
	void Draw(HDC hdc, int x, int y, float sizeX, float sizeY);
	void Draw(HDC hdc, int x, int y, SIZE size, RECT *rect);
	SIZE GetSize() { return m_MapSize; }
	HDC GetMapDC() { return m_hMemDC; }
private:
	HDC m_hMemDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitmap;
	SIZE m_MapSize;
};

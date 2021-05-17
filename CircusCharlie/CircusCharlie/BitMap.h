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
	void DrawBitBlt(HDC hdc, int x, int y);
	void Draw(HDC hdc, int x, int y, float multiple = 1);
	void Draw(HDC hdc, int x, int y, float sizeX, float sizeY);
	void Draw(HDC hdc, int x, int y, float multiple, int focus, POINT map_size);
	SIZE GetSize() { return size; }
	HDC GetMapDC() { return m_hMemDC; }
private:
	HDC m_hMemDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBitmap;
	SIZE size;
};

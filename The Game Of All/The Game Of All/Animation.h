#pragma once
#include <vector>
#include "BitMap.h"
using namespace std;

class Animation
{
public:
	Animation();
	~Animation();
	void Init(float delay);
	void Reset();
	void Push(BitMap* bitmap, int SizeX, int SizeY);
	void Push(BitMap* bitmap);
	void Update(float eTime);
	void Draw(HDC hdc, int posX = 0, int posY = 0);
	void Draw(HDC hdc, int posX, int posY, int gage,int max =1);
	void Draw(HDC hdc, int x, int y, SIZE size, RECT *rect);
	bool getOver() { return (offset == max - 1); }
	SIZE GetSize() { return m_Size[offset]; }
protected:
	vector<BitMap*> images;
	vector<SIZE> m_Size;
	float oldTime;
	int offset;
	int max;
	float delayTime;
};


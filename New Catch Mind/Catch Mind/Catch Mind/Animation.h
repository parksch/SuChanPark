#pragma once
#include "ResourceManager.h"
#include "BitMap.h"
#include <vector>
#include <string>

class Animation
{
public:
	Animation();
	~Animation();
	void Init(float delay);
	void Push(std::string str, int sizeX, int sizeY);
	void Push(std::string str);
	void Update(float eTime);
	void Draw(HDC hdc, int posX = 0, int posY = 0);
	void Draw(HDC hdc, int x, int y, SIZE size, RECT *rect);
	bool getOver() { return (m_Offset == m_Max - 1); }
	SIZE GetSize() { return m_Size[m_Offset]; }
private:
	float m_DelayTime;
	float m_OldTime;
	int m_Offset;
	int m_Max;
	std::vector<BitMap*> m_Images;
	std::vector<SIZE> m_Size;
};


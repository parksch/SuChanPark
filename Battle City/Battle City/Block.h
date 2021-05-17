#pragma once
#include "Status.h"

class Block : public Object
{
public:
	Block();
	~Block();
	void Init(int width, int height, int startX, int startY);
	void BlockSet(int code);
	void Draw(HDC hdc);
	string CollisionCheck(RECT *rect, string tag, int code);
private:
	void CollisionBoxSet(int code);
	int m_BlockCode;
	SIZE m_BlockSize;
	SIZE m_ImageSize;
	RECT m_CollisionBox;
	RECT m_DrawBox;
	POINT m_Pos;
	Animation *m_Block;
};

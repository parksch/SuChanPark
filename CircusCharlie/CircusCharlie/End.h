#pragma once
#include "EngineHeader.h"

class End : public EnvironmentObject
{
public:
	End();
	~End();
	void Init(int width, int heightint, int multiple);
	bool Update(float eTime);
	void Release();
	void Draw(HDC hdc);
	void Move(int offset);
	string CollisionCheck(RECT rect);
private:
	int m_Multiple;
	bool isLoad;
	Animation* end;
	RECT box;
	SIZE size;
	POINT pos;
};

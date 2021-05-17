#pragma once
#include "Status.h"

class TimeBar : public Object
{
public:
	TimeBar();
	~TimeBar();
	void Init(int width, int height);
	void Update(float efTime);
	void Draw(HDC hdc);
	string CollisionCheck(RECT *rect, string tag, int code);
private:
	SIZE m_size;
	Animation *m_TimeBar;
	float time;
	int m_Gage;
};


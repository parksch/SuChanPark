#pragma once
#include "Status.h"

class SmallExplosion : public Effect
{
public:
	SmallExplosion();
	~SmallExplosion();
	 void Init(int width, int height);
	 void Update(float eTime);
	 void Draw(HDC hdc);
	 bool getOver() { return isOver; }
	 Effect* Create();
	 void Set(POINT pos);
private:
	bool isOver;
	SIZE m_MapSize;
	POINT m_Pos;
	Animation *m_Explosion;
};

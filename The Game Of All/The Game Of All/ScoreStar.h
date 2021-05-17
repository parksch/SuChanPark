#pragma once
#include "Projectile.h"

class ScoreStar : public Projectile
{
public:
	ScoreStar();
	~ScoreStar();
	void ImageSet();
	void CollisionUpdate();
	void SetCombo(int combo);
	bool Set(int combo);
	void Draw(HDC hdc);
	string CollisionEvent();
private:
	STAR m_curStar;
	Animation *m_Star[3];
	int m_Combo;
};


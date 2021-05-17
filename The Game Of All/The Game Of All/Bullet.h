#pragma once
#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet();
	~Bullet();
	void ImageSet();
	void CollisionUpdate();
	bool Set();
	void Draw(HDC hdc);
	string CollisionEvent();
private:
	Animation *m_Projectile;
};


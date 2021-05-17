#pragma once
#include "Status.h"

class Projectile : public Object
{
public:
	Projectile() {};
	virtual ~Projectile() {};
	void Init(int width, int height); 
	void Update(float efTime);
	string CollisionCheck(RECT *rect, string tag, int code);

	virtual void Draw(HDC hdc) = 0;
	virtual void CollisionUpdate() = 0;
	virtual string CollisionEvent() = 0;
	virtual void ImageSet() = 0;
protected:
	float m_MoveTime;
	bool isLive;
	RECT m_CollisionBox;
	SIZE m_MapSize;
	POINT m_pos;
	POINT m_Offset;
};


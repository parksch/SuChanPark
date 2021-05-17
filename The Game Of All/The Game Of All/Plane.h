#pragma once
#include "Status.h"

class Plane : public Object
{
public:
	Plane();
	~Plane();
	void Init(int width, int height);
	void Update(float eFtime);
	void Set();
	void Draw(HDC hdc);
	string CollisionCheck(RECT *rect, string tag, int code);
private:
	bool isLive;
	bool isInvincible;
	bool isHide;
	float m_InvincibleTime;
	float m_SpawnTime;
	float m_HideTime;
	POINT m_Pos;
	SIZE m_MapSize;
	Animation *m_Plane;
	RECT m_CollisionBox;
};


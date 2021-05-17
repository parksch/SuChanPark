#pragma once
#include "Status.h"

class Fever : public Object
{
public:
	Fever();
	~Fever();
	void Init(int width, int height);
	void Update(float eftime);
	void Set(int delay);
	void Draw(HDC hdc);
	void Up();
	void Down();
	string CollisionCheck(RECT *rect, string tag, int code);
private:
	int SetLimit(int offset);
	bool isFever;
	bool isFeverEffect;
	SIZE m_MapSize;
	Animation *m_Fever[4];
	Animation *m_FeverEffect;
	float m_GageDelay;
	float m_EffectDelay;
	float m_FeverTime;
	float m_HitGageDown;
	int m_HitOffset;
	int m_Gage;
	int m_GageDown;
};


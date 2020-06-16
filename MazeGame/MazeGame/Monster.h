#pragma once
#include "GameManager.h"
#include "Object.h"

#define MOVEDELAY 500
enum STATE
{
	STATE_SLEEP,
	STATE_PARTROL,
	STATE_TRACKING
};

class Boss : public BossAlarm
{
public:
	Boss(int code, int x, int y);
	~Boss();
	void Collision_Handle(int Code) ;
	void Update();
	void SpawnBoss()
	{
		isAppear = true;
		Notification();
	}
private:
	STATE m_CurState;
	int offset;
	int time;
};

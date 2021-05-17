#pragma once
#include "EngineHeader.h"

enum STATE
{
	IDLE,
	MOVE,
	JUMP,
	DEAD
};

class Charlie : public Object
{
public:
	Charlie();
	~Charlie();
	void Init(int width, int heightint,int multiple) ;
	bool Update(float eTime) ;
	void Release() ;
	bool Input(float eTime);
	void Draw(HDC hdc) ;
	void Move(int keyCode);
	int GetPos() { return pos.x; }
	bool Win() { return isWin; }
	string CollisionCheck(RECT rect);
private:
	bool isWin;
	bool isLoad;
	bool isDead;
	bool isJump;
	int input;
	int m_Multiple;
	int jumpOffset;
	int aniSize;
	float curTime;
	RECT lion ;
	RECT human;
	POINT pos;
	SIZE size;
	Animation* curAni;
	Animation* charlie_Move;
	Animation* charlie_Win;
	Animation* charlie_Die;
};


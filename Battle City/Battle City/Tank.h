#pragma once
#include "Status.h"
#include "Projectile.h"

class Tank :public Object
{
public:
	Tank();
	virtual ~Tank();
	string CollisionCheck(RECT *rect, string tag, int code);
	virtual void Update(float eTime);
	virtual void InitAni();
	void Init(int width, int height,TYPE type,int code);
	string Move(int offsetX, int offsetY);
	void Set(int x, int y, MOVE_STATE state);
	void Draw(HDC hdc);
	void Shoot();
private:
	void StateExcute();
	void StateChange();
protected:
	int m_Code;
	TYPE m_Type;
	float delay;
	bool isAlive;
	RECT m_CollisionBox;
	string m_MoveCode;
	SIZE m_MapSize;
	MOVE_STATE m_State;
	Animation *m_TankMoves[4];
	Projectile *m_Projectile;
	POINT m_ShootPos;
	POINT m_Pos;
	SIZE m_Size;
};

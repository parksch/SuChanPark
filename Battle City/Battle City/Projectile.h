#pragma once
#include "Status.h"

class Projectile : public Object
{
public:
	Projectile();
	~Projectile();
	void Init(int width, int height);
	void SetType(TYPE type);
	void Set(POINT pos, int offsetX, int offsetY, MOVE_STATE state);
	void Update(float eTime);
	void Draw(HDC hdc);
	void RegisterCollision();
	void CollCheck();
	string CollisionCheck(RECT *rect, string tag, int code);
private:
	string m_Type;
	MOVE_STATE m_State;
	Animation *m_Projectile;
	RECT coll;
	SIZE m_Size;
	POINT m_Offset;
	POINT m_Pos;
	bool isAlive;
};


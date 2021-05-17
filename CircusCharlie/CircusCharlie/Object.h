#pragma once
#include "BitMap.h"

class Object
{
public:
	Object() {};
	virtual ~Object() {};
	virtual void Init(int width,int height,int m_Multiple) = 0;
	virtual bool Update(float eTime) = 0;
	virtual void Release() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual string CollisionCheck(RECT rect) = 0;
};

class EnvironmentObject : public Object
{
public:
	EnvironmentObject() {};
	virtual ~EnvironmentObject() {};
	virtual void Move(int focus) = 0;
};



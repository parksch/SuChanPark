#pragma once
#include "Macro.h"
#include "Interface.h"

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

class Object
{
public:
	Object() {};
	virtual ~Object() {};
	virtual void Collision_Handle(int Code) = 0;
	virtual void Update() = 0;
	bool Comp(Point pos) { return pos == Point(X, Y); }
	inline int getX() { return X; }
	inline int getY() { return Y; }
	inline int getCode() { return m_Code; }
protected:
	Interface m_MapDraw;
	string m_Icon;
	int m_Code;
	int X;
	int Y;
};



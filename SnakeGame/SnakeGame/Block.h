#pragma once
#include "Macro.h"
#include "Draw.h"

class Block
{
public:
	Block();
	~Block();
	void Create(TYPE type, Pos pos);
	void Reset();
	void Move(Pos pos);
	void Lose();
	void Collision();
	inline Pos getPos() { return m_Pos; }
	inline bool isAlive(){ return isLive; }
	bool Check(Pos pos);
private:
	bool isLive;
	TYPE m_Type;
	string m_Display[5];
	Pos m_Pos;
	Draw m_Draw;
};
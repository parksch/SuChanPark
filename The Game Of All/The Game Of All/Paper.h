#pragma once
#include "Status.h"

class Paper : public Object
{
public:
	Paper();
	~Paper();
	void Init(int width, int height);
	void Update(float efTime);
	void Draw(HDC hdc);
	string CollisionCheck(RECT *rect, string tag, int code);
	void Set();
	void SetStar(int combo);
	bool Move(MOVE_STATE move);
	void DrawOn();
public:
	bool isMove;
	bool isDraw;
	bool isStars;
	int m_Score;
	SIZE m_MapSize;
	POINT m_StartPos;
	POINT m_MovePos;
	POINT m_CurPos;
	STAR m_CurStar;
	MOVE_STATE m_CurState;
	Animation *m_Paper[4];
	Animation *m_Stars[3];
};


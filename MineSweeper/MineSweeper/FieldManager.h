#pragma once
#include "Draw.h"

struct Field
{
	Field() { State = EMPTY; isHide = true; isFlag = false; }
	FIELD_STATE State;
	bool isHide;
	bool isFlag;
};

class FieldManager
{
public:
	FieldManager();
	~FieldManager();
	void CreateMine(int size,int width,int height);
	void DrawPoint(int x,int y);
	int SetFlag(int x, int y);
	bool Check(int x, int y);
	void Reset();
private:
	Draw m_Draw;
	vector<vector<Field>> m_Objects;
};


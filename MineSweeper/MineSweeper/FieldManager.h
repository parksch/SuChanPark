#pragma once
#include "Draw.h"

struct Field
{
	Field() { Value = 0; isHide = true; isFlag = false; }
	int Value;
	bool isHide;
	bool isFlag;
};

class FieldManager
{
public:
	FieldManager();
	~FieldManager();
	void CreateMine(int size,int width,int height);
	void FocusPoint(int x, int y);
	void DrawPoint(int x,int y);
	int SetFlag(int x, int y);
	bool Check(int x, int y);
	bool FlagCheck(int mine);
	bool EmptyCheck(int mine);
	void OctagonCheck(int x, int y);
	void Reset();
	void Win();
private:
	Draw m_Draw;
	vector<vector<Field>> m_Objects;
	int m_Width;
	int m_Height;
};


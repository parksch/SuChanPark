#pragma once
#include <Windows.h>

class Effect
{
public:
	Effect() {};
	virtual ~Effect() {};
	virtual void Init(int width,int height) = 0;
	virtual void Update(float eTime) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual bool getOver() = 0;
	virtual Effect* Create() = 0;
	virtual void Set(POINT pos) = 0;
};


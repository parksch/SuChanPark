#pragma once
#include <Windows.h>

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void Init(HWND hWnd, int width, int height) = 0;
	virtual bool Input(float fETime) = 0;
	virtual void Update(float fETime) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Release() = 0;
};



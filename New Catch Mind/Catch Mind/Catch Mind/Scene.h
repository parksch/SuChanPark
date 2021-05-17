#pragma once
#include <Windows.h>

class Scene
{
public:
	Scene() { isLoad = false; };
	virtual ~Scene() {};
	virtual void Init(HWND hWnd, int width, int height) = 0;
	virtual bool Input(float fETime) = 0;
	virtual bool Update(float fETime) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Release() = 0;
	virtual void ObjectMessage(char type, LPVOID message) = 0;
protected:
	bool isLoad;
};


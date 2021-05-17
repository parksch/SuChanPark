#pragma once
#include "Status.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	void Init(HWND hWnd, int width, int height);
	void Recive(int code);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();
private:
	Animation *m_Menu;
};


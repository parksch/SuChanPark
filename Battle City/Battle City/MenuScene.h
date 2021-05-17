#pragma once
#include "Status.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	void Init(HWND hWnd, int width, int height);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();
private:
	float m_CursorY;
	bool isLoad;
	SIZE m_MapSize;
	Animation *m_Menu;
	Animation *m_Tank;
	Animation *m_StartBar;
	Animation *m_EditBar;
};

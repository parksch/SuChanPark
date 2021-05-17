#pragma once
#include "Status.h"

class SelectScene : public Scene
{
public:
	SelectScene();
	~SelectScene();
	void Init(HWND hWnd, int width, int height);
	void Recive(int code);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();
private:
	int m_HighScore[2];
	RECT m_ClickBox[2];
	Animation *m_Select;
};


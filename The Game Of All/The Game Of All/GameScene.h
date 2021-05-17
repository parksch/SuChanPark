#pragma once
#include "Status.h"
#include "Paper.h"
#include "Fever.h"
#include "TimeBar.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void Init(HWND hWnd, int width, int height);
	void Recive(int code);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();
	void ScoreSet();
private:
	void InputExcute(MOVE_STATE state);
	bool isOver;
	bool inputFail;
	float m_inputDelay;
	float m_ChangeDelay;
	int m_Score;
	int m_Combo;
	int m_StarCombo;
	int m_Rand;
	int	m_PaperIdx;
	GAME_STATE m_CurGame;
	Paper *m_Paper[4];
	Fever *m_Fever;
	TimeBar *m_Timebar;
	Animation *m_Back;
	Animation *m_Over;
};


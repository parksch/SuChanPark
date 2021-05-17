#pragma once
#include "Status.h"
#include "Fever.h"
#include "TimeBar.h"
#include "Bullet.h"
#include "ScoreStar.h"
#include "Plane.h"
#include "Explosion.h"

class GameSceneAir : public Scene
{
public:
	GameSceneAir();
	~GameSceneAir();
	void Init(HWND hWnd, int width, int height);
	void Recive(int code);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();
	void ScoreSet();
private:
	SIZE m_MapSize;
	Explosion *m_Explosion;
	Bullet *m_Bullet[30];
	ScoreStar *m_Stars[40];
	Animation *m_Back;
	Animation *m_Over;
	Plane *m_Plane;
	Fever *m_Fever;
	TimeBar *m_TimeBar;
	GAME_STATE m_CurState;
	float m_BulletSpawnTime;
	float m_StarSpawnTime;
	float m_ChangeDelay;
	int m_Combo;
	int m_Score;
};


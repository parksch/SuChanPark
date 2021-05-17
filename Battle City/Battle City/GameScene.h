#pragma once
#include "Status.h"
#include "Player.h"
#include "Block.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void Init(HWND hWnd, int width, int height);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();
	void ChangeScore(TYPE type);
private:
	bool Check(float eTime);
	void ScoreSave();
	void SpawnPlayer(float eTime);
	void Spawn(float eTime);
	void Set();
	void StageLoad();
	void BlockLoad();
	void DrawBack(HDC hdc, int left, int top, int right, int bottom, int r, int g, int b);
	bool isLoad;
	bool isPlyerDead;
	bool isOver;
	int m_Score;
	int m_CurStage;
	int m_Life;
	int m_EnemyLife;
	int m_CurTank;
	float m_MapChangeTimer;
	float m_SpawnTime;
	float m_Timer;
	Effect *m_SmallExplosion;
	Effect *m_Explosion;
	Tank *m_EnemyTank[20];
	Player *m_Player;
	vector<string> m_StageName;
	SIZE m_MapSize;
	Block *m_Blocks[13][13];
	Animation *m_EnemyIcon;
	Animation *m_PlayerIcon;
};

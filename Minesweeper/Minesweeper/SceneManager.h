#pragma once
#include <Windows.h>
#include <vector>
#include "Singleton.h"
#include "GameScene.h"

using namespace std;

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager() {}
	~SceneManager() {}
	void ReStart(int difficulty);
	void Init(HWND hWnd);
	void Update();
	void Relase();
	void Save();
	void Load();
	HWND getHWND() { return m_hWnd; }
private:
	int curDifficulty;
	int m_Width, m_Height;
	HWND m_hWnd;
	GameScene *m_curScene;
};
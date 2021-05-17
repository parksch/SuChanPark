#pragma once
#include <Windows.h>
#include <vector>
#include "Singleton.h"
#include "Scene.h"
using namespace std;

enum SCENE
{
	MAIN,
	GAME,
	OVER
};

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager() {}
	~SceneManager() {}
	void Init(HWND hWnd, int width, int height);
	void RegistScene(Scene* scene);
	Scene* getCurScene();
	void Update();
	void Relase();
	void LoadScene(SCENE scene);
private:
	int m_Width, m_Height;
	HWND m_hWnd;
	Scene* m_curScene;
	vector<Scene*> m_Scenes;
};
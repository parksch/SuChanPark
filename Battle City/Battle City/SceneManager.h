#pragma once
#include <map>
#include <string>
#include "Singleton.h"
#include "Scene.h"
using namespace std;

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
	void Init(HWND hWnd, int width, int height);
	void RegistScene(string name, Scene * scene);
	Scene* LoadScene(string name);
	void ChangeScene(string name);
	void Release();
	void Update();
	HWND GetHWND() { return m_hWnd; }
	Scene* getCurScene() { return m_curScene; }
private:
	HWND m_hWnd;
	SIZE m_MapSize;
	Scene* m_curScene;
	map<string, Scene*> m_Scenes;
};


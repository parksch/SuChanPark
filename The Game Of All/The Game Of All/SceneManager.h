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
	void SendToScene(int code);
	Scene* LoadScene(string name);
	void ChangeScene(string name);
	void Release();
	void Update();
	HWND GetHWND() { return m_hWnd; }
private:
	HWND m_hWnd;
	SIZE m_MapSize;
	Scene* m_curScene;
	map<string, Scene*> m_Scenes;
};


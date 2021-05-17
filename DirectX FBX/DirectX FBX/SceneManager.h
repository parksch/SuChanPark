#pragma once
#include "FBXModelLoader.h"
#include "Scene.h"
#include <map>
#include <string>

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
	bool Init(LPDIRECT3DDEVICE9 device, HWND hWnd);
	void RegistScene(std::string name, Scene * scene);
	Scene* LoadScene(std::string name);
	void ChangeScene(std::string name);
	void Release();
	void Update();
	HWND GetHWND() { return m_hWnd; }
	Scene* getCurScene() { return m_curScene; }
private:
	LPDIRECT3DDEVICE9 m_Device;
	HWND m_hWnd;
	SIZE m_MapSize;
	Scene* m_curScene;
	std::map<std::string, Scene*> m_Scenes;
};


#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <map>

class SceneManager : public Singleton<SceneManager>
{
public:
	void Init(HWND hWnd, HINSTANCE hInstance, int width, int height);
	void RegistScene(std::string name, Scene *scene);
	void SendObjectMessage(char type, LPVOID message);
	void ChangeScene(std::string str);
	void Update();
	void Release();
	HINSTANCE get_hInst() { return m_hInstance; }
	HWND  get_HWND() { return m_hWnd; }
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	SIZE m_MapSize;
	Scene* m_curScene;
	std::map<std::string, Scene*> m_Scenes;
};


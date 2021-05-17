#include "ServerManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

SceneManager* SceneManager::m_pThis = nullptr;

void SceneManager::RegistScene(std::string name, Scene * scene)
{
	m_Scenes.insert(make_pair(name, scene));
}

void SceneManager::Init(HWND hWnd, HINSTANCE hInstance, int width, int height)
{
	m_hInstance = hInstance;
	m_hWnd = hWnd;
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	if (!ServerManager::GetInstance()->Init())
	{
		PostQuitMessage(0);
		return;
	}

	TimeManager::GetInstance()->Init();

	HDC hdc = GetDC(m_hWnd);
	ResourceManager::GetInstance()->initBitmap(hdc);
	ResourceManager::GetInstance()->initBack(hdc, m_MapSize.cx, m_MapSize.cy);
	ReleaseDC(m_hWnd, hdc);

	m_curScene = m_Scenes["Menu"];
	m_curScene->Init(m_hWnd, width, height);


}

void SceneManager::Update()
{
	if (!TimeManager::GetInstance()->Update())
		return;

	if (!ServerManager::GetInstance()->isConnect())
	{
		PostQuitMessage(0);
		return;
	}

	InputManager::GetInstance()->Update();

	if (m_curScene->Input(TimeManager::GetInstance()->GetElipseTime()))
		return;

	if (m_curScene->Update(TimeManager::GetInstance()->GetElipseTime()))
		return;

	HDC hdc = GetDC(m_hWnd);
	ResourceManager::GetInstance()->DrawBack(hdc);
	m_curScene->Draw(ResourceManager::GetInstance()->GetBackDC());
	ReleaseDC(m_hWnd, hdc);
}

void SceneManager::Release()
{
	for (auto iter = m_Scenes.begin(); iter != m_Scenes.end(); iter++)
	{
		auto del = (*iter).second;
		del->Release();
		delete del;
	}
}

void SceneManager::SendObjectMessage(char type, LPVOID message)
{
	m_curScene->ObjectMessage(type, message);
}

void SceneManager::ChangeScene(std::string str)
{
	Scene* scene = m_Scenes.find(str)->second;;
	m_curScene->Release();
	m_curScene = scene;
	m_curScene->Init(m_hWnd, m_MapSize.cx, m_MapSize.cy);
}


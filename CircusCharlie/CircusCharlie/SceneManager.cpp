#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "InputManager.h"
#include "MapManager.h"
#include "CollisionManager.h"

void SceneManager::Init(HWND hWnd, int width, int height)
{
	m_hWnd = hWnd;
	m_Width = width;
	m_Height = height;

	TimeManager::GetInstance()->Init();

	HDC hdc = GetDC(hWnd);
	ResourceManager::GetInstance()->initBitmap(hdc);
	ResourceManager::GetInstance()->initBack(hdc, width, height);
	UIManager::GetInstance()->Init(hWnd, width, height);
	ReleaseDC(hWnd, hdc);
	m_curScene = m_Scenes[0];
	m_curScene->Init(hWnd,width,height);
}

void SceneManager::RegistScene(Scene * scene)
{
	m_Scenes.push_back(scene);
}

Scene * SceneManager::getCurScene()
{
	return m_curScene;
}

void SceneManager::Update()
{
	if (!TimeManager::GetInstance()->Update())
		return;

	InputManager::GetInstance()->Update();
	UIManager::GetInstance()->Update(TimeManager::GetInstance()->GetElipseTime());

	if (m_curScene->Input(TimeManager::GetInstance()->GetElipseTime()))
		return;

	m_curScene->Update(TimeManager::GetInstance()->GetElipseTime());

	HDC hdc = GetDC(m_hWnd);
	ResourceManager::GetInstance()->DrawBack(hdc);
	m_curScene->Draw(ResourceManager::GetInstance()->GetBackDC());
	UIManager::GetInstance()->Draw(ResourceManager::GetInstance()->GetBackDC());
	ReleaseDC(m_hWnd, hdc);

}

void SceneManager::Relase()
{
	for (int i = 0; i < m_Scenes.size(); i++)
	{
		m_Scenes[i]->Release();
		delete m_Scenes[i];
	}

	vector<Scene*>().swap(m_Scenes);
}

void SceneManager::LoadScene(SCENE scene)
{
	CollisionManager::GetInstance()->Clear();
	m_curScene = m_Scenes[(int)scene];
	m_curScene->Init(m_hWnd, m_Width, m_Height);
}

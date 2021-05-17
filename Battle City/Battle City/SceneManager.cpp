#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "EffectManager.h"

SceneManager* SceneManager::m_pThis = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(HWND hWnd, int width, int height)
{
	m_hWnd = hWnd;
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	TimeManager::GetInstance()->Init();

	HDC hdc = GetDC(hWnd);
	ResourceManager::GetInstance()->initBitmap(hdc);
	ResourceManager::GetInstance()->initBack(hdc, m_MapSize.cx, m_MapSize.cy);
	ReleaseDC(hWnd, hdc);

	m_curScene = LoadScene("Menu");
	m_curScene->Init(m_hWnd, width, height);
}

void SceneManager::RegistScene(string name, Scene * scene)
{
	m_Scenes.insert(make_pair(name, scene));
}

Scene * SceneManager::LoadScene(string name)
{
	return m_Scenes.find(name)->second;
}

void SceneManager::ChangeScene(string name)
{
	Scene* scene = LoadScene(name);
	m_curScene->Release();
	m_curScene = scene;
	m_curScene->Init(m_hWnd, m_MapSize.cx, m_MapSize.cy);
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

void SceneManager::Update()
{
	if (!TimeManager::GetInstance()->Update())
		return;

	InputManager::GetInstance()->Update();

	if (m_curScene->Input(TimeManager::GetInstance()->GetElipseTime()))
		return;

	EffectManager::GetInstance()->Update(TimeManager::GetInstance()->GetElipseTime());
	m_curScene->Update(TimeManager::GetInstance()->GetElipseTime());

	HDC hdc = GetDC(m_hWnd);
	ResourceManager::GetInstance()->DrawBack(hdc);
	m_curScene->Draw(ResourceManager::GetInstance()->GetBackDC());
	ReleaseDC(m_hWnd, hdc);

	EffectManager::GetInstance()->Check();
}

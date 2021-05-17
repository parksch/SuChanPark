#include "SceneManager.h"
#include "TimeManager.h"
#include "InputManager.h"

SceneManager* SceneManager::m_pThis = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::Init(LPDIRECT3DDEVICE9 device, HWND hWnd)
{
	m_Device = device;
	m_hWnd = hWnd;

	if (!FBXModelLoader::GetInstance()->Init(device, hWnd))
		return false;

	m_curScene = LoadScene("GameScene");
	m_curScene->Init(m_Device, m_hWnd);

	return true;
}

void SceneManager::Update()
{

	InputManager::GetInstance()->Update();

	if (!m_curScene->Input(TimeManager::GetInstance()->GetElipseTime()))
		return;

	if (!m_curScene->Update(TimeManager::GetInstance()->GetElipseTime()))
		return;

	if (!TimeManager::GetInstance()->Update())
		return;

	m_curScene->Render();

}

void SceneManager::RegistScene(std::string name, Scene * scene)
{
	m_Scenes.insert(make_pair(name, scene));
}

Scene * SceneManager::LoadScene(std::string name)
{
	return m_Scenes.find(name)->second;
}

void SceneManager::ChangeScene(std::string name)
{
	Scene* scene = LoadScene(name);
	m_curScene->Release();
	m_curScene = scene;
	m_curScene->Init(m_Device,m_hWnd);
}

void SceneManager::Release()
{
	FBXModelLoader::GetInstance()->Release();

	for (auto iter = m_Scenes.begin(); iter != m_Scenes.end(); iter++)
	{
		auto del = (*iter).second;
		del->Release();
		delete del;
	}
}

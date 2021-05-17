#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "InputManager.h"
#include <algorithm>

void SceneManager::ReStart(int difficulty)
{
	m_curScene->Init(m_hWnd,difficulty);
}

void SceneManager::Init(HWND hWnd)
{
	m_curScene = new GameScene();

	m_hWnd = hWnd;
	TimeManager::GetInstance()->Init();

	HDC hdc = GetDC(hWnd);
	ResourceManager::GetInstance()->initBitmap(hdc);
	ReleaseDC(hWnd, hdc);

	m_curScene->Init(hWnd);
}

void SceneManager::Update()
{
	if (!TimeManager::GetInstance()->Update())
		return;

	InputManager::GetInstance()->Update();
	UIManager::GetInstance()->Update(TimeManager::GetInstance()->GetElipseTime());

	if (m_curScene->Input(TimeManager::GetInstance()->GetElipseTime()))
	{
		HDC hdc = GetDC(m_hWnd);
		m_curScene->Draw(ResourceManager::GetInstance()->GetBackDC());
		UIManager::GetInstance()->Draw(ResourceManager::GetInstance()->GetBackDC());
		ResourceManager::GetInstance()->DrawBack(hdc);
		Save();
		return;
	}

	HDC hdc = GetDC(m_hWnd);
	ResourceManager::GetInstance()->DrawBack(hdc);
	m_curScene->Draw(ResourceManager::GetInstance()->GetBackDC());
	UIManager::GetInstance()->Draw(ResourceManager::GetInstance()->GetBackDC());
	ReleaseDC(m_hWnd, hdc);

}

void SceneManager::Relase()
{
	delete m_curScene;
}

void SceneManager::Save()
{
	vector<string> str;
	vector<int> score;
	int time = UIManager::GetInstance()->getTime();
	string copy;
	string save;
	DWORD dwReadWrite;
	HANDLE file = CreateFile(TEXT("Score.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	char line[1024];

	ReadFile(file, &line, 1024, &dwReadWrite, NULL);
	CloseHandle(file);

	line[dwReadWrite] = '\0';
	copy = line;

	while (copy != "")
	{
		str.push_back(copy.substr(0, copy.find("\n")));
		copy = copy.substr(copy.find("\n") + 1);
	}

	for (int i = 0; i < str.size(); i++)
	{
		score.push_back(stoi(str[i]));
	}

	score.push_back(time);
	sort(score.begin(), score.end());

	for (int i = 0; i < score.size(); i++)
	{
		copy += to_string(i + 1) + ". ";
		copy += to_string(score[i]);
		copy += '\n';
	}

	MessageBox(m_hWnd, TEXT(copy.c_str()), TEXT("Score"), MB_OK);

	for (int i = 0; i < score.size(); i++)
	{
		save += to_string(score[i]);
		save += '\n';
	}

	file = CreateFile(TEXT("Score.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, save.c_str(), save.size(), &dwReadWrite, NULL);
	CloseHandle(file);
}

void SceneManager::Load()
{
	vector<string> str;
	vector<int> score;
	string copy;
	DWORD dwRead;
	HANDLE file = CreateFile(TEXT("Score.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	char line[1024];

	ReadFile(file, &line, 1024, &dwRead, NULL);
	line[dwRead] = '\0';
	copy = line;

	while (copy != "")
	{
		str.push_back(copy.substr(0, copy.find("\n")));
		copy = copy.substr(copy.find("\n") + 1);
	}

	for (int i = 0; i < str.size(); i++)
	{
		score.push_back(stoi(str[i]));
	}

	sort(score.begin(), score.end());

	for (int i = 0; i < score.size(); i++)
	{
		copy += to_string(i + 1) + ". ";
		copy += to_string(score[i]);
		copy += '\n';
	}

	CloseHandle(file);
	MessageBox(m_hWnd, TEXT(copy.c_str()), TEXT("Score"), MB_OK);
}


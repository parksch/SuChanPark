#include "SelectScene.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Init(HWND hWnd, int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_HighScore[0] = 0;
	m_HighScore[1] = 0;

	m_ClickBox[0].left = m_MapSize.cx * 0.77f;
	m_ClickBox[0].top = m_MapSize.cy * 0.26f;
	m_ClickBox[0].right = m_MapSize.cx * 0.9f;
	m_ClickBox[0].bottom = m_MapSize.cy * 0.34f;

	m_ClickBox[1].left = m_MapSize.cx * 0.77f;
	m_ClickBox[1].top = m_MapSize.cy * 0.38;
	m_ClickBox[1].right = m_MapSize.cx * 0.9f;
	m_ClickBox[1].bottom = m_MapSize.cy * 0.47f;

	m_Select = new Animation();
	m_Select->Push(ResourceManager::GetInstance()->GetBitmap("GameSelect.bmp"), m_MapSize.cx , m_MapSize.cy );

	InputManager::GetInstance()->RegistKeyCode(MK_LBUTTON);

	HANDLE hFile = CreateFile(TEXT("PaperScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	char chr[1024];
	string str;

	ReadFile(hFile, chr, 1024, &dwRead, NULL);
	CloseHandle(hFile);

	chr[dwRead] = '\0';
	str = chr;
	m_HighScore[0] = atoi(str.c_str());

	hFile = CreateFile(TEXT("AirScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, chr, 1024, &dwRead, NULL);
	CloseHandle(hFile);

	chr[dwRead] = '\0';
	str = chr;
	m_HighScore[1] = atoi(str.c_str());

	isLoad = true;
}

void SelectScene::Recive(int code)
{
}

bool SelectScene::Input(float fETime)
{
	if (InputManager::GetInstance()->isKeyDown(MK_LBUTTON))
	{
		if (PtInRect(&m_ClickBox[0],InputManager::GetInstance()->GetMousePos()))
		{
			SceneManager::GetInstance()->ChangeScene("Game_Paper");
			return true;
		}

		if (PtInRect(&m_ClickBox[1], InputManager::GetInstance()->GetMousePos()))
		{
			SceneManager::GetInstance()->ChangeScene("Game_Air");
			return true;
		}
	}

	return false;
}

void SelectScene::Update(float fETime)
{
}

void SelectScene::Draw(HDC hdc)
{
	m_Select->Draw(hdc);
	TextOut(hdc, m_MapSize.cx *0.27f, m_MapSize.cy * 0.3f,
		to_string(m_HighScore[0]).c_str(), strlen(to_string(m_HighScore[0]).c_str()));
	TextOut(hdc, m_MapSize.cx *0.27f, m_MapSize.cy * 0.43f,
		to_string(m_HighScore[1]).c_str(), strlen(to_string(m_HighScore[0]).c_str()));

}

void SelectScene::Release()
{
	if (isLoad)
	{
		delete m_Select;
		InputManager::GetInstance()->Clear();
		isLoad = false;
	}
}

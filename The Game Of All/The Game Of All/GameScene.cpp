#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(HWND hWnd, int width, int height)
{
	m_CurGame = NOMAL;

	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Score = 0;
	m_Combo = 0;
	m_Rand = 0;
	m_PaperIdx = 0;
	m_StarCombo = 0;
	m_ChangeDelay = 0;

	m_Back = new Animation();
	m_Back->Push(ResourceManager::GetInstance()->GetBitmap("ColoredPaperBack.bmp"), m_MapSize.cx, m_MapSize.cy);

	m_Over = new Animation();
	m_Over->Push(ResourceManager::GetInstance()->GetBitmap("TimeOver.bmp"));

	m_Timebar = new TimeBar();
	m_Timebar->Init(m_MapSize.cx, m_MapSize.cy);

	m_Fever = new Fever();
	m_Fever->Init(m_MapSize.cx, m_MapSize.cy);
	m_Fever->Set(1);

	for (int i = 0; i < 4; i++)
	{
		m_Paper[i] = new Paper();
		m_Paper[i]->Init(width, height);
		m_Paper[i]->Set();
	}

	m_Paper[0]->DrawOn();

	InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	InputManager::GetInstance()->RegistKeyCode(VK_UP);
	InputManager::GetInstance()->RegistKeyCode(VK_DOWN);

	inputFail = false;
	m_inputDelay = 0;
	isLoad = true;
}

void GameScene::Recive(int code)
{
	switch (code)
	{
	case NOMAL:
		m_CurGame = NOMAL;
		break;
	case FEVER:
		m_CurGame = FEVER;
		break;
	case SUPER_FEVER:
		m_CurGame = SUPER_FEVER;
		break;
	case OVER:
		m_CurGame = OVER;
		break;
	default:
		break;
	}
}

bool GameScene::Input(float fETime)
{
	if (m_CurGame == OVER)
	{
		return false;
	}

	if (inputFail)
	{
		return false;
	}

	if (InputManager::GetInstance()->isKeyDown(VK_LEFT))
	{
		InputExcute(LEFT);

		return false;
	}

	if (InputManager::GetInstance()->isKeyDown(VK_RIGHT))
	{
		InputExcute(RIGHT);
		

		return false;
	}

	if (InputManager::GetInstance()->isKeyDown(VK_UP))
	{
		InputExcute(UP);

		return false;
	}

	if (InputManager::GetInstance()->isKeyDown(VK_DOWN))
	{
		InputExcute(DOWN);

		return false;
	}

	return false;
}

void GameScene::Update(float fETime)
{

	if (m_CurGame == OVER)
	{
		m_ChangeDelay += fETime;

		if (m_ChangeDelay >= 5.0f)
		{
			ScoreSet();
			SceneManager::GetInstance()->ChangeScene("Select");
		}

		return;
	}


	if (inputFail)
	{
		m_inputDelay += fETime;

		if (m_inputDelay > 0.5f)
		{
			m_inputDelay = 0;
			inputFail = false;
		}
	}

	m_Fever->Update(fETime);
	m_Timebar->Update(fETime);

	for (int i = 0; i < 4; i++)
	{
		m_Paper[i]->Update(fETime);
	}
}

void GameScene::Draw(HDC hdc)
{
	m_Back->Draw(hdc);
	for (int i = 3; i > -1; i--)
	{
		m_Paper[i]->Draw(hdc);
	}

	m_Fever->Draw(hdc);
	m_Timebar->Draw(hdc);
	TextOut(hdc, m_MapSize.cx *0.4f, m_MapSize.cy *0.03f, TEXT(to_string(m_Score).c_str()), strlen(to_string(m_Score).c_str()));

	if (m_CurGame == OVER)
	{
		m_Over->Draw(hdc, m_MapSize.cx *0.25f, m_MapSize.cy *0.4f);
	}
}

void GameScene::Release()
{
	if (isLoad)
	{
		for (int i = 0; i < 4; i++)
		{
			delete m_Paper[i];
		}

		delete m_Over;
		delete m_Timebar;
		delete m_Fever;
		delete m_Back;

		InputManager::GetInstance()->Clear();

		isLoad = false;
	}
}

void GameScene::ScoreSet()
{
	HANDLE hFile = CreateFile(TEXT("PaperScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	char chr[1024];
	string str;
	int score;

	ReadFile(hFile, chr, 1024, &dwRead, NULL);
	CloseHandle(hFile);

	chr[dwRead] = '\0';
	str = chr;
	score = atoi(str.c_str());
	
	if (m_Score > score)
	{
		score = m_Score;
	}

	str = to_string(score);

	hFile = CreateFile(TEXT("PaperScore.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, str.c_str(), str.size(), &dwRead, NULL);
	CloseHandle(hFile);
}

void GameScene::InputExcute(MOVE_STATE state)
{
	if (m_Paper[m_PaperIdx]->Move(state))
	{
		m_Combo += 1;
		m_Score += 90;
		m_Paper[(m_PaperIdx + 1) % 4]->DrawOn();
		m_PaperIdx = (m_PaperIdx + 1) % 4;
		m_Fever->Up();

	switch (m_CurGame)
	{
	case NOMAL:
		if (m_Combo % 5 == 0)
		{
			m_StarCombo += 1;
			m_Score += m_StarCombo * 100;
			m_Paper[(m_PaperIdx + 1) % 4]->SetStar(m_StarCombo);
		}
		break;
	case FEVER:
	case SUPER_FEVER:
		m_StarCombo += 1;
		m_Score += m_StarCombo * 100;
		m_Paper[(m_PaperIdx + 1) % 4]->SetStar(m_StarCombo);
		break;
	default:
		break;
	}

	}
	else
	{
		inputFail = true;

		switch (m_CurGame)
		{
		case NOMAL:
			m_Fever->Down();
			m_Combo = 0;
			m_StarCombo = 0;
			m_Paper[(m_PaperIdx)]->SetStar(m_Combo);
			m_Paper[(m_PaperIdx + 1) % 4]->SetStar(m_Combo);
			break;
		case FEVER:
			m_Fever->Down();
		case SUPER_FEVER:
			m_Combo = 1;
			m_StarCombo = 1;
			m_Paper[(m_PaperIdx)]->SetStar(m_Combo);
			break;
		default:
			break;
		}
	}

}

#include "GameSceneAir.h"

GameSceneAir::GameSceneAir()
{
}

GameSceneAir::~GameSceneAir()
{
}

void GameSceneAir::Init(HWND hWnd, int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_TimeBar = new TimeBar();
	m_TimeBar->Init(width, height);

	m_Fever = new Fever();
	m_Fever->Init(width, height);

	m_Back = new Animation();
	m_Back->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameBack.bmp"),m_MapSize.cx,m_MapSize.cy);

	m_Plane = new Plane();
	m_Plane->Init(width, height);

	m_Over = new Animation();
	m_Over->Push(ResourceManager::GetInstance()->GetBitmap("TimeOver.bmp"));

	m_Explosion = new Explosion;
	m_Explosion->Init(width, height);

	EffectManager::GetInstance()->Clear();
	EffectManager::GetInstance()->Register(m_Explosion, "Explosion");

	for (int i = 0; i < 30; i++)
	{
		m_Bullet[i] = new Bullet();
		m_Bullet[i]->Init(width, height);
	}

	for (int i = 0; i < 40; i++)
	{
		m_Stars[i] = new ScoreStar();
		m_Stars[i]->Init(width, height);
	}

	m_BulletSpawnTime = 0;
	m_StarSpawnTime = 0;
	m_Combo = 1;
	m_Score = 0;
	m_ChangeDelay = 0;
	m_CurState = NOMAL;

	isLoad = true;
}

void GameSceneAir::Recive(int code)
{
	switch (code)
	{
	case NOMAL:
		m_CurState = NOMAL;
		break;
	case FEVER:
		m_CurState = FEVER;
		break;
	case SUPER_FEVER:
		m_CurState = SUPER_FEVER;
		break;
	case OVER:
		m_CurState = OVER;
		break;
	case SCORE_UP:
		m_Score += m_Combo * 100;
		m_Combo += 1;
		m_Fever->Up();

		for (int i = 0; i < 40; i++)
		{
			m_Stars[i]->SetCombo(m_Combo);
		}
		
		break;
	case SCORE_DOWN:
		m_Combo = 1;
		m_Fever->Down();

		for (int i = 0; i < 40; i++)
		{
			m_Stars[i]->SetCombo(m_Combo);
		}
		break;
	default:
		break;
	}
}

bool GameSceneAir::Input(float fETime)
{
	return false;
}

void GameSceneAir::Update(float fETime)
{
	if (m_CurState == OVER)
	{
		m_ChangeDelay += fETime;

		if (m_ChangeDelay >= 5.0f)
		{
			ScoreSet();
			SceneManager::GetInstance()->ChangeScene("Select");
		}

		return;
	}

	m_BulletSpawnTime += fETime;
	m_StarSpawnTime += fETime;

	if (m_BulletSpawnTime > 0.5f)
	{
		m_BulletSpawnTime = 0;
		m_Score += 3;
		for (int i = 0; i < 30; i++)
		{
			if (m_Bullet[i]->Set())
			{
				break;
			}
		}
	}

	if (m_StarSpawnTime > 2.0f)
	{
		m_StarSpawnTime = 0;
		int count = 0;
		switch (m_CurState)
		{
		case NOMAL:
			for (int i = 0; i < 40; i++)
			{
				if (m_Stars[i]->Set(m_Combo))
				{
					break;
				}
			}
			break;
		case FEVER:
		case SUPER_FEVER:
			for (int i = 0; i < 40; i++)
			{
				if (m_Stars[i]->Set(m_Combo))
				{
					count++;
					if (count > 5)
					{
						break;
					}
				}
			}
			break;
		default:
			break;
		}

	}

	for (int i = 0; i < 30; i++)
	{
		m_Bullet[i]->Update(fETime);
	}

	for (int i = 0; i < 40; i++)
	{
		m_Stars[i]->Update(fETime);
	}

	m_Fever->Update(fETime);
	m_Plane->Update(fETime);
	m_TimeBar->Update(fETime);
}

void GameSceneAir::Draw(HDC hdc)
{

	m_Back->Draw(hdc);
	m_Fever->Draw(hdc);

	for (int i = 0; i < 40; i++)
	{
		m_Stars[i]->Draw(hdc);
	}

	for (int i = 0; i < 30; i++)
	{
		m_Bullet[i]->Draw(hdc);
	}

	TextOut(hdc, m_MapSize.cx *0.4f, m_MapSize.cy *0.03f, TEXT(to_string(m_Score).c_str()), strlen(to_string(m_Score).c_str()));
	m_Plane->Draw(hdc);
	EffectManager::GetInstance()->Draw(hdc);
	m_TimeBar->Draw(hdc);

	if (m_CurState == OVER)
	{
		m_Over->Draw(hdc, m_MapSize.cx *0.25f, m_MapSize.cy *0.4f);
	}
}

void GameSceneAir::Release()
{
	if (isLoad)
	{
		delete m_TimeBar;
		delete m_Fever;
		delete m_Back;
		delete m_Plane;
		delete m_Explosion;
		delete m_Over;

		for (int i = 0; i < 30; i++)
		{
			delete m_Bullet[i];
		}

		for (int i = 0; i < 40; i++)
		{
			delete m_Stars[i];
		}

		EffectManager::GetInstance()->Clear();
		isLoad = false;
	}
}

void GameSceneAir::ScoreSet()
{
	HANDLE hFile = CreateFile(TEXT("AirScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	char chr[1024];
	string str;
	int score;

	ReadFile(hFile, chr, 1024, &dwRead, NULL);
	chr[dwRead] = '\0';
	str = chr;
	score = atoi(str.c_str());

	if (m_Score > score)
	{
		score = m_Score;
	}

	str = to_string(score);

	CloseHandle(hFile);
	hFile = CreateFile(TEXT("AirScore.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, str.c_str(), str.size(), &dwRead, NULL);

	CloseHandle(hFile);
}

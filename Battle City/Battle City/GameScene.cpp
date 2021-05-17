#include "GameScene.h"
#include <algorithm>
#include <functional>
#include "SmallExplosion.h"
#include "Explosion.h"

GameScene::GameScene()
{
	isLoad = false;
}

GameScene::~GameScene()
{

}

void GameScene::Init(HWND hWnd, int width, int height)
{

	m_MapChangeTimer = 0;
	m_MapSize.cx = width;
	m_MapSize.cy = height;
	m_Score = 0;
	m_CurStage = 0;
	m_Life = 1;
	isPlyerDead = false;

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			m_Blocks[y][x] = new Block();
			m_Blocks[y][x]->Init(m_MapSize.cx, m_MapSize.cy, x, y);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		m_EnemyTank[i] = new Tank();
		m_EnemyTank[i]->Init(m_MapSize.cx, m_MapSize.cy,ENEMY,i);
		m_EnemyTank[i]->InitAni();
	}

	m_Player = new Player();
	m_Player->Init(m_MapSize.cx, m_MapSize.cy,PLAYER,-1);
	m_Player->InitAni();

	StageLoad();
	Set();

	m_SmallExplosion = new SmallExplosion();
	m_SmallExplosion->Init(m_MapSize.cx, m_MapSize.cy);

	m_Explosion = new Explosion();
	m_Explosion->Init(m_MapSize.cx, m_MapSize.cy);

	m_EnemyIcon = new Animation();
	m_EnemyIcon->Push(ResourceManager::GetInstance()->GetBitmap("enemy_icon.bmp"),  ((m_MapSize.cx * 0.8f) / 13) * 0.5f, (m_MapSize.cy / 13) * 0.5f);

	m_PlayerIcon = new Animation();
	m_PlayerIcon->Push(ResourceManager::GetInstance()->GetBitmap("player_icon.bmp"), ((m_MapSize.cx * 0.8f) / 13) * 0.5f, (m_MapSize.cy / 13) * 0.5f);

	EffectManager::GetInstance()->Register(m_SmallExplosion, "SmallExplosion");
	EffectManager::GetInstance()->Register(m_Explosion, "Explosion");

	InputManager::GetInstance()->RegistKeyCode(VK_UP);
	InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	InputManager::GetInstance()->RegistKeyCode(VK_SPACE);

	isOver = false;
	isLoad = true;
}

bool GameScene::Input(float fETime)
{
	m_Player->Input();
	return false;
}

void GameScene::Update(float fETime)
{
	if (Check(fETime))
	{
		return;
	}
	Spawn(fETime);
	SpawnPlayer(fETime);
	for (int i = 0; i < 20; i++)
	{
		m_EnemyTank[i]->Update(fETime);
	}
	m_Player->Update(fETime);
}

void GameScene::Draw(HDC hdc)
{
	DrawBack(hdc, 0, 0, m_MapSize.cx*0.8f, m_MapSize.cy, 0, 0, 0);
	DrawBack(hdc, m_MapSize.cx*0.8f, 0, m_MapSize.cx, m_MapSize.cy, 128, 128, 128);

	for (int i = 0; i < 20; i++)
	{
		m_EnemyTank[i]->Draw(hdc);
	}

	m_Player->Draw(hdc);

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			m_Blocks[y][x]->Draw(hdc);
		}
	}

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			if ( (y*2) + x < m_EnemyLife)
			{
				m_EnemyIcon->Draw(hdc, 
					m_MapSize.cx * 0.8f + ((m_MapSize.cx - (m_MapSize.cx * 0.8f)) / 2) - (m_EnemyIcon->GetSize().cx * 1.1) + (x * (m_EnemyIcon->GetSize().cx * 1.1f)), 
					m_MapSize.cy * 0.1 + (y * m_EnemyIcon->GetSize().cy * 1.1f));
			}
		}
	}
	
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			if ((y * 2) + x < m_Life)
			{
				m_PlayerIcon->Draw(hdc,
					m_MapSize.cx * 0.8f + ((m_MapSize.cx - (m_MapSize.cx * 0.8f)) / 2) - (m_PlayerIcon->GetSize().cx * 1.1) + (x * (m_PlayerIcon->GetSize().cx * 1.1f)),
					m_MapSize.cy * 0.7f + (y * m_PlayerIcon->GetSize().cy * 1.1f));
			}
		}
	}

	RECT rect;
	string str = "Score : ";
	rect.left = m_MapSize.cx *0.8f;
	rect.top = m_MapSize.cy *0.05f;
	rect.right = m_MapSize.cx;
	rect.bottom = m_MapSize.cy *0.1f;
	str += to_string(m_Score) ;
	DrawText(hdc, TEXT(str.c_str()), -1, &rect, DT_CENTER);

	EffectManager::GetInstance()->Draw(hdc);

}

void GameScene::Release()
{
	if (isLoad)
	{
		delete m_EnemyIcon;
		delete m_PlayerIcon;

		for (int y = 0; y < 13; y++)
		{
			for (int x = 0; x < 13; x++)
			{
				delete m_Blocks[y][x];
			}
		}

		delete m_Explosion;
		delete m_SmallExplosion;

		for (int i = 0; i < 20; i++)
		{
			delete m_EnemyTank[i];
		}

		delete m_Player;
		EffectManager::GetInstance()->Clear();
		m_StageName.clear();
		isLoad = false;
	}
}

void GameScene::ChangeScore(TYPE type)
{
	switch (type)
	{
	case PLAYER:
		m_Life--;
		isPlyerDead = true;
		m_Timer = 0;
		break;
	case ENEMY:
		m_Score += 100;
		m_EnemyLife--;
		break;
	case FLAG:
		isOver = true;
		m_Player->GameOver();
		break;
	default:
		break;
	}

}

bool GameScene::Check(float fETime)
{
	if (isOver)
	{
		m_MapChangeTimer += fETime;
		if (m_MapChangeTimer >= SPAWN_DELAY)
		{
			isOver = false;
			m_MapChangeTimer = 0;
			MessageBox(SceneManager::GetInstance()->GetHWND(), TEXT("GAME OVER"), TEXT("GAME OVER"), MB_OK);
			ScoreSave();
			SceneManager::GetInstance()->ChangeScene("Menu");
			return true;
		}
	}

	if (m_Life == 0)
	{
		isOver = true;
	}

	if (m_EnemyLife == 0)
	{
		m_CurStage++;

		if (m_CurStage == m_StageName.size())
		{
			ScoreSave();
			SceneManager::GetInstance()->ChangeScene("Menu");
		}
		else
		{
			Set();
		}

		return true;
	}

	return false;
}

void GameScene::ScoreSave()
{
	HANDLE hFile = CreateFile(TEXT("Score.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	vector<string> scoresStr;
	vector<int> scoresInt;
	int count = 0;
	char chr[1024];
	string str;

	ReadFile(hFile, chr, 1024, &dwRead, NULL);
	CloseHandle(hFile);

	chr[dwRead] = '\0';
	str = chr;

	while (str != "")
	{
		scoresStr.push_back(str.substr(0, str.find('\n')));
		str = str.substr(str.find('\n') + 1);
		scoresInt.push_back(atoi(scoresStr[count].c_str()));
		count++;
	}

	scoresInt.push_back(m_Score);
	sort(scoresInt.begin(), scoresInt.end(),greater<int>());

	hFile = CreateFile(TEXT("Score.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	str.clear();

	for (int i = 0; i < scoresInt.size(); i++)
	{
		str += to_string(scoresInt[i]);
		str += '\n';
	}

	WriteFile(hFile, str.c_str(), str.size(), &dwRead, NULL);
	CloseHandle(hFile);
}

void GameScene::SpawnPlayer(float eTime)
{
	if (isPlyerDead)
	{
		m_Timer += eTime;
		if (m_Timer >= SPAWN_DELAY)
		{
			m_Timer = 0;
			m_Player->Set(4, 12, UP);
			isPlyerDead = false;
		}
	}
}

void GameScene::Spawn(float eTime)
{
	if (m_CurTank < 2)
	{
		m_SpawnTime += eTime;

		if (m_SpawnTime >= SPAWN_DELAY)
		{
			m_SpawnTime = 0;
			int randCount;
			RECT box;
			while (true)
			{
				randCount = rand() % 13;
				box.left = ((m_MapSize.cx *0.8f) / 13) * randCount;
				box.top = 0;
				box.right = ((m_MapSize.cx *0.8f) / 13) * randCount + ((m_MapSize.cx *0.8f) / 13);
				box.bottom = m_MapSize.cy / 13;

				if (CollisionManager::GetInstance()->CollisionCheck(&box, "Spawn", -1) == "Non")
				{
					m_EnemyTank[m_CurTank]->Set(randCount, 0,DOWN);
					m_CurTank++;
					return;
				}
			}
		}
	}
}

void GameScene::Set()
{
	CollisionManager::GetInstance()->Clear();

	m_CurTank = 0;
	m_EnemyLife = 2;
	m_SpawnTime = 0;

	BlockLoad();

}

void GameScene::StageLoad()
{
	HANDLE hFile = CreateFile(TEXT("Stage/StageList.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	char chr[1024];
	string str;

	ReadFile(hFile, chr, 1024, &dwRead, NULL);
	chr[dwRead] = '\0';
	str = chr;

	while (str != "")
	{
		m_StageName.push_back(str.substr(0, str.find('\n')));
		str = str.substr(str.find('\n') + 1);
	}

	CloseHandle(hFile);
}

void GameScene::BlockLoad()
{
	HANDLE hFile = CreateFile(TEXT(("Stage/" + m_StageName[m_CurStage]).c_str()), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	char chr[1024];
	string str;

	if (hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, chr, 1024, &dwRead, NULL);
		chr[dwRead] = '\0';
		str = chr;

		for (int y = 0; y < 13; y++)
		{
			for (int x = 0; x < 13; x++)
			{
				m_Blocks[y][x]->BlockSet(stoi(str.substr(0, str.find(" "))));
				str = str.substr(str.find(" ") + 1);
			}
			str = str.substr(str.find('\n') + 1);
		}
	}

	m_Player->Set(4, 12,UP);

	CloseHandle(hFile);
}

void GameScene::DrawBack(HDC hdc, int left, int top, int right, int bottom, int r, int g, int b)
{
	HBRUSH myBroush;
	HBRUSH oldBroush;
	myBroush = CreateSolidBrush(RGB(r, g, b));
	oldBroush = (HBRUSH)SelectObject(hdc, myBroush);
	Rectangle(hdc, left, top, right, bottom);
	SelectObject(hdc, oldBroush);
	DeleteObject(myBroush);
}

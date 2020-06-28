#include "GameManager.h"
#include "ResourceManager.h"

GameManager* GameManager::m_pThis = nullptr;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::CollisionCheck(HWND hWnd, int x, int y)
{
	string name;
	int code = ResourceManager::GetInstance()->CollisonCheck(x, y);

	switch (code)
	{
	case 0:
		name = "강아지";
		break;
	case 1:
		name = "호랑이";
		break;
	case 2:
		name = "오리";
		break;
	case 3:
		name = "코끼리";
		break;
	case 4:
		name = "소";
		break;
	case 5:
		name = "말";
		break;
	case 6:
		name = "고양이";
		break;
	case 7:
		name = "원숭이";
		break;
	case 8:
		name = "개구리";
		break;
	case 9:
		name = "닭";
		break;
	default:
		break;
	}

	if (code != -1)
	{
		MessageBox(hWnd, TEXT(name.c_str()), TEXT("동물이름"), MB_OK);
	}
}

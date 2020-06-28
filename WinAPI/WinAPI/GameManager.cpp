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
		name = "������";
		break;
	case 1:
		name = "ȣ����";
		break;
	case 2:
		name = "����";
		break;
	case 3:
		name = "�ڳ���";
		break;
	case 4:
		name = "��";
		break;
	case 5:
		name = "��";
		break;
	case 6:
		name = "�����";
		break;
	case 7:
		name = "������";
		break;
	case 8:
		name = "������";
		break;
	case 9:
		name = "��";
		break;
	default:
		break;
	}

	if (code != -1)
	{
		MessageBox(hWnd, TEXT(name.c_str()), TEXT("�����̸�"), MB_OK);
	}
}

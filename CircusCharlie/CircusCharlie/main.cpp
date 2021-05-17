#include <Windows.h>
#include <crtdbg.h>
#include <time.h>
#include "GameManager.h"
#include "SceneManager.h"
#include "MapManager.h"
#include "GameMap.h"
#include "MenuMap.h"
#include "GameScene.h"
#include "MenuScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int nCmdShow)
{
	srand((unsigned)time(NULL));
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	GameManager manager;
	SceneManager::GetInstance()->RegistScene(new MenuScene);
	SceneManager::GetInstance()->RegistScene(new GameScene);
	MapManager::GetInstance()->RegistMap(new MenuMap);
	MapManager::GetInstance()->RegistMap(new GameMap);

	return manager.Init(hInstance, 1024, 768);
}


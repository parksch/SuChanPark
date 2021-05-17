#include <Windows.h>
#include <crtdbg.h>
#include <time.h>
#include "EngineHeader.h"
#include "MenuScene.h"
#include "EditScene.h"
#include "GameScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int nCmdShow)
{
	srand((unsigned)time(NULL));
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	GameManager manager;
	SceneManager::GetInstance()->RegistScene("Menu", new MenuScene);
	SceneManager::GetInstance()->RegistScene("Edit", new EditScene);
	SceneManager::GetInstance()->RegistScene("Game", new GameScene);
	return manager.Init(hInstance, 1024, 768);
}
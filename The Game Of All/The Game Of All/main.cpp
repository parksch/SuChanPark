#include <Windows.h>
#include <crtdbg.h>
#include <time.h>
#include "EngineHeader.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameSceneAir.h"
#include "SelectScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int nCmdSho)
{
	srand((unsigned)time(NULL));
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	GameManager manager;
	SceneManager::GetInstance()->RegistScene("Menu", new MenuScene);
	SceneManager::GetInstance()->RegistScene("Game_Paper", new GameScene);
	SceneManager::GetInstance()->RegistScene("Game_Air", new GameSceneAir);
	SceneManager::GetInstance()->RegistScene("Select", new SelectScene);
	return manager.Init(hInstance, 420, 650);
}
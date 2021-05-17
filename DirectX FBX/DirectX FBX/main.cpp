#include "GameManager.h"
#include "GameScene.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, INT nCmdShow)
{
	srand((unsigned)time(NULL));
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	GameManager manager;
	manager.Init(1024, 768);

	SceneManager::GetInstance()->RegistScene("GameScene",new GameScene);

	return manager.Run();
}
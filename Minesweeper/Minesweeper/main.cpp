#include <Windows.h>
#include <crtdbg.h>
#include "EngineHeader.h"
#include "GameScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	GameManager manager;
	return manager.Init(hInstance, 260, 286);
}
#include "Manager.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	Manager manager;
	return manager.Init(hInstance, 600, 700);
}

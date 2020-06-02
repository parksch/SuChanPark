#include"PlayManager.h"

void main()
{
	system("mode con: lines=25 cols=41");
	PlayManager::GetInstance()->SetGame();
	PlayManager::GetInstance()->Display();
	PlayManager::GetInstance()->DestoryInstance();
}
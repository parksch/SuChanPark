#include "MineManager.h"

MineManager::MineManager()
{
}

MineManager::~MineManager()
{
}

void MineManager::CreateMine(int size)
{
	m_Mines.reserve(size);
}

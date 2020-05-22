#pragma once
#include "Macro.h"
#include "Mine.h"

class MineManager
{
public:
	MineManager();
	~MineManager();
	void CreateMine(int size);
private:
	vector<Mine> m_Mines;
};


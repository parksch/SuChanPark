#pragma once
#include <vector>
#include <Windows.h>
#include "Singleton.h"
#include "SceneManager.h"
#include "Map.h"
using namespace std;

class MapManager : public Singleton<MapManager>
{
public:
	MapManager();
	~MapManager();
	void RegistMap(Map* map);
	Map* GetMap(string name);
private:
	vector<Map*> game_Maps;
};


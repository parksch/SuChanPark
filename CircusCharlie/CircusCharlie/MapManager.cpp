#include "MapManager.h"

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
	for (int i = 0; i < game_Maps.size(); i++)
	{
		delete game_Maps[i];
	}

	vector<Map*>().swap(game_Maps);
}

void MapManager::RegistMap(Map * map)
{
	game_Maps.push_back(map);
}

Map * MapManager::GetMap(string name)
{
	if (name == "Menu")
	{
		return game_Maps[0];
	}

	if (name == "Game")
	{
		return game_Maps[1];
	}
}


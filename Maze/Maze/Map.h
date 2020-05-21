#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define WIDTH 15
#define HEIGHT 15 
#define WALL 1
#define EMPTY 0
#define PLAYER 2
#define GATE 3

class Map
{
public:
	Map();
	~Map() {};
	void Show();
private:
	vector<int> m_Map;
};


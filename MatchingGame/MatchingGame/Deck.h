#pragma once
#include <Windows.h>;
#include "Singleton.h"
#include "BitMap.h"
#include <string>
#include <vector>
using namespace std;

class Deck :public Singleton<Deck>
{
public:
	Deck() {};
	~Deck();
	void Init(HWND hWnd, HINSTANCE hInst);
	BitMap* Find(int index);
private:
	vector<BitMap*> cards;
};


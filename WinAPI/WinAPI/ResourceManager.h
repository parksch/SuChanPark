#pragma once
#include "Singleton.h"
#include "BitMap.h"
#include "resource.h"
#include <Vector>
using namespace std;

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();
	void Init(HDC hdc,HINSTANCE hInstance);
	void Draw(HDC hdc,int wndSizeX,int wndSizeY);
	int CollisonCheck(int x,int y);
private:
	vector<BitMap*> m_BitMaps;
};


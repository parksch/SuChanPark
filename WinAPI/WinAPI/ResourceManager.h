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
	void Init(HWND hWnd,HINSTANCE hInstance);
	void Draw(HWND hWnd,int wndSizeX,int wndSizeY);
	void CollisonCheck(HWND hWnd,int x,int y);
private:
	vector<BitMap*> m_BitMaps;
	HDC hdc;
	PAINTSTRUCT ps;
};


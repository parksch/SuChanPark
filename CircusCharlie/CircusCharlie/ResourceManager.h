#pragma once
#include <Windows.h>
#include <map>
#include <list>
#include <vector>
#include "Singleton.h"
#include "BitMap.h"
using namespace std;

struct Animation
{
	Animation()
	{
		oldTime = 0;
		offset = 0;
		delayTime = 0;
		max = 0;
	};
	~Animation()
	{
		for (int i = 0; i < images.size(); i++)
		{
			delete images[i];
		}
	}
	vector<BitMap*> images;
	float oldTime;
	int offset;
	int max;
	float delayTime;
};


class ResourceManager : public Singleton <ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();
	void initBitmap(HDC hdc);
	void initBack(HDC hdc,int width,int height);
	HDC GetBackDC();
	BitMap* CreateBack(HDC hdc, int width, int height);
	BitMap* GetBitmap(string strFileName);
	void DrawBack(HDC hdc);
private:
	BitMap *m_Back;
	map<string, BitMap*>	m_mapBitmap;
};


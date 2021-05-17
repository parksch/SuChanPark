#pragma once
#include <vector>
#include <map>
#include "SingleTon.h"
#include "BitMap.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();
	void initBitmap(HDC hdc);
	void initBack(HDC hdc, int width, int height);
	void DrawBack(HDC hdc);
	HDC GetBackDC() { return m_Back->GetMapDC(); };
	BitMap* CreateBack(HDC hdc, int width, int height);
	BitMap* GetBitmap(std::string strFileName);
private:
	BitMap *m_Back;
	std::map<std::string, BitMap*> m_BitMaps;
};


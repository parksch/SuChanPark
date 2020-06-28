#include "ResourceManager.h"

ResourceManager * ResourceManager::m_pThis = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < 10; i++)
	{
		delete m_BitMaps[i];
	}

	vector<BitMap*>().swap(m_BitMaps);
}

void ResourceManager::Init(HDC hdc, HINSTANCE hInstance)
{
	BitMap *temp;
	for (int i = IDB_BITMAP1; i < 111; i++)
	{
		temp = new BitMap();
		temp->Init(hdc, hInstance,i);
		m_BitMaps.push_back(temp);
	}
}

void ResourceManager::Draw(HDC hdc,int wndSizeX, int wndSizeY)
{
	for (int i = 0;  i < 2; i++)
	{
		for (int j = 0; j < 5 ; j++)
		{
			m_BitMaps[j + (i * 5)]->Draw(hdc,150 + (j * 200),100 + (i * 250));
		}
	}
}

int ResourceManager::CollisonCheck(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_BitMaps[i]->CollisionCheck(x,y))
		{
			return i;
		}
	}

	return -1;
}

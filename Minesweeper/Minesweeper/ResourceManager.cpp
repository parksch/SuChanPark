#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	m_Back = NULL;
}

ResourceManager::~ResourceManager()
{
	for (auto iter = m_mapBitmap.begin(); iter != m_mapBitmap.end(); iter++)
	{
		auto del = (*iter).second;
		delete del;
	}
	delete m_Back;
}

void ResourceManager::initBitmap(HDC hdc)
{
	BitMap *temp;
	temp = new BitMap();
	temp->Init(hdc, "back.bmp");
	m_mapBitmap.insert(make_pair("back.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block.bmp");
	m_mapBitmap.insert(make_pair("block.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_0.bmp");
	m_mapBitmap.insert(make_pair("block_0.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_1.bmp");
	m_mapBitmap.insert(make_pair("block_1.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_2.bmp");
	m_mapBitmap.insert(make_pair("block_2.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_3.bmp");
	m_mapBitmap.insert(make_pair("block_3.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_4.bmp");
	m_mapBitmap.insert(make_pair("block_4.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_5.bmp");
	m_mapBitmap.insert(make_pair("block_5.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_6.bmp");
	m_mapBitmap.insert(make_pair("block_6.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_7.bmp");
	m_mapBitmap.insert(make_pair("block_7.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "block_8.bmp");
	m_mapBitmap.insert(make_pair("block_8.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "flag.bmp");
	m_mapBitmap.insert(make_pair("flag.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "mine.bmp");
	m_mapBitmap.insert(make_pair("mine.bmp", temp));
}

void ResourceManager::initBack(HDC hdc, int width, int height)
{
	if (m_Back != NULL)
	{
		delete m_Back;
	}

	m_Back = new BitMap();
	m_Back->InitBack(hdc,width,height);
}

HDC ResourceManager::GetBackDC()
{
	return m_Back->GetMapDC();
}

BitMap * ResourceManager::CreateBack(HDC hdc, int width, int height)
{
	BitMap* back = new BitMap();
	back->InitBack(hdc, width, height);
	return back;
}

BitMap * ResourceManager::GetBitmap(string strFileName)
{
	return m_mapBitmap.find(strFileName)->second;
}

void ResourceManager::DrawBack(HDC hdc)
{
	m_Back->DrawBack(hdc);
}

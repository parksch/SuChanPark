#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
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
	temp->Init(hdc, "back_deco.bmp");
	m_mapBitmap.insert(make_pair("back_deco.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "back_normal.bmp");
	m_mapBitmap.insert(make_pair("back_normal.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "back_normal2.bmp");
	m_mapBitmap.insert(make_pair("back_normal2.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "cash.bmp");
	m_mapBitmap.insert(make_pair("cash.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "die.bmp");
	m_mapBitmap.insert(make_pair("die.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "end.bmp");
	m_mapBitmap.insert(make_pair("end.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy.bmp");
	m_mapBitmap.insert(make_pair("enemy.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy_1b.bmp");
	m_mapBitmap.insert(make_pair("enemy_1b.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy_1f.bmp");
	m_mapBitmap.insert(make_pair("enemy_1f.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy_b.bmp");
	m_mapBitmap.insert(make_pair("enemy_b.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy_f.bmp");
	m_mapBitmap.insert(make_pair("enemy_f.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy_l.bmp");
	m_mapBitmap.insert(make_pair("enemy_l.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy_l_b.bmp");
	m_mapBitmap.insert(make_pair("enemy_l_b.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy_l_f.bmp");
	m_mapBitmap.insert(make_pair("enemy_l_f.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "enemy1.bmp");
	m_mapBitmap.insert(make_pair("enemy1.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "front.bmp");
	m_mapBitmap.insert(make_pair("front.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "front2.bmp");
	m_mapBitmap.insert(make_pair("front2.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "icon.bmp");
	m_mapBitmap.insert(make_pair("icon.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "miter.bmp");
	m_mapBitmap.insert(make_pair("miter.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "player0.bmp");
	m_mapBitmap.insert(make_pair("player0.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "player1.bmp");
	m_mapBitmap.insert(make_pair("player1.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "player2.bmp");
	m_mapBitmap.insert(make_pair("player2.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "star.bmp");
	m_mapBitmap.insert(make_pair("star.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "star1.bmp");
	m_mapBitmap.insert(make_pair("star1.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "star2.bmp");
	m_mapBitmap.insert(make_pair("star2.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "win.bmp");
	m_mapBitmap.insert(make_pair("win.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "win2.bmp");
	m_mapBitmap.insert(make_pair("win2.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "CircusCharlie.bmp");
	m_mapBitmap.insert(make_pair("CircusCharlie.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "Bar.bmp");
	m_mapBitmap.insert(make_pair("Bar.bmp", temp));

	temp = new BitMap();
	temp->Init(hdc, "Black_Back.bmp");
	m_mapBitmap.insert(make_pair("Black_Back.bmp", temp));

}

void ResourceManager::initBack(HDC hdc, int width, int height)
{
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
	return new BitMap(*m_mapBitmap.find(strFileName)->second);
}

void ResourceManager::DrawBack(HDC hdc)
{
	m_Back->DrawBack(hdc);
}

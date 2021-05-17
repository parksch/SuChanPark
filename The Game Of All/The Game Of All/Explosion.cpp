#include "Explosion.h"

Explosion::Explosion()
{
}

Explosion::~Explosion()
{
	delete m_Explosion;
}

void Explosion::Init(int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Explosion = new Animation();
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion1.bmp"), m_MapSize.cx *0.2f, m_MapSize.cy *0.1f);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion2.bmp"), m_MapSize.cx *0.2f, m_MapSize.cy *0.1f);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion3.bmp"), m_MapSize.cx *0.2f, m_MapSize.cy *0.1f);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion3.bmp"), m_MapSize.cx *0.2f, m_MapSize.cy *0.1f);
	m_Explosion->Init(0.05f);
	isOver = false;
}

void Explosion::Update(float eTime)
{
	if (m_Explosion->getOver())
	{
		isOver = true;
	}
	if (!m_Explosion->getOver())
	{
		m_Explosion->Update(eTime);
	}
}

void Explosion::Draw(HDC hdc)
{
	m_Explosion->Draw(hdc, m_pos.x, m_pos.y);
}

bool Explosion::getOver()
{
	return isOver;
}

Effect * Explosion::Create()
{
	Explosion *sma = new Explosion();
	sma->Init(m_MapSize.cx, m_MapSize.cy);
	return sma;
}

void Explosion::Set(POINT pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

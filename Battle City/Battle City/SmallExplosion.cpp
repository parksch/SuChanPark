#include "SmallExplosion.h"

SmallExplosion::SmallExplosion()
{
}

SmallExplosion::~SmallExplosion()
{
	delete m_Explosion;
}

void SmallExplosion::Init(int width, int height)
{
	SIZE size;

	m_MapSize.cx = width;
	m_MapSize.cy = height;

	size.cx = (width * 0.8f / 13) * 0.5f;
	size.cy = (height / 13) * 0.5f;

	m_Explosion = new Animation();
	m_Explosion->Init(0.05f);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_00.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_01.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_02.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_02.bmp"), size.cx, size.cy);

}

void SmallExplosion::Update(float eTime)
{
	if (m_Explosion->getOver())
	{
		isOver = true;
	}

	if (!isOver)
	{
		m_Explosion->Update(eTime);
	}
}

void SmallExplosion::Draw(HDC hdc)
{
	if (!isOver)
	{
		m_Explosion->Draw(hdc, m_Pos.x - m_Explosion->GetSize().cx/2, m_Pos.y - m_Explosion->GetSize().cy/2);
	}
}

Effect * SmallExplosion::Create()
{
	SmallExplosion *sma = new SmallExplosion();
	sma->Init(m_MapSize.cx, m_MapSize.cy);

	return sma;
}

void SmallExplosion::Set(POINT pos)
{
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;

	m_Explosion->Reset();

	isOver = false;
}

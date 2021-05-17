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
	SIZE size;

	m_MapSize.cx = width;
	m_MapSize.cy = height;

	size.cx = (width * 0.8f / 13);
	size.cy = (height / 13);

	m_Explosion = new Animation();
	m_Explosion->Init(0.05f);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_00.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_01.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_02.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_03.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_04.bmp"), size.cx, size.cy);
	m_Explosion->Push(ResourceManager::GetInstance()->GetBitmap("explosion_04.bmp"), size.cx, size.cy);
}

void Explosion::Update(float eTime)
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

void Explosion::Draw(HDC hdc)
{
	if (!isOver)
	{
		m_Explosion->Draw(hdc, m_Pos.x , m_Pos.y );
	}
}

Effect * Explosion::Create()
{
	Explosion *sma = new Explosion();
	sma->Init(m_MapSize.cx, m_MapSize.cy);

	return sma;
}

void Explosion::Set(POINT pos)
{
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;

	m_Explosion->Reset();

	isOver = false;
}

#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	delete m_Projectile;
}

void Bullet::ImageSet()
{
	m_Projectile = new Animation;
	m_Projectile->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameBullet.bmp"), m_MapSize.cx *0.04f, m_MapSize.cy * 0.03f);
}

void Bullet::CollisionUpdate()
{
	m_CollisionBox.left = m_pos.x;
	m_CollisionBox.top = m_pos.y;
	m_CollisionBox.right = m_pos.x + m_Projectile->GetSize().cx;
	m_CollisionBox.bottom = m_pos.y + m_Projectile->GetSize().cy;

	if (m_pos.y > m_MapSize.cy *0.92f || m_pos.y < m_MapSize.cy * 0.14f ||
		m_pos.x < -m_Projectile->GetSize().cx || m_pos.x > m_MapSize.cx *0.98f
		)
	{
		isLive = false;
	}

}

bool Bullet::Set()
{
	if (isLive)
	{
		return false;
	}

	int state = rand() % 4;

	m_MoveTime = 0;

	switch (state)
	{
	case UP:
		m_pos.x = m_Projectile->GetSize().cx + rand() % (int)(m_MapSize.cx - m_Projectile->GetSize().cx * 1.5f);
		m_pos.y = m_MapSize.cy *0.15f;
		m_Offset.y = 1;
		m_Offset.x = ((rand() % (3)) - 1);
		break;
	case RIGHT:
		m_pos.y = m_MapSize.cy *0.15f + rand() % (int)(m_MapSize.cy *0.91f - m_MapSize.cy *0.15f);
		m_pos.x = m_MapSize.cx * 0.97f;
		m_Offset.x = -1;
		m_Offset.y = ((rand() % (3)) - 1);
		break;
	case DOWN:
		m_pos.y = m_MapSize.cy * 0.91f;
		m_pos.x = m_Projectile->GetSize().cx + rand() % (int)(m_MapSize.cx - m_Projectile->GetSize().cx * 1.5f);
		m_Offset.y = -1;
		m_Offset.x = ((rand() % (3)) - 1);
		break;
	case LEFT:
		m_pos.x = 0;
		m_pos.y = m_MapSize.cy *0.15f + rand() % (int)(m_MapSize.cy *0.91f - m_MapSize.cy *0.15f);
		m_Offset.x = 1;
		m_Offset.y = ((rand() % (3)) - 1);
		break;
	default:
		break;
	}


	isLive = true;
}

void Bullet::Draw(HDC hdc)
{
	if (isLive)
	{
		m_Projectile->Draw(hdc, m_pos.x,m_pos.y);
		DrawFocusRect(hdc, &m_CollisionBox);
	}
}

string Bullet::CollisionEvent()
{
	isLive = false;

	return "Bullet";
}


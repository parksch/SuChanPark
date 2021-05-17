#include "Projectile.h"

void Projectile::Init(int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Offset.x = 0;
	m_Offset.y = 0;

	CollisionManager::GetInstance()->RegisterObject(this);

	ImageSet();
	isLive = false;
}

void Projectile::Update(float efTime)
{
	if (!isLive)
	{
		return;
	}

	m_MoveTime += efTime;

	if (m_MoveTime > 0.03f)
	{
		m_pos.x += m_Offset.x;
		m_pos.y += m_Offset.y;
	}

	CollisionUpdate();

}

string Projectile::CollisionCheck(RECT * rect, string tag, int code)
{
	if (IntersectRect(&RECT(), rect, &m_CollisionBox))
	{
		if (tag == "Plane")
		{
			return CollisionEvent();
		}
	}

	return "Non";
}


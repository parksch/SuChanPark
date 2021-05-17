#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
	delete m_Projectile;
}

void Projectile::Init(int width, int height)
{
	
	m_Size.cx = width;
	m_Size.cy = height;


	m_Projectile = new Animation();
	m_Projectile->Init(0.5f);
	m_Projectile->Push(ResourceManager::GetInstance()->GetBitmap("missile_00.bmp"), ((m_Size.cx * 0.8f) / 13)*0.1f, (m_Size.cy / 13) * 0.1f);

	isAlive = false;
}

void Projectile::SetType(TYPE type)
{
	if (type == ENEMY)
	{
		m_Type = "EnemyProjectile";
	}

	if (type == PLAYER)
	{
		m_Type = "PlayerProjectile";
	}

}

void Projectile::Update(float eTime)
{
	if (isAlive)
	{

		if (
			!(
			(m_Pos.x + m_Offset.x >= m_Size.cx * 0.8f || m_Pos.x + m_Offset.x <= 0) ||
				(m_Pos.y + m_Offset.y >= m_Size.cy || m_Pos.y + m_Offset.y <= 0)
				))
		{
			m_Pos.x += m_Offset.x;
			m_Pos.y += m_Offset.y;
		}
		else
		{
			SIZE size;
			size.cx = ((m_Size.cx * 0.8f) / 13) * 0.5f;
			size.cy = (m_Size.cy / 13) * 0.5f;
			EffectManager::GetInstance()->Create("SmallExplosion", m_Pos);
			isAlive = false;
		}

		coll.left = m_Pos.x;
		coll.top = m_Pos.y;
		coll.right = m_Pos.x + ((m_Size.cx * 0.8f) / 13)*0.1f;
		coll.bottom = m_Pos.y + (m_Size.cy / 13) * 0.1f;

		CollCheck();

	}
}

void Projectile::Set(POINT pos, int offsetX, int offsetY, MOVE_STATE state)
{
	if (isAlive)
	{
		return;
	}

	m_State = state;
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_Offset.x = offsetX;
	m_Offset.y = offsetY;
	isAlive = true;
}

void Projectile::Draw(HDC hdc)
{
	if (isAlive)
	{
		m_Projectile->Draw(hdc, m_Pos.x, m_Pos.y);
	}
}

void Projectile::RegisterCollision()
{
	CollisionManager::GetInstance()->RegisterObject(this);
}

void Projectile::CollCheck()
{
	string tag;
	tag = CollisionManager::GetInstance()->CollisionCheck(&coll, m_Type, m_State);
	
	if (tag == "Non")
	{
		return;
	}

	if (tag == "Block")
	{
		isAlive = false;
		EffectManager::GetInstance()->Create("SmallExplosion", m_Pos);
		return;
	}

	if (m_Type == "EnemyProjectile" )
	{
		if (tag == "PlayerProjectile" || tag == "PlayerTank")
		{
			isAlive = false;
			EffectManager::GetInstance()->Create("SmallExplosion", m_Pos);
			return;
		}
	}

	if (m_Type == "PlayerProjectile")
	{
		if (tag == "EnemyTank" || tag == "EnemyProjectile")
		{
			isAlive = false;
			EffectManager::GetInstance()->Create("SmallExplosion", m_Pos);
			return;
		}
	}
}

string Projectile::CollisionCheck(RECT * rect, string tag, int code)
{
	if (!isAlive || tag == m_Type)
	{
		return "Non";
	}

	if (IntersectRect(&RECT(), rect, &coll))
	{

		if (m_Type == "PlayerProjectile" )
		{
			if (tag == "EnemyProjectile")
			{
				isAlive = false;
				EffectManager::GetInstance()->Create("SmallExplosion", m_Pos);
				return "PlayerProjectile";
			}
		}

		if (m_Type == "EnemyProjectile")
		{
			if (tag == "PlayerProjectile")
			{
				isAlive = false;
				EffectManager::GetInstance()->Create("SmallExplosion", m_Pos);
				return "EnemyProjectile";
			}
		}

	}

	return "Non";
}
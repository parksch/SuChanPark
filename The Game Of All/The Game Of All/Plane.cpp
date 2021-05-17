#include "Plane.h"

Plane::Plane()
{
}

Plane::~Plane()
{
	delete m_Plane;
}

void Plane::Init(int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Plane = new Animation();
	m_Plane->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameFlight.bmp"),m_MapSize.cx *0.15f,m_MapSize.cy *0.1f);

	m_Pos.x = width * 0.5f - m_Plane->GetSize().cx *0.5f;
	m_Pos.y = height * 0.5f - m_Plane->GetSize().cy *0.5f;

	m_SpawnTime = 0;
	m_InvincibleTime = 0;
	m_HideTime = 0;
	isHide = false;
	isInvincible = false;
	isLive = true;
}

void Plane::Update(float eFtime)
{
	if (!isLive)
	{
		m_SpawnTime += eFtime;
		if (m_SpawnTime > 3.0f)
		{
			m_SpawnTime = 0;
			isInvincible = true;
			Set();
		}
		return;
	}

	POINT pos = InputManager::GetInstance()->GetMousePos();

	if (pos.x < 1)
	{
		m_Pos.x = -m_Plane->GetSize().cx * 0.5f;
	}
	else if (pos.x > m_MapSize.cx)
	{
		m_Pos.x = m_MapSize.cx - m_Plane->GetSize().cx * 0.5f;
	}
	else
	{
		m_Pos.x = pos.x - m_Plane->GetSize().cx * 0.5f;
	}

	if (pos.y < m_MapSize.cy * 0.2f )
	{
		m_Pos.y = m_MapSize.cy * 0.2f - m_Plane->GetSize().cy *0.5f ;
	}
	else if (pos.y > m_MapSize.cy * 0.9f)
	{
		m_Pos.y = m_MapSize.cy * 0.9f - m_Plane->GetSize().cy * 0.5f;
	}
	else
	{
		m_Pos.y = pos.y - m_Plane->GetSize().cy * 0.5f;
	}

	m_CollisionBox.left = m_Pos.x + m_Plane->GetSize().cx *0.35f;
	m_CollisionBox.top = m_Pos.y + m_Plane->GetSize().cy *0.35f;
	m_CollisionBox.right = m_Pos.x + m_Plane->GetSize().cx *0.65f;
	m_CollisionBox.bottom = m_Pos.y + m_Plane->GetSize().cy *0.65f;

	if (isInvincible)
	{
		m_InvincibleTime += eFtime;
		m_HideTime += eFtime;
		
		if (m_HideTime > 0.1f)
		{
			m_HideTime = 0;
			isHide = !isHide;
		}

		if (m_InvincibleTime > 4.0f)
		{
			m_InvincibleTime = 0;
			m_HideTime = 0;
			isHide = false;
			isInvincible = false;
		}
	}
	
	if (CollisionManager::GetInstance()->CollisionCheck(&m_CollisionBox, "Plane", 0) == "Bullet")
	{
		if (!isInvincible)
		{
			SceneManager::GetInstance()->SendToScene(SCORE_DOWN);
			isLive = false;
			POINT center;
			center.x = m_Pos.x - m_Plane->GetSize().cx * 0.5f;
			center.y = m_Pos.y - m_Plane->GetSize().cy * 2;
			EffectManager::GetInstance()->Create("Explosion", m_Pos);
		}
	}

}

void Plane::Set()
{
	isLive = true;

	POINT pos = InputManager::GetInstance()->GetMousePos();

	if (pos.x < 1)
	{
		m_Pos.x = -m_Plane->GetSize().cx * 0.5f;
	}
	else if (pos.x > m_MapSize.cx)
	{
		m_Pos.x = m_MapSize.cx - m_Plane->GetSize().cx * 0.5f;
	}
	else
	{
		m_Pos.x = pos.x - m_Plane->GetSize().cx * 0.5f;
	}

	if (pos.y < m_MapSize.cy * 0.2f)
	{
		m_Pos.y = m_MapSize.cy * 0.2f - m_Plane->GetSize().cy *0.5f;
	}
	else if (pos.y > m_MapSize.cy * 0.9f)
	{
		m_Pos.y = m_MapSize.cy * 0.9f - m_Plane->GetSize().cy * 0.5f;
	}
	else
	{
		m_Pos.y = pos.y - m_Plane->GetSize().cy * 0.5f;
	}

}

void Plane::Draw(HDC hdc)
{
	if (isLive && !isHide)
	{
		m_Plane->Draw(hdc, m_Pos.x, m_Pos.y);
		DrawFocusRect(hdc, &m_CollisionBox);
	}
}

string Plane::CollisionCheck(RECT * rect, string tag, int code)
{
	return string();
}

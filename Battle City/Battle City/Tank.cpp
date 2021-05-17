#include "Tank.h"
#include "GameScene.h"
Tank::Tank()
{
}

Tank::~Tank()
{
	for (int i = 0; i < 4; i++)
	{
		delete	m_TankMoves[i];
	}

	delete m_Projectile;
}

void Tank::Init(int width, int height, TYPE type,int code)
{
	m_Code = code;
	m_Type = type;
	m_Pos.x = 0;
	m_Pos.y = 0;

	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Size.cx = (width *0.8f) / 13.0f;
	m_Size.cy = height / 13.0f;

	m_Projectile = new Projectile();
	m_Projectile->Init(width, height);

	for (int i = 0; i < 4; i++)
	{
		m_TankMoves[i] = new Animation();
		m_TankMoves[i]->Init(0.1f);
	}

	isAlive = false;
}

void Tank::InitAni()
{
	m_Projectile->SetType(ENEMY);

	m_TankMoves[0]->Push(ResourceManager::GetInstance()->GetBitmap("e_left_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[0]->Push(ResourceManager::GetInstance()->GetBitmap("e_left_01.bmp"), m_Size.cx, m_Size.cy);

	m_TankMoves[1]->Push(ResourceManager::GetInstance()->GetBitmap("e_right_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[1]->Push(ResourceManager::GetInstance()->GetBitmap("e_right_01.bmp"), m_Size.cx, m_Size.cy);

	m_TankMoves[2]->Push(ResourceManager::GetInstance()->GetBitmap("e_up_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[2]->Push(ResourceManager::GetInstance()->GetBitmap("e_up_01.bmp"), m_Size.cx, m_Size.cy);

	m_TankMoves[3]->Push(ResourceManager::GetInstance()->GetBitmap("e_down_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[3]->Push(ResourceManager::GetInstance()->GetBitmap("e_down_01.bmp"), m_Size.cx, m_Size.cy);

}

void Tank::Set(int x, int y, MOVE_STATE state)
{
	m_State = state;
	m_Pos.x = x * m_Size.cx;
	m_Pos.y = y * m_Size.cy;
	delay = 0;

	for (int i = 0; i < 4; i++)
	{
		m_TankMoves[i]->Reset();
	}

	m_CollisionBox.left = m_Pos.x + 4;
	m_CollisionBox.top = m_Pos.y + 7;
	m_CollisionBox.right = m_Pos.x + m_Size.cx - 6;
	m_CollisionBox.bottom = m_Pos.y + m_Size.cy - 3;
	CollisionManager::GetInstance()->RegisterObject(this);
	m_Projectile->RegisterCollision();
	isAlive = true;
}

void Tank::Draw(HDC hdc)
{
	m_Projectile->Draw(hdc);

	if (isAlive)
	{
		m_TankMoves[m_State]->Draw(hdc, m_Pos.x, m_Pos.y);
		DrawFocusRect(hdc, &m_CollisionBox);
	}
}

void Tank::StateExcute()
{
	switch (m_State)
	{
	case LEFT:
		if (m_Pos.x - 3 >= 0)
		{
			if (Move(-3, 0) == "Non")
				m_Pos.x -= 3;
			else
				StateChange();
		}
		else
		{
			m_Pos.x = 0;
			StateChange();
		}
		break;
	case RIGHT:
		if (m_Pos.x + 3 <= m_MapSize.cx * 0.8f - m_Size.cx)
		{
			if (Move(3, 0) == "Non")
				m_Pos.x += 3;
			else
				StateChange();
		}
		else
		{
			m_Pos.x = m_MapSize.cx * 0.8f - m_Size.cx;
			StateChange();
		}
		break;
	case UP:
		if (m_Pos.y - 3 >= 0)
		{
			if (Move(0, -3) == "Non")
				m_Pos.y -= 3;
			else
				StateChange();
		}
		else
		{
			m_Pos.y = 0;
			StateChange();
		}
		break;
	case DOWN:
		if (m_Pos.y + 3 <= m_MapSize.cy - m_Size.cy)
		{
			if (Move(0, 3) == "Non")
				m_Pos.y += 3;
			else
				StateChange();
		}
		else
		{
			m_Pos.y = m_MapSize.cy - m_Size.cy;
			StateChange();
		}
		break;
	default:
		break;
	}
}

void Tank::StateChange()
{
	int randIdx;
	randIdx = rand() % 4;
	m_State = (MOVE_STATE)randIdx;
}

void Tank::Shoot()
{
		switch (m_State)
		{
		case LEFT:
			m_ShootPos.x = m_Pos.x;
			m_ShootPos.y = m_Pos.y + m_Size.cy / 2;
			m_Projectile->Set(m_ShootPos, -8, 0, LEFT);
			break;
		case RIGHT:
			m_ShootPos.x = m_Pos.x + m_Size.cx;
			m_ShootPos.y = m_Pos.y + m_Size.cy / 2;
			m_Projectile->Set(m_ShootPos, 8, 0, RIGHT);
			break;
		case UP:
			m_ShootPos.x = m_Pos.x + m_Size.cx / 2;
			m_ShootPos.y = m_Pos.y - 1;
			m_Projectile->Set(m_ShootPos, 0, -8, UP);
			break;
		case DOWN:
			m_ShootPos.x = m_Pos.x + m_Size.cx / 2;
			m_ShootPos.y = m_Pos.y + m_Size.cy + 1;
			m_Projectile->Set(m_ShootPos, 0, 8, DOWN);
			break;
		default:
			break;
		}
}

void Tank::Update(float eTime)
{
	m_Projectile->Update(eTime);

	if (!isAlive)
	{
		return;
	}
	
	delay += eTime;
	if (delay > 1)
	{
		delay = 0;
		Shoot();
	}

	StateExcute();
	m_TankMoves[m_State]->Update(eTime);

	m_CollisionBox.left = m_Pos.x + 4;
	m_CollisionBox.top = m_Pos.y + 7;
	m_CollisionBox.right = m_Pos.x + m_Size.cx - 6;
	m_CollisionBox.bottom = m_Pos.y + m_Size.cy - 3;

}

string Tank::Move(int offsetX, int offsetY)
{
	RECT tempRect;
	tempRect.left = m_Pos.x + 4 + offsetX;
	tempRect.top = m_Pos.y + 7 + offsetY;
	tempRect.right = m_Pos.x + m_Size.cx - 6 + offsetX;
	tempRect.bottom = m_Pos.y + m_Size.cy - 3 + offsetY;

	if (CollisionManager::GetInstance()->CollisionCheck(&tempRect, "Tank", m_Code) == "Non")
		return "Non";

	return "Block";
}

string Tank::CollisionCheck(RECT *rect, string tag, int code)
{
	if (!isAlive || (code == m_Code && tag == "Tank") )
	{
		return "Non";
	}

	if (IntersectRect(&RECT(), rect, &m_CollisionBox))
	{
		GameScene *scene = (GameScene*)SceneManager::GetInstance()->getCurScene();

		if (tag == "Spawn")
		{
			return "Block";
		}

		if (tag == "Tank")
		{
			return "Block";
		}

		switch (m_Type)
		{
		case PLAYER:
			if (tag == "EnemyProjectile")
			{
				isAlive = false;
				EffectManager::GetInstance()->Create("Explosion", m_Pos);
				scene->ChangeScore(PLAYER);
				return "PlayerTank";
			}
			break;
		case ENEMY:
			if (tag == "PlayerProjectile")
			{
				isAlive = false;
				EffectManager::GetInstance()->Create("Explosion", m_Pos);
				scene->ChangeScore(ENEMY);
				return "EnemyTank";
			}

			break;
		default:
			break;
		}
	}

	return "Non";
}
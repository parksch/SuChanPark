#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Input()
{
	if (!isAlive)
	{
		return false;
	}

	if (InputManager::GetInstance()->isKeyDown(VK_SPACE))
	{
		Shoot();
	}

	if (InputManager::GetInstance()->isKeyPress(VK_LEFT))
	{
		isInput = true;

		if (m_Pos.x - 3 > 0)
		{
			m_MoveCode = Move(-3, 0);

			if (m_MoveCode == "Non")
			{
				m_Pos.x -= 3;
			}
		}
		else
		{
			m_Pos.x = 0;
		}
		m_State = LEFT;
		return false;
	}

	if (InputManager::GetInstance()->isKeyPress(VK_RIGHT))
	{
		isInput = true;

		if (m_Pos.x + 3 < (m_MapSize.cx - m_Size.cx) * 0.79f)
		{
			m_MoveCode = Move(3, 0);

			if (m_MoveCode == "Non")
			{
				m_Pos.x += 3;
			}
		}
		else
		{
			m_Pos.x = (m_MapSize.cx - m_Size.cx) * 0.79f;
		}

		m_State = RIGHT;
		return false;

	}

	if (InputManager::GetInstance()->isKeyPress(VK_UP))
	{
		isInput = true;

		if (m_Pos.y - 3 > 0)
		{
			m_MoveCode = Move(0, -3);

			if (m_MoveCode == "Non")
			{
				m_Pos.y -= 3;
			}
		}
		else
		{
			m_Pos.y = 0;
		}

		m_State = UP;
		return false;
	}

	if (InputManager::GetInstance()->isKeyPress(VK_DOWN))
	{
		isInput = true;

		if (m_Pos.y + 3 < m_MapSize.cy - m_Size.cy)
		{
			m_MoveCode = Move(0, 3);

			if (m_MoveCode == "Non")
			{
				m_Pos.y += 3;
			}
		}
		else
		{
			m_Pos.y = m_MapSize.cy - m_Size.cy;
		}

		m_State = DOWN;
		return false;
	}

	if (InputManager::GetInstance()->isKeyUp(VK_LEFT) ||
		InputManager::GetInstance()->isKeyUp(VK_RIGHT) ||
		InputManager::GetInstance()->isKeyUp(VK_UP) ||
		InputManager::GetInstance()->isKeyUp(VK_DOWN))
	{
		isInput = false;
	}

	return false;
}

void Player::GameOver()
{
	isAlive = false;
	EffectManager::GetInstance()->Create("Explosion", m_Pos);
}

void Player::Update(float eTime)
{
	m_Projectile->Update(eTime);

	if (isInput)
	{
		m_TankMoves[m_State]->Update(eTime);

		m_CollisionBox.left = m_Pos.x + 4;
		m_CollisionBox.top = m_Pos.y + 7;
		m_CollisionBox.right = m_Pos.x + m_Size.cx - 6;
		m_CollisionBox.bottom = m_Pos.y + m_Size.cy - 3;
	}
}

void Player::InitAni()
{
	m_Projectile->SetType(PLAYER);

	m_TankMoves[0]->Push(ResourceManager::GetInstance()->GetBitmap("tank_left_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[0]->Push(ResourceManager::GetInstance()->GetBitmap("tank_left_01.bmp"), m_Size.cx, m_Size.cy);

	m_TankMoves[1]->Push(ResourceManager::GetInstance()->GetBitmap("tank_right_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[1]->Push(ResourceManager::GetInstance()->GetBitmap("tank_right_01.bmp"), m_Size.cx, m_Size.cy);

	m_TankMoves[2]->Push(ResourceManager::GetInstance()->GetBitmap("tank_up_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[2]->Push(ResourceManager::GetInstance()->GetBitmap("tank_up_01.bmp"), m_Size.cx, m_Size.cy);

	m_TankMoves[3]->Push(ResourceManager::GetInstance()->GetBitmap("tank_down_00.bmp"), m_Size.cx, m_Size.cy);
	m_TankMoves[3]->Push(ResourceManager::GetInstance()->GetBitmap("tank_down_01.bmp"), m_Size.cx, m_Size.cy);
	isInput = false;
}

#include "Block.h"
#include "GameScene.h"
Block::Block()
{
}

Block::~Block()
{
	delete m_Block;
}

void Block::Init(int width, int height, int startX, int startY)
{
	m_Block = NULL;
	m_BlockSize.cx = (width *0.8f) / 13.0f;
	m_BlockSize.cy = height / 13.0f;
	m_Pos.x = m_BlockSize.cx * startX;
	m_Pos.y = m_BlockSize.cy * startY;
}

void Block::BlockSet(int code)
{
	string name;

	m_BlockCode = code;

	if (m_BlockCode < 10)
	{
		name = "block0" + to_string(code) + ".bmp";
	}
	else if (m_BlockCode < 15)
	{
		name = "block" + to_string(code) + ".bmp";
	}

	if (m_BlockCode < 15)
	{
		if (m_Block != NULL)
		{
			delete m_Block;
		}

		m_Block = new Animation();
		m_Block->Push(ResourceManager::GetInstance()->GetBitmap(name));
	}

	CollisionBoxSet(code);
}

void Block::Draw(HDC hdc)
{
	if (m_BlockCode < 15)
	{
		m_Block->Draw(hdc, m_Pos.x, m_Pos.y, m_ImageSize, &m_DrawBox);
		DrawFocusRect(hdc, &m_CollisionBox);
	}
}

string Block::CollisionCheck(RECT *rect, string tag, int code)
{

	if (IntersectRect(&RECT(), rect, &m_CollisionBox))
	{
		if (tag == "Spawn")
		{
			return "Block";
		}

		if (m_BlockCode == 5)
		{
			return "IceBlock";
		}
		else if (m_BlockCode == 6)
		{
			return "Non";
		}
		else if (m_BlockCode == 7)
		{
			if (tag == "Tank")
			{
				return "Block";
			}
		}
		else if (m_BlockCode == 0 || m_BlockCode == 1 || m_BlockCode == 2 || m_BlockCode == 3 || m_BlockCode == 4)
		{
 			if (tag == "PlayerProjectile" || tag == "EnemyProjectile")
			{
				switch ((MOVE_STATE)code)
				{
				case UP:

					if (m_BlockCode == 0 || m_BlockCode == 2 || m_BlockCode == 4)
					{
						m_ImageSize.cy = m_ImageSize.cy - m_BlockSize.cy / 4;
						m_CollisionBox.bottom = m_CollisionBox.bottom - m_BlockSize.cy / 4;
						m_DrawBox.bottom = m_DrawBox.bottom - m_Block->GetSize().cy / 4;
					}

					if (m_BlockCode == 1)
					{
						m_CollisionBox.bottom = m_CollisionBox.bottom - m_BlockSize.cy / 4;
						m_ImageSize.cy = m_CollisionBox.bottom - m_CollisionBox.top;
						m_DrawBox.bottom = m_DrawBox.bottom - m_Block->GetSize().cy * 0.75f;
					}

					if (m_BlockCode == 3)
					{
						m_ImageSize.cy = m_ImageSize.cy - m_BlockSize.cy / 4;
						m_CollisionBox.bottom = m_CollisionBox.bottom - m_BlockSize.cy / 4;
						m_DrawBox.bottom = m_DrawBox.bottom - m_Block->GetSize().cy / 4;

						if (m_ImageSize.cy < m_BlockSize.cy * 0.55f)
						{
							m_ImageSize.cy = 0;
							m_CollisionBox.bottom = 0;
							m_DrawBox.bottom = 0;
						}
					}

					if (m_ImageSize.cy < m_BlockSize.cy * 0.1f)
					{
						m_ImageSize.cy = 0;
						m_CollisionBox.bottom = 0;
						m_DrawBox.bottom = 0;
					}

					break;
				case DOWN:

					if (m_BlockCode == 0 || m_BlockCode == 2 || m_BlockCode == 4)
					{
						m_Pos.y = m_Pos.y + m_BlockSize.cy * 0.25f;
						m_ImageSize.cy = m_ImageSize.cy - m_BlockSize.cy / 4;
						m_CollisionBox.top = m_CollisionBox.top + m_BlockSize.cy / 4;
						m_DrawBox.top = m_DrawBox.top + m_Block->GetSize().cy / 4;
						m_DrawBox.bottom = m_DrawBox.bottom - m_Block->GetSize().cy / 4;

					}

					if (m_BlockCode == 1)
					{
						m_Pos.y = m_Pos.y + m_BlockSize.cy * 0.25f;
						m_CollisionBox.top = m_CollisionBox.top + m_BlockSize.cy / 4;
						m_ImageSize.cy = m_ImageSize.cy - m_BlockSize.cy / 4;
						m_DrawBox.top = m_DrawBox.top + m_Block->GetSize().cy / 4;
						m_DrawBox.bottom = m_DrawBox.bottom - m_Block->GetSize().cy / 4;

						if (m_ImageSize.cy < m_BlockSize.cy * 0.55f)
						{
							m_ImageSize.cy = 0;
							m_CollisionBox.bottom = 0;
							m_DrawBox.bottom = 0;
						}
					}

					if (m_BlockCode == 3)
					{
						m_Pos.y = m_Pos.y + m_BlockSize.cy * 0.75f;
						m_CollisionBox.top = m_CollisionBox.top + m_BlockSize.cy / 4;
						m_ImageSize.cy = m_ImageSize.cy - m_BlockSize.cy *0.75f;
						m_DrawBox.top = m_DrawBox.top + m_Block->GetSize().cy * 0.75f;
						m_DrawBox.bottom = m_DrawBox.bottom - m_Block->GetSize().cy *0.75f;

					}

					if (m_ImageSize.cy < m_BlockSize.cy * 0.1f)
					{
						m_ImageSize.cy = 0;
						m_CollisionBox.bottom = 0;
						m_DrawBox.bottom = 0;
					}

					break;
				case LEFT:
					if (m_BlockCode == 0 || m_BlockCode == 1 || m_BlockCode == 3)
					{
						m_CollisionBox.right = m_CollisionBox.right - m_BlockSize.cx * 0.25f;
						m_ImageSize.cx = m_ImageSize.cx - m_BlockSize.cx * 0.25f;
						m_DrawBox.right = m_DrawBox.right - m_Block->GetSize().cx * 0.25f;
					}

					if (m_BlockCode == 2)
					{
						m_CollisionBox.right = m_CollisionBox.right - m_BlockSize.cx * 0.25f;
						m_ImageSize.cx = m_ImageSize.cx - m_BlockSize.cx * 0.75f;
						m_DrawBox.right = m_DrawBox.right - m_Block->GetSize().cx * 0.75f;
					}

					if (m_BlockCode == 4)
					{
						m_CollisionBox.right = m_CollisionBox.right - m_BlockSize.cx * 0.25f;
						m_ImageSize.cx = m_ImageSize.cx - m_BlockSize.cx * 0.25f;
						m_DrawBox.right = m_DrawBox.right - m_Block->GetSize().cx * 0.25f;

						if (m_ImageSize.cx < m_BlockSize.cx * 0.55f)
						{
							m_ImageSize.cx = 0;
							m_CollisionBox.bottom = 0;
							m_DrawBox.bottom = 0;
						}
					}

					if (m_ImageSize.cx < m_BlockSize.cx * 0.2f)
					{
						m_ImageSize.cx = 0;
						m_CollisionBox.bottom = 0;
						m_DrawBox.bottom = 0;
					}

					break;
				case RIGHT:
					if (m_BlockCode == 0 || m_BlockCode == 1 || m_BlockCode == 3)
					{
						m_Pos.x = m_Pos.x + m_BlockSize.cx *0.25f;
						m_CollisionBox.left = m_CollisionBox.left + m_BlockSize.cx * 0.25f;
						m_ImageSize.cx = m_ImageSize.cx - m_BlockSize.cx * 0.25f;
						m_DrawBox.left = m_DrawBox.left + m_Block->GetSize().cx * 0.25f;
						m_DrawBox.right = m_DrawBox.right - m_Block->GetSize().cx * 0.25f;
					}

					if (m_BlockCode == 2)
					{
						m_Pos.x = m_Pos.x + m_BlockSize.cx *0.25f;
						m_CollisionBox.left = m_CollisionBox.left + m_BlockSize.cx * 0.25f;
						m_ImageSize.cx = m_ImageSize.cx - m_BlockSize.cx * 0.25f;
						m_DrawBox.left = m_DrawBox.left + m_Block->GetSize().cx * 0.25f;
						m_DrawBox.right = m_DrawBox.right - m_Block->GetSize().cx * 0.25f;

						if (m_ImageSize.cx < m_BlockSize.cx * 0.55f)
						{
							m_ImageSize.cx = 0;
							m_CollisionBox.bottom = 0;
							m_DrawBox.bottom = 0;
						}
					}

					if (m_BlockCode == 4)
					{
						m_Pos.x = m_Pos.x + m_BlockSize.cx *0.75f;
						m_CollisionBox.left = m_CollisionBox.left + m_BlockSize.cx * 0.25f;
						m_ImageSize.cx = m_ImageSize.cx - m_BlockSize.cx * 0.75f;
						m_DrawBox.left = m_DrawBox.left + m_Block->GetSize().cx * 0.75f;
						m_DrawBox.right = m_DrawBox.right - m_Block->GetSize().cx * 0.75f;
					}


					if (m_ImageSize.cx < m_BlockSize.cx * 0.2f)
					{
						m_ImageSize.cx = 0;
						m_CollisionBox.bottom = 0;
						m_DrawBox.bottom = 0;
					}

					break;
				default:
					break;
				}
				return "Block";
			}
			else if (tag == "Tank")
			{
				return "Block";
			}
		}
		else if (m_BlockCode == 8 || m_BlockCode == 9 || m_BlockCode == 10 || m_BlockCode == 11 || m_BlockCode == 12)
		{
			return "Block";
		}
		else if (m_BlockCode == 13)
		{
			if (tag == "PlayerProjectile" || tag == "EnemyProjectile")
			{
				delete m_Block;
				m_Block = new Animation();
				m_Block->Push(ResourceManager::GetInstance()->GetBitmap("block14.bmp"), m_BlockSize.cx, m_BlockSize.cy);
				GameScene *scene = (GameScene*)(SceneManager::GetInstance()->getCurScene());
				scene->ChangeScore(FLAG);
				return "Block";
			}
			else if (tag == "Tank")
			{
				return "Block";
			}
		}

	}

	return "Non";
}

void Block::CollisionBoxSet(int code)
{
	m_CollisionBox.left = 0;
	m_CollisionBox.top = 0;
	m_CollisionBox.right = 0;
	m_CollisionBox.bottom = 0;

	m_ImageSize.cx = m_BlockSize.cx;
	m_ImageSize.cy = m_BlockSize.cy;

	if (code < 15)
	{
		m_DrawBox.left = 0;
		m_DrawBox.top = 0;
		m_DrawBox.right = m_Block->GetSize().cx;
		m_DrawBox.bottom = m_Block->GetSize().cy;
	}

	if (code == 0 || code == 5 || code == 7 || code == 8 || code == 13)
	{
		m_CollisionBox.left = m_Pos.x;
		m_CollisionBox.top = m_Pos.y;
		m_CollisionBox.right = m_Pos.x + m_BlockSize.cx;
		m_CollisionBox.bottom = m_Pos.y + m_BlockSize.cy;
	}
	else if (code == 1 || code == 9)
	{
		m_CollisionBox.left = m_Pos.x;
		m_CollisionBox.top = m_Pos.y;
		m_CollisionBox.right = m_Pos.x + m_ImageSize.cx;
		m_CollisionBox.bottom = m_Pos.y + m_ImageSize.cy / 2;
	}
	else if (code == 2 || code == 10)
	{
		m_CollisionBox.left = m_Pos.x;
		m_CollisionBox.top = m_Pos.y;
		m_CollisionBox.right = m_Pos.x + m_ImageSize.cx / 2;
		m_CollisionBox.bottom = m_Pos.y + m_ImageSize.cy;
	}
	else if (code == 3 || code == 11)
	{
		m_CollisionBox.left = m_Pos.x;
		m_CollisionBox.top = m_Pos.y + m_ImageSize.cy / 2;
		m_CollisionBox.right = m_Pos.x + m_ImageSize.cx;
		m_CollisionBox.bottom = m_Pos.y + m_ImageSize.cy;
	}
	else if (code == 4 || code == 12)
	{
		m_CollisionBox.left = m_Pos.x + m_ImageSize.cx / 2;
		m_CollisionBox.top = m_Pos.y;
		m_CollisionBox.right = m_Pos.x + m_ImageSize.cx;
		m_CollisionBox.bottom = m_Pos.y + m_ImageSize.cy;
	}

	CollisionManager::GetInstance()->RegisterObject(this);
}

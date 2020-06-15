#include "Player.h"

Player::Player(int code, int x, int y)
{
	m_Code = code;
	X = x;
	Y = y;
	m_Icon = "¢¼";
	m_MapDraw.DrawPoint(m_Icon, x, y);
}

Player::~Player()
{
}

void Player::Update()
{
	if (kbhit())
	{
		char get = getch();

		if (get == UP)
		{
			Move(UP);
		}

		if (get == DOWN)
		{
			Move(DOWN);
		}

		if (get == LEFT)
		{
			Move(LEFT);
		}

		if (get == RIGHT)
		{
			Move(RIGHT);
		}
	}
}

void Player::Move(char input)
{
	int offsetx = 0;
	int offsety = 0;
	int code;

	switch (input)
	{
	case UP:
		offsety = -1;
		break;
	case DOWN:
		offsety = 1;
		break;
	case LEFT:
		offsetx = -1;
		break;
	case RIGHT:
		offsetx = 1;
		break;
	default:
		break;
	}

	if (X + offsetx == 0 || Y + offsety == 0 || X + offsetx == DEFAULT_WIDTH - 1 || Y + offsety == DEFAULT_HEIGHT - 1)
	{
		return;
	}

	code = GameManager::GetInstacne()->CollisionCheck(Point(X + offsetx, Y + offsety), m_Code);

	if (code == WALL)
	{
		return;
	}
	else if(code != 0)
	{
		Collision_Handle(code);
	}

	m_MapDraw.ErasePoint(X, Y);
	X = X + offsetx;
	Y = Y + offsety;
	m_MapDraw.DrawPoint(m_Icon, X, Y);
}

void Player::Collision_Handle(int Code)
{
	switch (Code)
	{
	case DOOR:
		GameManager::GetInstacne()->Stage_Clear();
		return;
	default:
		break;
	}
}

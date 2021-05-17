#include "ChessPiece.h"
#include "CollisionManager.h"
#include "ResourceManager.h"

King::King()
{
}

King::~King()
{
}

void King::Init(bool isdark, POINT point)
{
	state = NON;
	if (isdark)
	{
		team = DARK;
		id = BLACK_KING;
	}
	else
	{
		team = WHITE;
		id = WHITE_KING;
	}
	pos = point;
}

void King::Update()
{
	ChessPiece *piece;
	POINT movePoint;

	ChessPiece::Update();
	movingPoint.erase(movingPoint.begin(), movingPoint.end());

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			movePoint.x = pos.x + x;
			movePoint.y = pos.y + y;
			if (movePoint.x  < 8 && movePoint.y < 8 && movePoint.x > -1 && movePoint.y > -1 && !(movePoint.x == pos.x && movePoint.y == pos.y))
			{
				piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);
				if (piece == NULL)
				{
					movingPoint.push_back(movePoint);
				}
				else if (piece->GetTeam() != team)
				{
					movingPoint.push_back(movePoint);
				}
			}
		}
	}

}

Queen::Queen()
{
}

Queen::~Queen()
{
}

void Queen::Init(bool isdark, POINT point)
{
	state = NON;
	if (isdark)
	{
		team = DARK;
		id = BLACK_QUEEN;
	}
	else
	{
		team = WHITE;
		id = WHITE_QUEEN;
	}
	pos = point;
}

void Queen::Update()
{
	ChessPiece *piece;
	POINT movePoint;

	ChessPiece::Update();
	movingPoint.erase(movingPoint.begin(), movingPoint.end());

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			for (int i = 1; i < 8; i++)
			{
				movePoint.x = pos.x + (x * i);
				movePoint.y = pos.y + (y * i);
				if (movePoint.x  < 8 && movePoint.y < 8 && movePoint.x > -1 && movePoint.y > -1 && !(movePoint.x == pos.x && movePoint.y == pos.y))
				{
					piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

					if (piece == NULL)
					{
						movingPoint.push_back(movePoint);
					}
					else if (piece != NULL && piece->GetTeam() != team)
					{
						movingPoint.push_back(movePoint);
						break;
					}
					else if (piece != NULL && piece->GetTeam() == team)
					{
						break;
					}
				}

			}
		}
	}

}



Rook::Rook()
{
}

Rook::~Rook()
{
}

void Rook::Init(bool isdark, POINT point)
{
	state = NON;
	if (isdark)
	{
		team = DARK;
		id = BLACK_ROOK;
	}
	else
	{
		team = WHITE;
		id = WHITE_ROOK;
	}
	pos = point;
}

void Rook::Update()
{
	ChessPiece *piece;
	POINT movePoint;

	ChessPiece::Update();
	movingPoint.erase(movingPoint.begin(), movingPoint.end());

	for (int x = -1; x < 2; x += 2)
	{
		for (int i = 1; i < 8; i++)
		{
			movePoint.x = pos.x + (x * i);
			movePoint.y = pos.y;
			if (movePoint.x  < 8 && movePoint.y < 8 && movePoint.x > -1 && movePoint.y > -1 && !(movePoint.x == pos.x && movePoint.y == pos.y))
			{
				piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

				if (piece == NULL)
				{
					movingPoint.push_back(movePoint);
				}
				else if (piece != NULL && piece->GetTeam() != team)
				{
					movingPoint.push_back(movePoint);
					break;
				}
				else if (piece != NULL && piece->GetTeam() == team)
				{
					break;
				}
			}
		}
	}

	for (int y = -1; y < 2; y += 2)
	{
		for (int i = 1; i < 8; i++)
		{
			movePoint.x = pos.x;
			movePoint.y = pos.y + (y * i);
			if (movePoint.x  < 8 && movePoint.y < 8 && movePoint.x > -1 && movePoint.y > -1 && !(movePoint.x == pos.x && movePoint.y == pos.y))
			{
				piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

				if (piece == NULL)
				{
					movingPoint.push_back(movePoint);
				}
				else if (piece != NULL && piece->GetTeam() != team)
				{
					movingPoint.push_back(movePoint);
					break;
				}
				else if (piece != NULL && piece->GetTeam() == team)
				{
					break;
				}
			}
		}
	}


}

Bishop::Bishop()
{
}

Bishop::~Bishop()
{
}

void Bishop::Init(bool isdark, POINT point)
{
	state = NON;
	if (isdark)
	{
		team = DARK;
		id = BLACK_BISHOP;
	}
	else
	{
		team = WHITE;
		id = WHITE_BISHOP;
	}
	pos = point;
}

void Bishop::Update()
{
	ChessPiece *piece;
	POINT movePoint;

	ChessPiece::Update();
	movingPoint.erase(movingPoint.begin(), movingPoint.end());

	for (int y = -1; y < 2; y += 2)
	{
		for (int x = -1; x < 2; x += 2)
		{
			for (int i = 1; i < 8; i++)
			{
				movePoint.x = pos.x + (x * i);
				movePoint.y = pos.y + (y * i);
				if (movePoint.x  < 8 && movePoint.y < 8 && movePoint.x > -1 && movePoint.y > -1 && !(movePoint.x == pos.x && movePoint.y == pos.y))
				{
					piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);
					if (piece == NULL)
					{
						movingPoint.push_back(movePoint);
					}
					else if (piece != NULL && piece->GetTeam() != team)
					{
						movingPoint.push_back(movePoint);
						break;
					}
					else if (piece != NULL && piece->GetTeam() == team)
					{
						break;
					}
				}

			}
		}
	}

}

Knight::Knight()
{
}

Knight::~Knight()
{
}

void Knight::Init(bool isdark, POINT point)
{
	state = NON;
	if (isdark)
	{
		team = DARK;
		id = BLACK_KNIGHT;
	}
	else
	{
		team = WHITE;
		id = WHITE_KNIGHT;
	}
	pos = point;
}

void Knight::Update()
{
	ChessPiece *piece;
	POINT movePoint;

	ChessPiece::Update();
	movingPoint.erase(movingPoint.begin(), movingPoint.end());

	for (int y = -2; y < 3; y += 4)
	{
		for (int x = -1; x < 3; x += 2)
		{
			movePoint.x = pos.x + x;
			movePoint.y = pos.y + y;
			if (movePoint.x  < 8 && movePoint.y < 8 && movePoint.x > -1 && movePoint.y > -1 && !(movePoint.x == pos.x && movePoint.y == pos.y))
			{
				piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

				if (piece == NULL || piece->GetTeam() != team)
				{
					movingPoint.push_back(movePoint);
				}
			}
		}
	}

	for (int y = -2; y < 3; y += 4)
	{
		for (int x = -1; x < 3; x += 2)
		{
			movePoint.x = pos.x + y;
			movePoint.y = pos.y + x;
			if (movePoint.x  < 8 && movePoint.y < 8 && movePoint.x > -1 && movePoint.y > -1 && !(movePoint.x == pos.x && movePoint.y == pos.y))
			{
				piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

				if (piece == NULL || piece->GetTeam() != team)
				{
					movingPoint.push_back(movePoint);

				}
			}
		}
	}

}

Pawn::Pawn()
{
}

Pawn::~Pawn()
{
}

void Pawn::Init(bool isdark, POINT point)
{
	first = true;
	state = NON;
	if (isdark)
	{
		team = DARK;
		id = BLACK_PAWN;
	}
	else
	{
		team = WHITE;
		id = WHITE_PAWN;
	}
	pos = point;
}

void Pawn::Update()
{
	ChessPiece *piece;
	POINT movePoint;

	ChessPiece::Update();
	movingPoint.erase(movingPoint.begin(), movingPoint.end());
	movePoint.x = pos.x;

	if (first)
	{
		if (team == DARK)
		{
			movePoint.y = pos.y + 2;
		}
		else
		{
			movePoint.y = pos.y - 2;
		}

		piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

		if (piece == NULL)
		{
			movingPoint.push_back(movePoint);
		}
	}


	if (team == DARK)
	{
		movePoint.y = pos.y + 1;
	}
	else
	{
		movePoint.y = pos.y - 1;
	}

	piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

	if (piece == NULL)
	{
		movingPoint.push_back(movePoint);
	}

	for (int x = -1; x < 2; x += 2)
	{
		movePoint.x = pos.x + x;

		piece = CollisionManager::GetInstance()->CollisionCheck(movePoint);

		if (piece != NULL && piece->GetTeam() != team)
		{
			movingPoint.push_back(movePoint);
		}
	}

}


void Pawn::Move(POINT movePos)
{
	ChessPiece::Move(movePos);
	if (first)
	{
		first = false;
	}
}

ChessPiece* Create(bool dark, std::string code, POINT pos)
{
	if (code == "King")
	{
		King *king = new King();
		king->Init(dark, pos);
		return king;
	}
	if (code == "Queen")
	{
		Queen *queen = new Queen();
		queen->Init(dark, pos);
		return queen;
	}
	if (code == "Rook")
	{
		Rook *rook = new Rook();
		rook->Init(dark, pos);
		return rook;
	}
	if (code == "Bishop")
	{
		Bishop *bishop = new Bishop();
		bishop->Init(dark, pos);
		return bishop;
	}
	if (code == "Knight")
	{
		Knight *knight = new Knight();
		knight->Init(dark, pos);
		return knight;
	}
	if (code == "Pawn")
	{
		Pawn *pawn = new Pawn();
		pawn->Init(dark, pos);
		return pawn;
	}
}

void ChessPiece::Update()
{
	if (state == OVER)
	{
		return;
	}
}

void ChessPiece::Move(POINT movePos)
{
	pos = movePos;
}

void ChessPiece::DrawMovingPoint(HDC hdc)
{
	if (state == SELECT)
	{
		for (std::list<POINT>::iterator i = movingPoint.begin(); i != movingPoint.end(); i++)
		{
			ResourceManager::GetInstance()->Draw(TILE_MOVE, hdc, (*i), false);
		}
	}
}

void ChessPiece::Draw(HDC hdc)
{
	if (state != OVER)
	{
		ResourceManager::GetInstance()->Draw(id, hdc, pos, true);
	}
}

void ChessPiece::Catch()
{
	state = OVER;
	CollisionManager::GetInstance()->Erase(this);
	movingPoint.erase(movingPoint.begin(), movingPoint.end());
}

POINT ChessPiece::GetMovingParts(int x, int y)
{
	SIZE size = ResourceManager::GetInstance()->GetSize(id);
	POINT pt;
	RECT rect;
	pt.x = x;
	pt.y = y;

	for (std::list<POINT>::iterator i = movingPoint.begin(); i != movingPoint.end(); i++)
	{
		rect.left = (*i).x * size.cx *0.5f;
		rect.top = (*i).y * size.cy *0.5f;
		rect.right = (*i).x * (size.cx *0.5f) + size.cx * 0.5f;
		rect.bottom = (*i).y * (size.cy *0.5f) + size.cy * 0.5f;
		if (PtInRect(&rect, pt))
		{
			return (*i);
		}
	}

	POINT point;
	point.x = -1;
	point.y = -1;
	return point;
}

RECT ChessPiece::GetBox()
{
	SIZE size = ResourceManager::GetInstance()->GetSize(id);
	RECT rect =
	{
		(pos.x * size.cx) * 0.5f,
		(pos.y * size.cy) * 0.5f,
		((pos.x * size.cx) * 0.5f) + size.cx * 0.5f,
		((pos.y * size.cy) * 0.5f) + size.cy * 0.5f
	};

	return rect;
}

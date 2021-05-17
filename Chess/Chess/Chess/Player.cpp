#include "Player.h"

Player::Player()
{

}

Player::~Player()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		delete pieces[i];
	}

	std::vector<ChessPiece*>().swap(pieces);
}

void Player::Init(bool dark)
{
	ChessPiece *piece;
	POINT pos;
	curChess = NULL;

	if (dark)
	{
		team = DARK;
		pos.y = 0;
	}
	else
	{
		team = WHITE;
		pos.y = 7;
	}

	pos.x = 0;
	piece = Create(dark, "Rook", pos);
	pieces.push_back(piece);
	pos.x++;
	piece = Create(dark, "Knight", pos);
	pieces.push_back(piece);
	pos.x++;

	piece = Create(dark, "Bishop", pos);
	pieces.push_back(piece);
	pos.x++;

	piece = Create(dark, "King", pos);
	pieces.push_back(piece);
	pos.x++;

	piece = Create(dark, "Queen", pos);
	pieces.push_back(piece);
	pos.x++;

	piece = Create(dark, "Bishop", pos);
	pieces.push_back(piece);
	pos.x++;

	piece = Create(dark, "Knight", pos);
	pieces.push_back(piece);
	pos.x++;

	piece = Create(dark, "Rook", pos);
	pieces.push_back(piece);

	if (dark)
	{
		pos.y++;
	}
	else
	{
		pos.y--;
	}

	for (int i = 0; i < 8; i++)
	{
		pos.x = i;
		piece = Create(dark, "Pawn", pos);
		pieces.push_back(piece);
	}

	for (int i = 0; i < pieces.size(); i++)
	{
		CollisionManager::GetInstance()->Push(pieces[i]);
	}
}

void Player::MovingPartsDraw(HDC hdc)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->DrawMovingPoint(hdc);
	}
}

void Player::Draw(HDC hdc)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->Draw(hdc);
	}
}

void Player::Reset(bool dark)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		delete pieces[i];
	}

	std::vector<ChessPiece*>().swap(pieces);
	Init(dark);
}

bool Player::Click(int x, int y)
{

	if (curChess != NULL)
	{
		POINT pos;
		ChessPiece* piece;
		pos = curChess->GetMovingParts(x, y);

		if (pos.x == -1 && pos.y == -1)
		{
			curChess->Relase();
			curChess = NULL;
			return false;
		}

		piece = CollisionManager::GetInstance()->CollisionCheck(pos);

		if (piece == NULL)
		{
			curChess->Move(pos);
			curChess->Relase();
			curChess = NULL;
			return true;
		}
		else if (piece->GetTeam() != team)
		{
			curChess->Move(pos);
			curChess->Relase();
			curChess = NULL;
			piece->Catch();
			return true;
		}


	}
	else
	{
		POINT pos;
		pos.x = x;
		pos.y = y;
		ChessPiece* piece = CollisionManager::GetInstance()->MouseClickCheck(pos);

		for (int i = 0; i < pieces.size(); i++)
		{
			if (piece == pieces[i] && piece->GetState() != OVER)
			{
				curChess = pieces[i];
				curChess->Select();
			}
		}

		return false;
	}
}

void Player::Update()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->Update();
	}

}

void Player::PawnCheck()
{
	POINT pos;
	if (team == DARK)
	{
		for (int i = 0; i < pieces.size(); i++)
		{
			if (pieces[i]->GetID() == BLACK_PAWN && pieces[i]->GetPos().y == 7)
			{
				pos = pieces[i]->GetPos();
				CollisionManager::GetInstance()->Erase(pieces[i]);
				delete pieces[i];
				pieces[i] = Create(true, "Queen", pos);
				CollisionManager::GetInstance()->Push(pieces[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < pieces.size(); i++)
		{
			if (pieces[i]->GetID() == WHITE_PAWN && pieces[i]->GetPos().y == 0)
			{
				pos = pieces[i]->GetPos();
				CollisionManager::GetInstance()->Erase(pieces[i]);
				delete pieces[i];
				pieces[i] = Create(false, "Queen", pos);
				CollisionManager::GetInstance()->Push(pieces[i]);
			}
		}
	}
}

bool Player::KingCheck()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->GetState() == OVER && (pieces[i]->GetID() == WHITE_KING || pieces[i]->GetID() == BLACK_KING))
		{
			return true;
		}
	}

	return false;
}

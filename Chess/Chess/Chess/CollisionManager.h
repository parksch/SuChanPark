#pragma once
#include <vector>
#include "Singleton.h"
#include "ChessPiece.h"

class CollisionManager : public Singleton<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();
	void Push(ChessPiece* object);
	ChessPiece* MouseClickCheck(POINT point);
	ChessPiece* CollisionCheck(POINT point);
	void Erase(ChessPiece* piece);
private:
	std::vector<ChessPiece*> objects;
};

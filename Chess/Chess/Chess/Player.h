#pragma once
#include <Windows.h>
#include <vector>
#include "ChessPiece.h"
#include "CollisionManager.h"

class Player
{
public:
	Player();
	~Player();
	void Init(bool dark);
	void MovingPartsDraw(HDC hdc);
	void Draw(HDC hdc);
	void Reset(bool dark);
	bool Click(int x, int y);
	void Move(int x, int y);
	void Update();
	void PawnCheck();
	bool KingCheck();
private:
	TEAM team;
	ChessPiece *curChess;
	std::vector<ChessPiece*> pieces;
	POINT pos;
};


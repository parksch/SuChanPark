#pragma once
#include <Windows.h>
#include <string>
#include <list>
#include "Macro.h"

class ChessPiece
{
public:
	ChessPiece() {};
	virtual ~ChessPiece() {};
	virtual void Init(bool isdark, POINT point) = 0;
	virtual void Update();
	virtual void Move(POINT movePos);
	void Select() { state = SELECT; };
	void Relase() { state = NON; };
	void DrawMovingPoint(HDC hdc);
	void Draw(HDC hdc);
	void Catch();
	int GetID() { return id; }
	STATE GetState() { return state; }
	POINT GetMovingParts(int x, int y);
	POINT GetPos() { return pos; }
	TEAM GetTeam() { return team; }
	RECT GetBox();
protected:
	TEAM team;
	std::list <POINT> movingPoint;
	STATE state;
	int id;
	POINT pos;
};

class King : public ChessPiece
{
public:
	King();
	~King();
	void Init(bool isdark, POINT point);
	void Update();
private:
};

class Queen : public ChessPiece
{
public:
	Queen();
	~Queen();
	void Init(bool isdark, POINT point);
	void Update();
private:

};

class Rook : public ChessPiece
{
public:
	Rook();
	~Rook();
	void Init(bool isdark, POINT point);
	void Update();
private:

};

class Bishop : public ChessPiece
{
public:
	Bishop();
	~Bishop();
	void Init(bool isdark, POINT point);
	void Update();
private:

};

class Knight : public ChessPiece
{
public:
	Knight();
	~Knight();
	void Init(bool isdark, POINT point);
	void Update();
private:

};

class Pawn : public ChessPiece
{
public:
	Pawn();
	~Pawn();
	void Init(bool isdark, POINT point);
	void Update();
	void Move(POINT movePos);
private:
	bool first;
};

ChessPiece* Create(bool dark, std::string code, POINT pos);

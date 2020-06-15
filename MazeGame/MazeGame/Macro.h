#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
#define DEFAULT_WIDTH 15
#define DEFAULT_HEIGHT 15
#define WALL 1
#define PLAYER 2
#define DOOR 3
#define POTAL 4
#define TRAP 5
#define MAXSTAGE 3

#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );

struct Point
{
	Point(int Width = 0,int Height = 0) : X(Width), Y(Height){}
	bool operator==(const Point pos) { return (this->X == pos.X && this->Y == pos.Y); }
	bool operator!=(const Point pos) { return !(this->X == pos.X && this->Y == pos.Y); }
	void Set(int x, int y) { X = x, Y = y; }
	int X;
	int Y;
};

enum PLAYER_STATE
{
	PLAYER_LIVE,
	PLAYER_CLEAR,
	PLAYER_DIE
};
#pragma once
#include "BitMap.h"

class Block 
{
public:
	Block() {};
	~Block() {};
	void Init(int width, int height);
	void Draw(HDC hdc,int offsetX,int offsetY);
	void ChanageState(string code);
	void Numbering(int number);
	void SetMine() { isMine = true; }
	string CollisionCheck(POINT mousePos,POINT offset,int key_Code);
	bool getMine() { return isMine; }
	bool getFlag() { return isFlag; }
	bool getNonBlock() { return isNonBlock; }
	bool getHide() { return isHide; }
private:
	BitMap *mine;
	BitMap *flag;
	BitMap *hide;
	BitMap *block;
	bool isNonBlock;
	bool isFlag;
	bool isHide;
	bool isMine;
	POINT pos;
};


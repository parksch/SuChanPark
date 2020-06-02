#include "Player.h"



Player::Player()
{
}
void Player::Release()
{
	while (Release_Stone());
	m_iReturn_Count = 5;
}
bool Player::Release_Stone()
{
	if (m_iStoneCount > 0)
	{
		m_iStoneCount--;
		delete m_StoneList[m_iStoneCount];
		return true;
	}
	return false;
}
bool Player::Compare_Stone(int x, int y)
{
	for (int i = 0; i < m_iStoneCount; i++)
	{
		if (m_StoneList[i]->x == x && m_StoneList[i]->y == y)
			return true;
	}
	return false;
}
void Player::Create_Stone(int x, int y)
{
	m_StoneList[m_iStoneCount] = new Stone;
	m_StoneList[m_iStoneCount]->x = x;
	m_StoneList[m_iStoneCount]->y = y;
	m_iStoneCount++;
}

bool Player::Omok_Win(int x, int y)
{
	if (m_iStoneCount == 0)
		return false;
	else
	{
		if (StoneCheck(x, y,-1,0) + StoneCheck(x, y, 1, 0) + 1 == 5)
			return true;
		else if (StoneCheck(x, y, 0, -1) + StoneCheck(x, y, 0, 1) + 1 == 5)
			return true;
		else if (StoneCheck(x, y, -1, 0-1) + StoneCheck(x, y, 1, 1) + 1 == 5)
			return true;
		else if (StoneCheck(x, y, 1, -1) + StoneCheck(x, y, -1, 1) + 1 == 5)
			return true;
	}
	return false;
}
Stone* Player::Stone_Backing()
{
	Stone* tmp;
	if (m_iStoneCount > 0 && m_iReturn_Count > 0)
	{
		m_iStoneCount--;
		tmp = m_StoneList[m_iStoneCount];
		m_StoneList[m_iStoneCount] = NULL;
		m_iReturn_Count--;
		return tmp;
	}
	else
		return NULL;
}

int Player::StoneCheck(int x, int y, int WidthNum, int HeightNum)
{
	int Count = 0;
	while (Compare_Stone(x += WidthNum, y += HeightNum))
	{
		Count++;
	}
	return Count;
}


Player::~Player()
{
	Release();
}

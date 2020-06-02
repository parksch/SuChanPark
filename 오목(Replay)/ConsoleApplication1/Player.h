#pragma once
#include"Mecro.h"
struct Stone
{
	int x;
	int y;
};
class Player
{
private:
	string m_strTeamName;
	Stone* m_StoneList[4050];
	string m_strStone_State;
	int m_iStoneCount = 0;
	int m_iReturn_Count = 5;
	bool Release_Stone();
	int StoneCheck(int x, int y, int WidthNum, int HeightNum);
public:
	void Release();
	bool Compare_Stone(int x, int y);
	void Create_Stone(int x, int y);
	bool Omok_Win(int x, int y);
	Stone* Stone_Backing();
	inline void Return_Set(int num)
	{
		m_iReturn_Count = num;
		return;
	}
	inline void SetStone(string Stone)
	{
		m_strStone_State = Stone;
		return;
	}
	inline string GetStone()
	{
		return m_strStone_State;
	}
	inline int Get_Return_Count()
	{
		return m_iReturn_Count;
	}
	inline string GetName()
	{
		return m_strTeamName;
	}
	inline void SetName(string Name)
	{
		m_strTeamName = Name;
	}
	inline Stone* GetStonePosition(int index)
	{
		return m_StoneList[index];
	}
	Player();
	~Player();
};


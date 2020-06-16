#pragma once
#include "Macro.h"
#include "Interface.h"

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

class Object
{
public:
	Object() {};
	virtual ~Object() {};
	virtual void Collision_Handle(int Code) = 0;
	virtual void Update() = 0;
	bool Comp(Point pos) { return pos == Point(X, Y); }
	inline int getX() { return X; }
	inline int getY() { return Y; }
	inline int getCode() { return m_Code; }
protected:
	Interface m_MapDraw;
	string m_Icon;
	int m_Code;
	int X;
	int Y;
};

class Observer :public Object
{
public:
	virtual void Notify() = 0;
};

class BossAlarm : public Object
{
public:
	BossAlarm() {};
	~BossAlarm() {};

	//������ ������ ���
	void AddPlayer(Observer* player)
	{
		players.push_back(player);
	}

	//���ð� ���� ������ ����
	void RemovePlayer(Observer* player)
	{
		vector<Observer*>::iterator seek = find(players.begin(), players.end(), player);
		players.erase(seek);
	}

	//��Ƽ�� ���̼� ���
	void Notification()
	{
		vector<Observer*>::iterator seek = players.begin();
		vector<Observer*>::iterator end = players.end();

		while (seek != end)
		{
			(*seek)->Notify();
			seek++;
		}

	}

	void Notification(Observer* player)
	{
		if (isAppear)
		{
			player->Notify();
		}
	}

protected:
	bool isAppear;
private:
	vector<Observer*> players;
};


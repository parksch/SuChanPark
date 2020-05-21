#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Point
{
	Point(int x, int y):X(x),Y(y) {}
	int X;
	int Y;

	bool operator ==(Point &point)
	{
		if (point.X == this->X && point.Y == point.X)
		{
			return true;
		}

		return false;
	}

	bool operator >(Point &point)
	{
		if (this->X > point.X && this->Y > point.Y)
		{
			return true;
		}
		else if (this->X > point.X && this->Y < point.Y)
		{
			return true;
		}
		else if (this->X == point.X && this->Y > point.Y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator <(Point &point)
	{
		if (this->X < point.X && this->Y < point.Y)
		{
			return true;
		}
		else if (this->X < point.X && this->Y > point.Y)
		{
			return true;
		}
		else if (this->X == point.X && this->Y < point.Y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend ostream& operator << (ostream&os,Point &point)
	{
		os << to_string(point.X) << ", " << to_string(point.Y);
		return os;
	}
};

class Node
{
public:
	Node(Point data) : m_Data(data) { m_Next = NULL;}
	~Node() {};
	void RemoveAll();
	Node* FindPre(Point m_Data);
	void ShowAll();
	Point m_Data;
	Node *m_Pre;
	Node *m_Next;
};

class List
{
public:
	List();
	~List();
	void insert(Point data);
	void ShowAll();
	int size() { return m_Size; }
	Node* begin() { return m_Head; }
	Node* end() { return m_Tail; }
private:
	Node *m_Head;
	Node *m_Tail;
	int m_Size;
};


#pragma once
#include <iostream>
#include <string>
#include "Character.h"
using namespace std;

template <typename T>
class Node
{
public:
	Node(T data) { m_Data = data; m_Next = NULL; }
	~Node() {}
	void Add(T data);
	void RemoveAll();
	void ShowAll();
	void Sort();
	void Sort(bool(*fp)(Character) );
	bool operator >(T data) { return this->m_Data > data; }
	bool operator <(T data) { return this->m_Data < data; }
	T m_Data;
	Node<T>* m_Next;
};

template<typename T>
void Node<T>::Add(T data)
{
	if (m_Next != NULL)
	{
		m_Next->Add(data);
	}
	else
	{
		m_Next = new Node<T>(data);
	}
}

template<typename T>
void Node<T>::RemoveAll()
{
	if (m_Next != NULL)
	{
		m_Next->RemoveAll();
	}

	delete this;
}

template<typename T>
inline void Node<T>::ShowAll()
{
	cout << m_Data << endl;

	if (m_Next != NULL)
	{
		m_Next->ShowAll();
	}
}

template<typename T>
void Node<T>::Sort()
{
	Node *temp = m_Next;

	while (temp != NULL)
	{
		if (temp->m_Data > m_Data)
		{
			T TempData = temp->m_Data;
			temp->m_Data = m_Data;
			m_Data = TempData;
		}

		temp = m_Next->m_Next;
	}
	
	if (m_Next != NULL)
	{
		m_Next->Sort();
	}
}

template<typename T>
void Node<T>::Sort(bool(*fp)(Character))
{

}

template <typename T>
class List
{
public:
	List();
	~List();
	void Add(T data);
	void ShowAll();
	void Sort();
	void Sort(bool(*fp)(Character));
private:
	Node<T> *m_Head;
};

template<typename T>
List<T>::List()
{
	m_Head = NULL;
}

template<typename T>
List<T>::~List()
{
	if (m_Head != NULL)
	{
		m_Head->RemoveAll();
	}
}

template<typename T>
void List<T>::Add(T data)
{
	if (m_Head == NULL)
	{
		m_Head = new Node<T>(data);
	}
	else
	{
		m_Head->Add(data);
	}

	m_Head->Sort();
}

template<typename T>
void List<T>::ShowAll()
{
	m_Head->ShowAll();
}

template<typename T>
void List<T>::Sort()
{
	m_Head->Sort();
}

template<typename T>
void List<T>::Sort(bool(*fp)(Character))
{
}


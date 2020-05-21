#include "List.h"

List::List()
{
	m_Head = NULL;
	m_Tail = NULL;
	m_Size = 0;
}

List::~List()
{
	if (m_Head != NULL)
	{
		m_Head->RemoveAll();
	}
}

void List::insert(Point data)
{
	m_Size++;

	if (m_Head == NULL)
	{
		m_Head = new Node(data);
		m_Tail = m_Head;
	}
	else
	{
		m_Tail->m_Next = new Node(data);
		m_Tail = m_Tail->m_Next;
	}
}

void List::ShowAll()
{
	if (m_Head == NULL)
	{
		return;
	}

	m_Head->ShowAll();
}

void Node::RemoveAll()
{
	if (m_Next != NULL)
	{
		m_Next->RemoveAll();
	}

	delete this;
}

Node * Node::FindPre(Point data)
{
	if (m_Next->m_Data == data)
	{
		return this;
	}

	if (m_Next != NULL)
	{
		m_Next->FindPre(data);
	}
}

void Node::ShowAll()
{
	cout << m_Data << endl;

	if (m_Next != NULL)
	{
		m_Next->ShowAll();
	}
}



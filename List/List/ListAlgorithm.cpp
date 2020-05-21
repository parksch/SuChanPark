#include "ListAlgorithm.h"

void ListSort(List &list)
{
	if (list.begin() == NULL)
	{
		return;
	}

	quickSort(list.begin(), list.end(),list.size());
}

void quickSort(Node*left, Node*right,int size)
{
	if (size <= 1)
	{
		return;
	}

	Node* leftNode = left->m_Next;
	Node* rightNode = right;
	Node* pivotNode = left;
	int nleft = 1;
	int nright = size;

	while (1)
	{
		while (leftNode->m_Data > pivotNode->m_Data)
		{
			leftNode = leftNode->m_Next;
			nleft++;
		}

		while (rightNode->m_Data < pivotNode->m_Data)
		{
			rightNode = 
		}
	}
}

#include "ListAlgorithm.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	List list;
	list.insert(Point(10, 20));
	list.insert(Point(5, 10));
	list.insert(Point(2, 60));
	list.insert(Point(3, 4));
	list.insert(Point(5, 50));
	list.ShowAll();
	getchar();
}
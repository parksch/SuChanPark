#include "List.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	List<string> list;
	List<Character> clist;
	Character character("asd",10);
	clist.Add(character);
	clist.ShowAll();
	list.Add("hi");
	list.Add("hello");
	list.Add("bye");
	list.Add("A");
	list.ShowAll();
	getchar();
}
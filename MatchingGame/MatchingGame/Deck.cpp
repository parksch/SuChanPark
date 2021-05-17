#include "Deck.h"
#include "resource.h"

Deck* Deck::m_pThis = nullptr;

Deck::~Deck()
{
	for (int i = 0; i < cards.size(); i++)
	{
		delete cards[i];
	}
	vector<BitMap*>().swap(cards);
}

void Deck::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	BitMap *temp;
	for (int i = IDB_BITMAP1 ; i < IDB_BITMAP11 + 1; i++)
	{
		temp = new BitMap();
		temp->Init(hdc, hInst, i);
		cards.push_back(temp);
	}
	ReleaseDC(hWnd, hdc);
}

BitMap * Deck::Find(int index)
{
	return cards[index];
}




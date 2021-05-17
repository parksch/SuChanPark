#include "GameManager.h"
#include <time.h>
#include <string>
GameManager* GameManager::m_pThis = nullptr;

GameManager::GameManager()
{
	srand(time(NULL));
	isClickFail = false;
	score = 0;
	curIndex = -1;
}

GameManager::~GameManager()
{
	Deck::DestoryInstance();
}

void GameManager::Init(HWND hWnd, HINSTANCE hInstance)
{
	Deck::GetInstance()->Init(hWnd, hInstance);
	Set();
}

void GameManager::Draw(HWND hWnd)
{
	HDC hdc;
	PAINTSTRUCT ps;
	BitMap *temp;
	Card card;
	hdc = BeginPaint(hWnd, &ps);
	TextOut(hdc, 500, 10, TEXT(to_string(score).c_str()), strlen(to_string(score).c_str()));

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < cards.size() / 2; x++)
		{
			card = cards[x + (y * cards.size() / 2)];
			if (card.state == STATE_HIDE)
			{
				temp = Deck::GetInstance()->Find(10);
			}
			else
			{
				temp = Deck::GetInstance()->Find(cards[x + (y * (cards.size() / 2))].index);
			}
			
			temp->Draw(hdc, card.pos.x, card.pos.y, CARDSIZE,CARDSIZE);
		}
	}

	if (score == cards.size() / 2)
	{
		MessageBox(hWnd, TEXT("클리어"), TEXT("축하합니다"), MB_OK);
		Set();
		InvalidateRect(hWnd, NULL, true);
	}

	EndPaint(hWnd, &ps);
}

void GameManager::Update(HWND hWnd)
{
	if (isClickFail)
	{
		cards[curIndex].state = STATE_HIDE;
		curIndex = -1;
		for (int i = 0; i < cards.size(); i++)
		{
			if (cards[i].state == STATE_OPEN_FAIL)
			{
				cards[i].state = STATE_HIDE;
			}
		}
		isClickFail = false;
		InvalidateRect(hWnd, NULL, true);
	}
}

void GameManager::Click(HWND hWnd,int mouseX, int mouseY)
{
	if (isClickFail)
	{
		return;
	}

	SIZE size;

	for (int i = 0; i < cards.size(); i++)
	{
		size = Deck::GetInstance()->Find(cards[i].index)->GetSize();
		if ((mouseX >= cards[i].pos.x && mouseX <= cards[i].pos.x + (size.cx * CARDSIZE)) &&
			(mouseY >= cards[i].pos.y && mouseY <= cards[i].pos.y + (size.cy * CARDSIZE))
			)
		{
			if (curIndex != -1 && curIndex != i && cards[i].state == STATE_HIDE)
			{
				if (cards[curIndex].index == cards[i].index)
				{
					cards[i].state = STATE_OPEN_SUCCESS;
					cards[curIndex].state = STATE_OPEN_SUCCESS;
					curIndex = -1;
					score++;

					return;
				}
				else
				{
					cards[i].state = STATE_OPEN_FAIL;
					isClickFail = true;
					SetTimer(hWnd, 1, 1000, NULL);
					return;
				}
			}
			else if(cards[i].state == STATE_HIDE)
			{
				cards[i].state = STATE_SELECT;
				curIndex = i;
				return;
			}

		}
	}

	if (curIndex != -1)
	{
		cards[curIndex].state = STATE_HIDE;
		curIndex = -1;
		return;
	}

}

void GameManager::Set()
{
	int randidx[10];
	int count;
	int idx;
	Card card;
	vector<Card>().swap(cards);
	cards.reserve(MAXCARD);
	score = 0;
	for (int i = 0; i < 2; i++)
	{
		count = 10;
		for (int j = 0; j < 10; j++)
		{
			randidx[j] = j;
		}

		for (int k = 0; k < 10; k++)
		{
			idx = rand() % count;
			card.index = randidx[idx];
			card.pos.x = 10 + (k * 150);
			card.pos.y = 100 + (i * 250);
			card.state = STATE_HIDE;
			cards.push_back(card);
			randidx[idx] = randidx[count - 1];
			count--;
		}
	}

}





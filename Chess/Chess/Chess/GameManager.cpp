#include "ServerManager.h"
#include "GameManager.h"
GameManager* GameManager::m_pThis = nullptr;

GameManager::GameManager()
{
	isGameOn = false;
}

GameManager::~GameManager()
{
	ResourceManager::DestoryInstance();
}

void GameManager::Reset()
{
	if (code == BLACK)
	{
		turn = true;
	}
	else
	{
		turn = false;
	}
	CollisionManager::DestoryInstance();
	p1.Reset(true);
	p2.Reset(false);
	board.x = 8;
	board.y = 8;
}

void GameManager::init(HWND hWnd)
{
	m_hWnd = hWnd;
	turn = true;
	p1.Init(true);
	p2.Init(false);
	board.x = 8;
	board.y = 8;
}

void GameManager::Display(HWND hWnd)
{
	bool cross = false;
	HDC hdc;
	PAINTSTRUCT ps;
	BitMap*temp;
	POINT point;

	hdc = BeginPaint(hWnd, &ps);

	for (int y = 0; y < board.y; y++)
	{

		for (int x = 0; x < board.x; x++)
		{
			point.x = x;
			point.y = y;

			if (cross)
			{
				ResourceManager::GetInstance()->Draw(TILE_BROWN, hdc, point, true);
			}

			ResourceManager::GetInstance()->Draw(TILE_ALPHA, hdc, point, true);
			cross = !cross;
		}

		cross = !cross;
	}

	p1.MovingPartsDraw(hdc);
	p2.MovingPartsDraw(hdc);
	p1.Draw(hdc);
	p2.Draw(hdc);

	EndPaint(hWnd, &ps);
}

void GameManager::Recv(std::string str)
{
	std::string buf = str;
	int x, y;

	if (str == "1p")
	{
		code = BLACK;
		curP = &p1;
		turn = true;
		return;
	}

	if (str == "2p")
	{
		code = WHITE;
		curP = &p2;
		turn = false;
		return;
	}

	if (str == "Game")
	{
		isGameOn = true;
		return;
	}

	if (code == BLACK)
	{
		x = atoi(buf.substr(0, buf.find(" ")).c_str());
		buf = buf.substr(buf.find(" ") + 1);
		y = atoi(buf.substr(0, buf.find(" ")).c_str());

		p2.Update();

		if (p2.Click(x, y))
		{
			turn = !turn;
			Check(m_hWnd);
		}

		InvalidateRect(m_hWnd, NULL, true);
		return;
	}

	if (code == WHITE)
	{
		x = atoi(buf.substr(0, buf.find(" ")).c_str());
		buf = buf.substr(buf.find(" ") + 1);
		y = atoi(buf.substr(0, buf.find(" ")).c_str());

		p1.Update();

		if (p1.Click(x, y))
		{
			turn = !turn;
			Check(m_hWnd);
		}

		InvalidateRect(m_hWnd, NULL, true);
		return;
	}


}

void GameManager::LButtonDown(HWND hWnd, int x, int y)
{
	std::string str;

	if (!isGameOn)
	{
		return;
	}

	if (turn)
	{
		curP->Update();

		str = std::to_string(x) + " " + std::to_string(y);
		ServerManager::GetInstance()->Send(str);

		if (curP->Click(x, y))
		{
			turn = !turn;
		}
	}
}

void GameManager::Check(HWND hWnd)
{
	std::string str;

	if (p1.KingCheck())
	{
		str = "플레이어 2";
		GameOver(str,hWnd);
		return;
	}
	else if (p2.KingCheck())
	{
		str = "플레이어 1";
		GameOver(str, hWnd);
		return;
	}

	p1.PawnCheck();
	p2.PawnCheck();
	InvalidateRect(hWnd, NULL, true);
}

void GameManager::GameOver(std::string str, HWND hWnd)
{
	MessageBox(hWnd, TEXT((str + "승리").c_str()), TEXT("결과"), MB_OK);
	Reset();
	InvalidateRect(hWnd, NULL, true);
	return;
}




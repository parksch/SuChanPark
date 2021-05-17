#include "Paper.h"
#include <math.h>

Paper::Paper()
{
}

Paper::~Paper()
{
	for (int i = 0; i < 4; i++)
	{
		delete m_Paper[i];
	}

	for (int i = 0; i < 3; i++)
	{
		delete m_Stars[i];
	}
}

void Paper::Init(int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;	

	m_Paper[0] = new Animation();
	m_Paper[0]->Push(ResourceManager::GetInstance()->GetBitmap("ColoredPaperGreen.bmp"), m_MapSize.cx *0.25f, m_MapSize.cy * 0.17f);

	m_Paper[1] = new Animation();
	m_Paper[1]->Push(ResourceManager::GetInstance()->GetBitmap("ColoredPaperRed.bmp"), m_MapSize.cx *0.25f, m_MapSize.cy * 0.17f);

	m_Paper[2] = new Animation();
	m_Paper[2]->Push(ResourceManager::GetInstance()->GetBitmap("ColoredPaperYellow.bmp"), m_MapSize.cx *0.25f, m_MapSize.cy * 0.17f);

	m_Paper[3] = new Animation();
	m_Paper[3]->Push(ResourceManager::GetInstance()->GetBitmap("ColoredPaperBlue.bmp"), m_MapSize.cx *0.25f, m_MapSize.cy * 0.17f);

	m_Stars[0] = new Animation();
	m_Stars[0]->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameStar1.bmp"), (m_MapSize.cx *0.25f) *0.8f, (m_MapSize.cy * 0.17f) * 0.8f);

	m_Stars[1] = new Animation();
	m_Stars[1]->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameStar2.bmp"), (m_MapSize.cx *0.25f) *0.8f, (m_MapSize.cy * 0.17f) * 0.8f);

	m_Stars[2] = new Animation();
	m_Stars[2]->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameStar3.bmp"), (m_MapSize.cx *0.25f) *0.8f, (m_MapSize.cy * 0.17f) * 0.8f);

	m_StartPos.x = m_MapSize.cx * 0.37f;
	m_StartPos.y = m_MapSize.cy * 0.46f;

	m_CurPos.x = m_StartPos.x;
	m_CurPos.y = m_StartPos.y;

	isStars = false;
	isMove = false;
	isDraw = false;
}

void Paper::Update(float efTime)
{
	if (isMove)
	{
		
		switch (m_CurState)
		{
		case UP:
			if (m_CurPos.y + ((m_MovePos.y - m_StartPos.y) / 4) <= m_MovePos.y)
			{
				m_CurPos.x = m_MovePos.x;
				m_CurPos.y = m_MovePos.y;
				isMove = false;
				Set();
				return;
			}
			m_CurPos.y += (m_MovePos.y - m_StartPos.y) / 4;
			break;
		case RIGHT:
			if (m_CurPos.x + ((m_MovePos.x - m_StartPos.x) / 4) >= m_MovePos.x)
			{
				m_CurPos.x = m_MovePos.x;
				m_CurPos.y = m_MovePos.y;
				isMove = false;
				Set();
				return;
			}
			m_CurPos.x += (m_MovePos.x - m_StartPos.x) / 4;
			break;
		case DOWN:
			if (m_CurPos.y + ((m_MovePos.y - m_StartPos.y) / 4) >= m_MovePos.y)
			{
				m_CurPos.x = m_MovePos.x;
				m_CurPos.y = m_MovePos.y;
				isMove = false;
				Set();
				return;
			}
			m_CurPos.y += (m_MovePos.y - m_StartPos.y) / 4;
			break;
		case LEFT:
			if (m_CurPos.x + ((m_MovePos.x - m_StartPos.x) / 4) <= m_MovePos.x)
			{
				m_CurPos.x = m_MovePos.x;
				m_CurPos.y = m_MovePos.y;
				isMove = false;
				Set();
				return;
			}
			m_CurPos.x += (m_MovePos.x - m_StartPos.x) / 4;
			break;
		default:
			break;
		}
	}
}

void Paper::Draw(HDC hdc)
{
	if (isDraw)
	{
		m_Paper[m_CurState]->Draw(hdc, m_CurPos.x, m_CurPos.y);
		
		if (isStars)
		{
			m_Stars[m_CurStar]->Draw(hdc, m_CurPos.x + m_Stars[m_CurStar]->GetSize().cx *0.1f, m_CurPos.y + m_Stars[m_CurStar]->GetSize().cy *0.1f);
			TextOut(hdc, m_CurPos.x + m_Stars[m_CurStar]->GetSize().cx *0.5f, m_CurPos.y + m_Stars[m_CurStar]->GetSize().cy *0.5f,TEXT(to_string(m_Score).c_str()),strlen(to_string(m_Score).c_str()));
		}
	}
}

string Paper::CollisionCheck(RECT * rect, string tag, int code)
{
	return string();
}

void Paper::Set()
{
	int randIdx = rand() % 4;
	m_CurState = (MOVE_STATE)randIdx;

	m_CurPos.x = m_StartPos.x;
	m_CurPos.y = m_StartPos.y;

	isDraw = false;
	isStars = false;
}

void Paper::SetStar(int combo)
{
	if (combo == 0)
	{
		isStars = false;
		m_Score = 0;
		return;
	}

	isStars = true;

	m_Score = combo * 100;

	if (combo >= 20)
	{
		m_CurStar = BLUE;
	}
	else if (combo >= 10)
	{
		m_CurStar = GREEN;
	}
	else
	{
		m_CurStar = YELLOW;
	}

}

bool Paper::Move(MOVE_STATE move)
{
	if (move != m_CurState)
	{
		return false;
	}

	isMove = true;

	switch (move)
	{
	case LEFT:
		m_MovePos.x = m_MapSize.cx * 0.03f;
		m_MovePos.y = m_StartPos.y;
		break;
	case RIGHT:
		m_MovePos.x = m_MapSize.cx * 0.7f;
		m_MovePos.y = m_StartPos.y;
		break;
	case UP:
		m_MovePos.x = m_StartPos.x;
		m_MovePos.y = m_MapSize.cy * 0.23f;
		break;
	case DOWN:
		m_MovePos.x = m_StartPos.x;
		m_MovePos.y = m_MapSize.cy * 0.68f;
		break;
	default:
		break;
	}

	return true;
}

void Paper::DrawOn()
{
	isDraw = true;
}

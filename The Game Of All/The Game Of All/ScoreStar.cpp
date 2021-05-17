#include "ScoreStar.h"

ScoreStar::ScoreStar()
{
}

ScoreStar::~ScoreStar()
{
	for (int i = 0; i < 3; i++)
	{
		delete m_Star[i];
	}
}

void ScoreStar::ImageSet()
{
	m_curStar = YELLOW;
	m_Combo = 0;

	m_Star[0] = new Animation();
	m_Star[0]->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameStar1.bmp"));

	m_Star[1] = new Animation();
	m_Star[1]->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameStar2.bmp"));


	m_Star[2] = new Animation();
	m_Star[2]->Push(ResourceManager::GetInstance()->GetBitmap("FlightGameStar3.bmp"));
}

void ScoreStar::CollisionUpdate()
{ 
	m_CollisionBox.left = m_pos.x - m_Star[m_curStar]->GetSize().cx  * 0.2f;
	m_CollisionBox.top = m_pos.y - m_Star[m_curStar]->GetSize().cy * 0.2f;
	m_CollisionBox.right = m_pos.x  + m_Star[m_curStar]->GetSize().cx  * 1.2f;
	m_CollisionBox.bottom = m_pos.y + m_Star[m_curStar]->GetSize().cy * 1.3f;


	if (m_pos.y > m_MapSize.cy *0.86f || m_pos.y < m_MapSize.cy * 0.14f ||
		m_pos.x < -m_Star[m_curStar]->GetSize().cx || m_pos.x > m_MapSize.cx *0.98f
		)
		{
			isLive = false;
		}

}

void ScoreStar::SetCombo(int combo)
{

	m_Combo = combo * 100;

	if (combo >= 20)
	{
		m_curStar = BLUE;
	}
	else if (combo >= 10)
	{
		m_curStar = GREEN;
	}
	else
	{
		m_curStar = YELLOW;
	}
}

bool ScoreStar::Set(int combo)
{
	if (isLive)
	{
		return false;
	}

	int state = rand() % 4;

	m_MoveTime = 0;
	SetCombo(combo);

	switch (state)
	{
	case UP:
		m_pos.x = rand() % (int)(m_MapSize.cx - m_Star[m_curStar]->GetSize().cx);
		m_pos.y = m_MapSize.cy *0.15f;

		m_Offset.y = 1;
		m_Offset.x = ((rand() % (3)) - 1);
		break;
	case RIGHT:
		m_pos.x = m_MapSize.cx - m_Star[m_curStar]->GetSize().cx * 0.5f;
		m_pos.y = m_MapSize.cy *0.15f + rand() % (int)(m_MapSize.cy *0.85f - m_MapSize.cy *0.15f);

		m_Offset.x = -1;
		m_Offset.y = ((rand() % (3)) - 1);
		break;
	case DOWN:
		m_pos.x = rand() % (int)(m_MapSize.cx - m_Star[m_curStar]->GetSize().cx);
		m_pos.y = m_MapSize.cy * 0.90f - m_Star[m_curStar]->GetSize().cy *0.5f;

		m_Offset.y = -1;
		m_Offset.x = ((rand() % (3)) - 1);
		break;
	case LEFT:
		m_pos.x = - m_Star[m_curStar]->GetSize().cx *0.5f;
		m_pos.y = m_MapSize.cy *0.15f + rand() % (int)(m_MapSize.cy *0.85f - m_MapSize.cy *0.15f);
		m_Offset.x = 1;
		m_Offset.y = ((rand() % (3)) - 1);
		break;
	default:
		break;
	}

	isLive = true;
}

void ScoreStar::Draw(HDC hdc)
{
	if (isLive)
	{
		m_Star[m_curStar]->Draw(hdc, m_pos.x, m_pos.y);
		TextOut(hdc, m_pos.x + m_Star[m_curStar]->GetSize().cx *0.25f, m_pos.y + m_Star[m_curStar]->GetSize().cy * 0.45f, TEXT(to_string(m_Combo).c_str()), strlen(to_string(m_Combo).c_str()));
	}
}

string ScoreStar::CollisionEvent()
{
	if (isLive)
	{
		SceneManager::GetInstance()->SendToScene(SCORE_UP);
	}

	isLive = false;

	return "Star";
}


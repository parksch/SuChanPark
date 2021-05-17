#include "TimeBar.h"

TimeBar::TimeBar()
{
}

TimeBar::~TimeBar()
{
	delete m_TimeBar;
}

void TimeBar::Init(int width, int height)
{
	m_size.cx = width;
	m_size.cy = height;
	m_Gage = 300;
	time = 0;
	m_TimeBar = new Animation();
	m_TimeBar->Push(ResourceManager::GetInstance()->GetBitmap("ColoredPaperTimeBar.bmp"), m_size.cx * 0.9f, m_size.cy * 0.05f);

}

void TimeBar::Update(float efTime)
{
	time += efTime;
	
	if (time > 0.1f)
	{
		time = 0;
		if (m_Gage == 0)
		{
			SceneManager::GetInstance()->SendToScene(OVER);
		}
		m_Gage--;
	}
}

void TimeBar::Draw(HDC hdc)
{
	m_TimeBar->Draw(hdc, m_size.cx *0.04f, m_size.cy * 0.95f, m_Gage, 3);
}

string TimeBar::CollisionCheck(RECT * rect, string tag, int code)
{
	return string();
}

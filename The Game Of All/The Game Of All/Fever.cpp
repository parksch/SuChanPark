#include "Fever.h"

Fever::Fever()
{
}

Fever::~Fever()
{
	for (int i = 0; i < 4; i++)
	{
		delete m_Fever[i];
	}

	delete m_FeverEffect;
}

void Fever::Init(int width, int height)
{
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Fever[0] = new Animation();
	m_Fever[0]->Push(ResourceManager::GetInstance()->GetBitmap("Fever1.bmp"), m_MapSize.cx * 0.9f,m_MapSize.cy * 0.05f);

	m_Fever[1] = new Animation();
	m_Fever[1]->Push(ResourceManager::GetInstance()->GetBitmap("Fever2.bmp"), m_MapSize.cx * 0.9f, m_MapSize.cy * 0.05f);

	m_Fever[2] = new Animation();
	m_Fever[2]->Push(ResourceManager::GetInstance()->GetBitmap("Fever3.bmp"), m_MapSize.cx * 0.9f, m_MapSize.cy * 0.05f);

	m_Fever[3] = new Animation();
	m_Fever[3]->Push(ResourceManager::GetInstance()->GetBitmap("ColoredPaperTimeBar.bmp"), m_MapSize.cx * 0.9f, m_MapSize.cy * 0.05f);

	m_FeverEffect = new Animation();
	m_FeverEffect->Push(ResourceManager::GetInstance()->GetBitmap("FeverEffect3.bmp"), m_MapSize.cx , m_MapSize.cy);

	isFeverEffect = false;
	isFever = false;

	m_Gage = 0;
	m_GageDelay = 0;
	m_EffectDelay = 0;
	m_GageDown = 0;
	m_HitOffset = 0;
	m_HitGageDown = 0;
}

void Fever::Update(float eftime)
{
	m_GageDelay += eftime;

	if (m_Gage > 100)
	{
		m_EffectDelay += eftime;
		if (m_EffectDelay >= 0.1f)
		{
			m_EffectDelay = 0;
			isFeverEffect = !isFeverEffect;
		}
	}
	else
	{
		isFeverEffect = false;	
		m_EffectDelay = 0;
	}

	if (isFever)
	{
		m_EffectDelay += 0;

		if (m_GageDelay > 5.0f)
		{
			SceneManager::GetInstance()->SendToScene(NOMAL);
			isFever = false;
			m_Gage = 0;
			m_GageDelay = 0;
		}
		return;
	}
	else
	{
		
		if (m_HitOffset > 0)
		{
			m_HitGageDown += eftime;
			if (m_HitGageDown > 0.1f)
			{
				m_HitGageDown = 0;
				m_HitOffset--;
			}
		}
		else
		{
			m_Gage = 0;
		}
	}

	if (m_GageDelay > 0.2f)
	{
		m_GageDelay = 0;

		if (m_Gage > 0)
		{
			m_Gage -= m_GageDown;
		}
	}
}

void Fever::Set(int delay)
{
	m_GageDown = delay;
}

void Fever::Draw(HDC hdc)
{

	if (isFever)
	{
		m_Fever[3]->Draw(hdc, m_MapSize.cx *0.04f, m_MapSize.cy *0.08f);
	}
	else
	{
		if (m_Gage > 0)
		{
			m_Fever[0]->Draw(hdc, m_MapSize.cx *0.04f, m_MapSize.cy *0.08f, SetLimit(0));
		}
		if (m_Gage > 100)
		{
			m_Fever[1]->Draw(hdc, m_MapSize.cx *0.04f, m_MapSize.cy *0.08f, SetLimit(1));
		}
		if (m_Gage > 200)
		{
			m_Fever[2]->Draw(hdc, m_MapSize.cx *0.04f, m_MapSize.cy *0.08f, SetLimit(2));
		}
	}

	if (isFeverEffect)
	{
		m_FeverEffect->Draw(hdc, 0, m_MapSize.cy *0.01f);
	}

}

void Fever::Up()
{
	m_Gage += 20;
	m_HitOffset = 50;

	if (m_Gage > 300)
	{
		isFever = true;
		SceneManager::GetInstance()->SendToScene(SUPER_FEVER);
	}
	else if (m_Gage > 100)
	{
		m_EffectDelay = 0;
		SceneManager::GetInstance()->SendToScene(FEVER);
	}
	else
	{
		SceneManager::GetInstance()->SendToScene(NOMAL);
	}
}

void Fever::Down()
{
	if (!isFever)
	{
		m_Gage -= 60;
		
		if (m_Gage < 100)
		{
			m_EffectDelay = 0;
			SceneManager::GetInstance()->SendToScene(NOMAL);
		}
		if (m_Gage < 0)
		{
			m_Gage = 0;
			m_GageDelay = 0;
		}
	}
}

string Fever::CollisionCheck(RECT * rect, string tag, int code)
{
	return string();
}

int Fever::SetLimit(int offset)
{
	if (m_Gage  > (100 * offset) + 100)
	{
		return 100;
	}
	else
	{
		return m_Gage - (100 * offset);
	}
}

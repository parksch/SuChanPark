#include "TimeManager.h"

TimeManager* TimeManager::m_pThis = nullptr;

void TimeManager::Init()
{
	m_nFPS = 60;
	m_fElapseTime = 0;
	m_dwCurTime = GetTickCount();
	m_dwLastTime = GetTickCount();
}

bool TimeManager::Update()
{
	m_dwCurTime = GetTickCount();

	if (m_dwCurTime - m_dwLastTime < 1000 / m_nFPS)
	{
		return false;
	}

	m_fElapseTime = (m_dwCurTime - m_dwLastTime) / 1000.0f;
	m_dwLastTime = GetTickCount();
	return true;
}

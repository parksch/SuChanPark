#pragma once
#include <Windows.h>
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
public:
	TimeManager() {};
	~TimeManager() {};
	void Init();
	bool Update();
	inline float GetElipseTime()
	{
		return m_fElapseTime;
	}
private:
	int					m_nFPS;
	DWORD				m_dwLastTime;
	DWORD				m_dwCurTime;
	float				m_fElapseTime;
};


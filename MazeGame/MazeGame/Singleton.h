#pragma once
#include "Macro.h"

template <class T>
class Singleton
{
public:
	static T* GetInstacne()
	{
		if (m_Instance == NULL)
		{
			m_Instance = new T;
		}

		return m_Instance;
	}

	static void DestoryInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}

protected:
	Singleton() {};
	virtual ~Singleton() {};
private:
	static T* m_Instance;
};

template<class T>T* Singleton<T>::m_Instance = 0;
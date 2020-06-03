#pragma once
#include "Macro.h"

template <typename T>
class Singleton
{
public:
	Singleton() {};
	virtual ~Singleton() {};
	
	static T* GetInstance()
	{
		if (m_This == NULL)
		{
			m_This = new T;
		}
		return m_This;
	}

	static void DestoryInstance()
	{
		if (m_This)
		{
			delete m_This;
			m_This = NULL;
		}
	}
private:
	static 	T* m_This;
};

template <typename T> T* Singleton<T>::m_This = 0;
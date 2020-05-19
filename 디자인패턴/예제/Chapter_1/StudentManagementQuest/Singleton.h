#pragma once
#include"iostream"

template<typename T>
class Singleton
{
private:
	static T* m_hThis;
protected:
	Singleton()
	{

	};
	virtual ~Singleton()
	{

	};
public:
	static T* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new T;
		return m_hThis;
	}

	static void DestroyInstance()
	{
		if (m_hThis)
		{
			delete m_hThis;
			m_hThis = NULL;
		}
	}
};

template <typename T> T* Singleton<T>::m_hThis = 0;
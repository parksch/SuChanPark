#pragma once

template <class T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (m_pThis == nullptr)
		{
			m_pThis = new T();
		}

		return m_pThis;
	}

	static void DestoryInstance()
	{
		if (m_pThis)
		{
			delete m_pThis;
			m_pThis = nullptr;
		}
	}

	Singleton() {};
	virtual ~Singleton() {};
private:
	static T* m_pThis;
};

template<class T> T* Singleton<T>::m_pThis = nullptr;

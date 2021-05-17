#include "CollisionManager.h"

CollisionManager* CollisionManager::m_pThis = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	Clear();
}

void CollisionManager::RegisterObject(Object * object)
{
	m_Objects.push_back(object);
}

void CollisionManager::Clear()
{
	vector<Object*>().swap(m_Objects);
}

string CollisionManager::CollisionCheck(RECT * rect, string tag, int code)
{
	string result;

	for (int i = 0; i < m_Objects.size(); i++)
	{
		result = m_Objects[i]->CollisionCheck(rect, tag, code);
		if (result != "Non")
		{
			return result;
		}
	}

	return "Non";
}

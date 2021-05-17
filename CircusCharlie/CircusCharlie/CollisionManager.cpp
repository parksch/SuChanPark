#include "CollisionManager.h"

CollisionManager* CollisionManager::m_pThis = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	Clear();
}

void CollisionManager::Clear()
{
	vector<Object*>().swap(coll);
}

void CollisionManager::Push(Object * object)
{
	coll.push_back(object);
}

string CollisionManager::CollisionCheck(Object* object, RECT rect)
{
	for (int i = 0; i < coll.size(); i++)
	{
		if (object != coll[i])
		{
			string tag = coll[i]->CollisionCheck(rect);

			if (tag != "Non")
			{
				return tag;
			}
		}
	}

	return "non";
}



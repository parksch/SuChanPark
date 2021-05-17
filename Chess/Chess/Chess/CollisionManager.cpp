#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	std::vector<ChessPiece*>().swap(objects);
}

void CollisionManager::Push(ChessPiece * object)
{
	objects.push_back(object);
}

ChessPiece * CollisionManager::MouseClickCheck(POINT point)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (PtInRect(&objects[i]->GetBox(), point))
		{
			return objects[i];
		}
	}

	return NULL;

}

ChessPiece * CollisionManager::CollisionCheck(POINT point)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetState() != OVER && objects[i]->GetPos().x == point.x && objects[i]->GetPos().y == point.y)
		{
			return objects[i];
		}
	}

	return NULL;
}

void CollisionManager::Erase(ChessPiece * piece)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (piece->GetID() == objects[i]->GetID() && piece->GetPos().x == objects[i]->GetPos().x && piece->GetPos().y == objects[i]->GetPos().y)
		{
			objects.erase(objects.begin() + i);
			break;
		}
	}
}

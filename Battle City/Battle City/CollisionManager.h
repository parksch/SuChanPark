#pragma once
#include "Singleton.h"
#include "Object.h"
#include <vector>
using namespace std;

class CollisionManager : public Singleton<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();
	void RegisterObject(Object *object);
	void Clear();
	string CollisionCheck(RECT *rect, string tag, int code);
private:
	vector<Object*> m_Objects;
};


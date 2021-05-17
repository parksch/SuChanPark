#pragma once
#include <vector>
#include "Singleton.h"
#include "Object.h"
using namespace std;

class CollisionManager : public Singleton<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();
	void Clear();
	void Push(Object* object);
	string CollisionCheck(Object* object,RECT rect);
 private:
	vector<Object*> coll;
};


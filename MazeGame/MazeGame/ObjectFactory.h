#pragma once
#include "Singleton.h"
#include "Object.h"
#include "Player.h"
#include "Door.h"

class ObjectFactory : public Singleton<ObjectFactory>
{
public:
	ObjectFactory() {};
	~ObjectFactory() {};
	Object* Create(int code,int x,int y);
};


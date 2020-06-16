#include "ObjectFactory.h"

ObjectFactory* ObjectFactory::m_Instance = NULL;

Object * ObjectFactory::Create(int code, int x, int y)
{
	switch (code)
	{
	case PLAYER:
		return new Player(code, x, y);
	case DOOR:
		return new Door(code, x, y);
	case BOSS:
		return new Boss(code, x, y);
	default:
		break;
	}
}

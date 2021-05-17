#pragma once
#include <Windows.h>
#include <string>
using namespace std;
class Object
{
public:
	Object() {};
	virtual ~Object() {};
	virtual void Draw(HDC hdc) = 0;
	virtual string CollisionCheck(RECT *rect, string tag, int code) = 0;
};
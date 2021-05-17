#pragma once
#include <Windows.h>
#include <list>
#include <map>
#include "Singleton.h"
#include "Effect.h"
using namespace std;

class EffectManager : public Singleton<EffectManager>
{
public:
	EffectManager();
	~EffectManager();
	void Register(Effect* effect, string code);
	void Create(string str, POINT pos);
	void Update(float eTime);
	void Draw(HDC hdc);
	void Check();
	void Clear();
private:
	map<string, Effect*> m_Effects;
	list<Effect*> m_PlayList;
};


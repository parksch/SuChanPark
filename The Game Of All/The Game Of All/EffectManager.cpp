#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	Clear();
}

void EffectManager::Register(Effect * effect, string code)
{
	m_Effects.insert(make_pair(code, effect));
}

void EffectManager::Create(string str, POINT pos)
{
	Effect *effect = (m_Effects.find(str)->second)->Create();
	effect->Set(pos);
	m_PlayList.push_back(effect);
}

void EffectManager::Update(float eTime)
{
	for (list<Effect*>::iterator i = m_PlayList.begin(); i != m_PlayList.end(); i++)
	{
		(*i)->Update(eTime);
	}
}

void EffectManager::Draw(HDC hdc)
{
	for (list<Effect*>::iterator i = m_PlayList.begin(); i != m_PlayList.end(); i++)
	{
		(*i)->Draw(hdc);
	}
}

void EffectManager::Check()
{
	for (list<Effect*>::iterator i = m_PlayList.begin(); i != m_PlayList.end();)
	{

		if ((*i)->getOver())
		{
			delete (*i);
			i = m_PlayList.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void EffectManager::Clear()
{
	for (list<Effect*>::iterator i = m_PlayList.begin(); i != m_PlayList.end();)
	{
		delete (*i); 
		i = m_PlayList.erase(i);
	}

	m_Effects.clear();
}

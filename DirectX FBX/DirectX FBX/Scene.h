#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Scene
{
public:
	virtual void Init(LPDIRECT3DDEVICE9 device, HWND hWnd) = 0;
	virtual void Release() = 0;
	virtual void Render() = 0;
	virtual bool Input(float curtime) = 0;
	virtual bool Update(float curtime) = 0;
};


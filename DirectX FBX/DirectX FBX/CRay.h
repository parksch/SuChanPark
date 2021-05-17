#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class cRay
{
public:
	cRay();
	~cRay();
public:

	typedef	struct MyStruct
	{
		D3DXVECTOR3 orign;
		D3DXVECTOR3 direction;

	}Ray, *LPRAY;

private:

	LPRAY m_cRay;

public:
	LPRAY InitRay(D3DXMATRIXA16 *matProj, D3DXMATRIXA16 *matView,POINT pt,LPDIRECT3DDEVICE9 device);
	bool destoryRay();
private:
	void TransformRay(LPRAY pRay, D3DXMATRIXA16 *pMatrix);

};


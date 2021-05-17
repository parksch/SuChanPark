#pragma once
#include <fbxsdk.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Model.h"

#define BOX_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos;
	DWORD color;
};

class Box
{
public:
	void Init(FLOAT horizontal, FLOAT vertical, FLOAT height, LPDIRECT3DDEVICE9 device);
	void Render(LPDIRECT3DDEVICE9 device, D3DXMATRIX& worldViewProj);
	bool Collision(D3DXVECTOR3 start, D3DXVECTOR3 dir);
private:

	CUSTOMVERTEX vertices[8];
	MYINDEX indices[12];
	D3DXVECTOR3 size;
	D3DXVECTOR3 m_pos;
	D3DXMATRIXA16 m_MatWorld;
	D3DXMATRIXA16 m_MatTM;
	D3DXMATRIXA16 m_MatS;
	LPDIRECT3DVERTEXBUFFER9	pVB = NULL;
	LPDIRECT3DINDEXBUFFER9	pIB = NULL;
};


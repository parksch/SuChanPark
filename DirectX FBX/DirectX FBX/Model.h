#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct MYINDEX
{
	WORD _0, _1, _2;
};

struct Vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 uv;
};

struct Parts
{
	int vertexCount = 0;
	int polyCount = 0;

	LPDIRECT3DTEXTURE9      pDiffuseTexture = NULL;
	LPDIRECT3DTEXTURE9      pNormalTexture = NULL;
	LPDIRECT3DTEXTURE9      pSpecularTexture = NULL;

	std::vector< MYINDEX>	 myindex;
	std::vector<UINT>		 indices;
	std::vector< Vertex>     vertices;
};

class Model
{
public:
	Model();
	~Model();
	void Input();
	bool SetGeometry(LPDIRECT3DDEVICE9 device);
	void Render(LPDIRECT3DDEVICE9 device, D3DXMATRIX& worldViewProj);
	Parts* getPartsP() { return &m_Parts; }
	void Release();
private:

	LPDIRECT3DVERTEXBUFFER9	pVB = NULL;
	LPDIRECT3DINDEXBUFFER9	pIB = NULL;

	Parts m_Parts;
};


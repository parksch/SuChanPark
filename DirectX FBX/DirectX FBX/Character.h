#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Model.h"
#include "Camera.h"
#include "Box.h"

class Character
{
public:
	Character();
	~Character();
	bool Collision(D3DXVECTOR3 pos, D3DXVECTOR3 direction);
	void SetPos(D3DXVECTOR3 pos);
	void Init(Camera *camera, Model* model, LPDIRECT3DDEVICE9 device);
	void Render(LPDIRECT3DDEVICE9 device, D3DXMATRIX& worldViewProj);
	void MouseMove(LPDIRECT3DDEVICE9 device, HWND hWnd);
	void MoveLocalZ(FLOAT dist);
	void MoveLocalX(FLOAT dist);
private:
	D3DXVECTOR3		m_pos;
	Box		*m_Box;
	Camera *m_Camera;
	Model *m_model;
	FLOAT m_RotX;
	FLOAT m_RotY;
	FLOAT m_MouseX;
	FLOAT m_MouseY;

	D3DXMATRIXA16 m_world;
	D3DXMATRIXA16 m_TM;
	D3DXMATRIXA16 m_R;
};
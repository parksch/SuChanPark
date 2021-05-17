#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
public:
	Camera();
	~Camera();
	void MoveLocalZ(FLOAT dist);
	void MoveLocalX(FLOAT dist);
	void Rotate(LPDIRECT3DDEVICE9 device, HWND hWnd);
	void LookAtView(LPDIRECT3DDEVICE9 device);
	D3DXMATRIXA16* RotateLocalY(FLOAT angle, D3DXVECTOR3 pos);
	D3DXMATRIXA16*	SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);
	D3DXMATRIXA16* getProj() { return &m_matProj; }
	D3DXMATRIXA16* getView() { return &m_matView; }
private:
	D3DXMATRIXA16* RotateLocalY(FLOAT angle);
	D3DXMATRIXA16* RotateLocalX(FLOAT angle);
private:

	DWORD m_MouseX;
	DWORD m_MouseY;

	D3DXMATRIXA16 matWorld;

	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookat;
	D3DXVECTOR3		m_vUp;

	D3DXVECTOR3		m_vView;
	D3DXVECTOR3		m_vCross;

	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matBill;
	D3DXMATRIXA16	m_matProj;

};


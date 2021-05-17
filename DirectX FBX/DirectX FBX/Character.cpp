#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
	delete m_Box;
}

bool Character::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 direction)
{
	return m_Box->Collision(pos, direction);
}

void Character::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	D3DXMatrixTranslation(&m_TM, m_pos.x, m_pos.y, m_pos.z);
}

void Character::Init(Camera *camera, Model* model, LPDIRECT3DDEVICE9 device)
{
	m_Camera = camera;
	m_model = model;
	m_Box = new Box();
	m_Box->Init(30, 30, 85,device);
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_MouseX = 0;
	m_MouseY = 0;
	m_RotX = 0;
	D3DXMatrixIdentity(&m_TM);
	D3DXMatrixIdentity(&m_R);

}

void Character::Render(LPDIRECT3DDEVICE9 device, D3DXMATRIX & worldViewProj)
{
	m_world = m_R * m_TM * worldViewProj;

	m_model->Render(device, m_world);
	m_Box->Render(device, m_world);
}

void Character::MouseMove(LPDIRECT3DDEVICE9 device, HWND hWnd)
{
	POINT pt;
	FLOAT fdelta = 0.001f;

	GetCursorPos(&pt);
	int dx = pt.x - m_MouseX;
	int dy = pt.y - m_MouseY;
	m_RotX += dx * fdelta;
	m_RotY += dy * 0.3f;

	if (m_RotY > 150)
	{
		m_RotY = 150;
	}
	else if (m_RotY < -50)
	{
		m_RotY = -50;
	}

	D3DXMatrixRotationY(&m_R, m_RotX);


	RECT	rc;
	GetClientRect(hWnd, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
	m_MouseX = pt.x;
	m_MouseY = pt.y;

	D3DXVECTOR3 vEyePt(0.0f, 330.0f + m_RotY, 300.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 270.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 newEye;
	D3DXVECTOR3 newLookat;

	D3DXVec3TransformCoord(&newEye, &vEyePt, &m_R);
	D3DXVec3TransformCoord(&newLookat, &vLookatPt, &m_R);

	newEye -= m_pos;
	newLookat -= m_pos;


	m_Camera->SetView(&newEye, &newLookat, &vUpVec);
}

void Character::MoveLocalZ(FLOAT dist)
{
	D3DXVECTOR3 vec(0, 0, 0);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(0, 0, dist), &m_R);
	m_pos += vec;

	D3DXMatrixTranslation(&m_TM, m_pos.x, m_pos.y, m_pos.z);
}

void Character::MoveLocalX(FLOAT dist)
{
	D3DXVECTOR3 vec(0, 0, 0);

	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(dist, 0, 0), &m_R);
	m_pos += vec;

	D3DXMatrixTranslation(&m_TM, m_pos.x, m_pos.y, m_pos.z);
}

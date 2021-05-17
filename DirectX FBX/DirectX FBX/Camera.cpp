#include "Camera.h"

Camera::Camera()
{
	D3DXVECTOR3	eye(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	lookat(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3	up(0.0f, 1.0f, 0.0f);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matBill);
	SetView(&eye, &lookat, &up);

	POINT	pt;
	GetCursorPos(&pt);
	m_MouseX = pt.x;
	m_MouseY = pt.y;
}

Camera::~Camera()
{
}

void Camera::MoveLocalZ(FLOAT dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vView);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	SetView(&vNewEye, &vNewDst, &m_vUp);
}

void Camera::MoveLocalX(FLOAT dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vCross);

	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	SetView(&vNewEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16* Camera::RotateLocalY(FLOAT angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vCross, angle);

	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);
	vNewDst += m_vEye;

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

D3DXMATRIXA16* Camera::RotateLocalX(FLOAT angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &D3DXVECTOR3(0, 1, 0), angle);

	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);
	vNewDst += m_vEye;

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

void Camera::Rotate(LPDIRECT3DDEVICE9 device, HWND hWnd)
{
	POINT pt;
	FLOAT fdelta = 0.001f;

	GetCursorPos(&pt);
	int dx = pt.x - m_MouseX;
	int dy = pt.y - m_MouseY;

	RotateLocalY(dy * fdelta);
	RotateLocalX(dx * fdelta);

	D3DXMATRIXA16*	pmatView = &m_matView;		// 카메라 행렬을 얻는다.
	device->SetTransform(D3DTS_VIEW, pmatView);

	RECT	rc;
	GetClientRect(hWnd, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
	m_MouseX = pt.x;
	m_MouseY = pt.y;

}

D3DXMATRIXA16 * Camera::SetView(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvLookat, D3DXVECTOR3 * pvUp)
{
	m_vEye = *pvEye;
	m_vLookat = *pvLookat;
	m_vUp = *pvUp;
	D3DXVec3Normalize(&m_vView, &(m_vLookat - m_vEye));
	D3DXVec3Cross(&m_vCross, &m_vUp, &m_vView);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookat, &m_vUp);
	D3DXMatrixInverse(&m_matBill, NULL, &m_matView);
	m_matBill._41 = 0.0f;
	m_matBill._42 = 0.0f;
	m_matBill._43 = 0.0f;

	return &m_matView;
}

void Camera::LookAtView(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	device->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookat, &m_vUp);
	device->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 3, 1.0f, 1.0f, 2000);
	device->SetTransform(D3DTS_PROJECTION, &m_matProj);

}

D3DXMATRIXA16* Camera::RotateLocalY(FLOAT angle, D3DXVECTOR3 pos)
{
	D3DXMATRIXA16 matRot;
	D3DXVECTOR3 vEyePt(0.0f, 250.0f, 300.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 80.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixRotationAxis(&matRot, &D3DXVECTOR3(pos - vEyePt), angle);


	D3DXVec3TransformCoord(&vEyePt, &vEyePt, &matRot);
	D3DXVec3TransformCoord(&vLookatPt, &vLookatPt, &matRot);

	SetView(&vEyePt, &vLookatPt, &vUpVec);

	return nullptr;
}


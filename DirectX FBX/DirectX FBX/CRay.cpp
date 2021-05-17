#include "CRay.h"
#include "FBXModelLoader.h"

cRay::cRay()
{
	m_cRay = NULL;
}

cRay::~cRay()
{
}

cRay::LPRAY cRay::InitRay(D3DXMATRIXA16 *matProj, D3DXMATRIXA16 *matView, POINT pt, LPDIRECT3DDEVICE9 device)
{
	if (m_cRay == NULL)
	{
		m_cRay = new Ray();
	}

	FLOAT fx = 0.0f;
	FLOAT fy = 0.0f;

	D3DVIEWPORT9 vp;
	device->GetViewport(&vp);

	fx = ((2.0f * pt.x) / vp.Width) - 1.0f;
	fy = ((-2.0f * pt.y) / vp.Height) + 1.0f;

	fx = fx / matProj->_11;
	fy = fy / matProj->_22;

	m_cRay->orign = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cRay->direction = D3DXVECTOR3(fx, fy, 1.0f);

	D3DXMATRIXA16 matViewInverse;
	D3DXMatrixInverse(&matViewInverse, NULL, matView);

	TransformRay(m_cRay, &matViewInverse);

	return m_cRay;
}

bool cRay::destoryRay()
{
	if (m_cRay != NULL)
	{
		delete m_cRay;
		return true;
	}

	return false;
}

void cRay::TransformRay(LPRAY pRay, D3DXMATRIXA16 * pMatrix)
{
	if (pRay != NULL && pMatrix != NULL)
	{
		D3DXVec3TransformCoord(&pRay->orign, &pRay->orign, pMatrix);

		D3DXVec3TransformNormal(&pRay->direction, &pRay->direction, pMatrix);

		D3DXVec3Normalize(&pRay->direction, &pRay->direction);
	}
}

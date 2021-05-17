#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Input()
{

}

bool Model::SetGeometry(LPDIRECT3DDEVICE9 device)
{
	void *verticesPtr;
	void *indicesPtr;
	long vertexSize = m_Parts.vertices.size() * sizeof(Vertex);
	long indexSize = m_Parts.myindex.size() * sizeof(MYINDEX);

	if (FAILED(device->CreateIndexBuffer(
		indexSize,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&pIB,
		NULL)))
		return false;

	if (FAILED(device->CreateVertexBuffer(
		vertexSize,
		0,
		D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT,
		&pVB,
		NULL)))
		return false;

	if (FAILED(pIB->Lock(
		0,
		indexSize,
		(void**)&indicesPtr,
		0)))
		return false;

	if (FAILED(pVB->Lock(
		0,
		vertexSize,
		(void**)&verticesPtr,
		0)))
		return false;

	memcpy(indicesPtr, m_Parts.myindex.data(), indexSize);
	memcpy(verticesPtr, m_Parts.vertices.data(), vertexSize);

	pVB->Unlock();
	pIB->Unlock();

	return true;
}

void Model::Render(LPDIRECT3DDEVICE9 device, D3DXMATRIX& worldViewProj)
{
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	device->SetTexture(0, m_Parts.pDiffuseTexture);  /// 0번 텍스쳐 스테이지에 텍스쳐 고정(벽면)
	device->SetTexture(1, m_Parts.pSpecularTexture);
	device->SetTexture(2, m_Parts.pNormalTexture);

	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
	device->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);

	//device->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//device->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//device->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);

	device->SetTransform(D3DTS_WORLD, &worldViewProj);
	device->SetStreamSource(0, pVB, 0, sizeof(Vertex));
	device->SetIndices(pIB);
	device->SetFVF(D3DFVF_CUSTOMVERTEX);

	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_Parts.vertexCount, 0, m_Parts.polyCount);


}

void Model::Release()
{
	if (m_Parts.pDiffuseTexture != NULL)
		m_Parts.pDiffuseTexture->Release();

	if (m_Parts.pNormalTexture != NULL)
		m_Parts.pNormalTexture->Release();

	if (m_Parts.pSpecularTexture != NULL)
		m_Parts.pSpecularTexture->Release();

	if (pIB != NULL)
		pIB->Release();

	if (pVB != NULL)
		pVB->Release();

}

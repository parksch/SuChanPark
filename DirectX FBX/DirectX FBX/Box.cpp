#include "Box.h"
#include "FBXModelLoader.h"

void Box::Init(FLOAT horizontal, FLOAT vertical, FLOAT height, LPDIRECT3DDEVICE9 device)
{
	size.x = horizontal;
	size.z = vertical;
	size.y = height;

	m_pos.x = 1;
	m_pos.y = height;
	m_pos.z = 1;

	D3DXMatrixIdentity(&m_MatS);
	D3DXMatrixIdentity(&m_MatTM);
	D3DXMatrixScaling(&m_MatS, horizontal, height, vertical);
	D3DXMatrixTranslation(&m_MatTM, 0, height, 0);
	
	// 상자(cube)를 랜더링하기 위해 8개의 정점 선언


	vertices[0] = { D3DXVECTOR3(-1, 1, 1), 0xffff0000 };	//v0
	vertices[1] = { D3DXVECTOR3(1, 1, 1), 0xff00ff00 };	//v1
	vertices[2] = { D3DXVECTOR3(1, 1,-1), 0xff0000ff };	//v2
	vertices[3] = { D3DXVECTOR3(-1, 1,-1), 0xffffff00 };	//v3
	vertices[4] = { D3DXVECTOR3(-1,-1, 1), 0xffff0000 };	//v4
	vertices[5] = { D3DXVECTOR3(1,-1, 1), 0xff00ff00 };	//v5
	vertices[6] = { D3DXVECTOR3(1,-1,-1), 0xff0000ff };	//v6
	vertices[7] = { D3DXVECTOR3(-1,-1,-1), 0xffffff00 };	//v7

	// 정점 버퍼를 생성한다.
	// 정점 구조체 3개를 저장할 메모리를 할당한다.
	// FVF를 지정하여 보관할 데이터의 형식을 지정한다.
	if (FAILED(device->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, BOX_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &pVB, NULL)))
		return;

	//정점의 버퍼를 값으로 채운다.
	//정점 버퍼의 Lock() 함수를 호출하여 포인터를 얻어온다.
	void* pVertices;

	if (FAILED(pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return;

	memcpy(pVertices, vertices, sizeof(vertices));

	pVB->Unlock();


	indices[0] = { 0, 1, 2 };
	indices[1] = { 0, 2, 3 };
	indices[2] = { 4, 5, 6 };
	indices[3] = { 4, 7, 6 };
	indices[4] = { 0, 3, 7 };
	indices[5] = { 0, 7, 4 };
	indices[6] = { 1, 5, 6 };
	indices[7] = { 1, 6, 2 };
	indices[8] = { 3, 2, 6 };
	indices[9] = { 3, 6, 7 };
	indices[10] = { 0, 4, 5 };
	indices[11] = { 0, 5, 1 };

	//인덱스 버퍼 생성
	//D3DFMT_INDEX16은 인덱스의 단위가 16비트라는 것.
	//MYINDEX 구조체에서 WORD형으로 선언으므로 D3DFMT_INDEX16을 사용한다.
	if (FAILED(device->CreateIndexBuffer(12 * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIB, NULL)))
		return;

	//인덱스 버퍼를 값으로 채운다.
	void* pIndices;
	//인덱스 버퍼의 Lock() 함수를 호출하여 포인터를 얻어와서 정보를 채운다.
	if (FAILED(pIB->Lock(0, sizeof(indices), (void**)&pIndices, 0)))
		return;

	memcpy(pIndices, indices, sizeof(indices));

	pIB->Unlock();
}

void Box::Render(LPDIRECT3DDEVICE9 device, D3DXMATRIX & worldViewProj)
{
	m_MatWorld = m_MatS * m_MatTM * worldViewProj;
	D3DXVec3TransformCoord(&m_pos, &D3DXVECTOR3(0, 40, 0), &worldViewProj);

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	device->SetTransform(D3DTS_WORLD, &m_MatWorld);
	device->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
	device->SetIndices(pIB);
	device->SetFVF(BOX_CUSTOMVERTEX);

	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

}

bool Box::Collision(D3DXVECTOR3 start, D3DXVECTOR3 dir)
{
	D3DXVECTOR3 pos[3];
	float u, v, t;
	bool collision = false;

	for (int i = 0; i < 12; i++)
	{
		pos[0] = vertices[indices[i]._0].pos;
		pos[1] = vertices[indices[i]._1].pos;
		pos[2] = vertices[indices[i]._2].pos;

		D3DXVec3TransformCoord(&pos[0], &pos[0], &m_MatWorld);
		D3DXVec3TransformCoord(&pos[1], &pos[1], &m_MatWorld);
		D3DXVec3TransformCoord(&pos[2], &pos[2], &m_MatWorld);


		if (D3DXIntersectTri(&pos[0], &pos[1], &pos[2], &start, &dir, &u, &v, &t))
		{
			collision = true;
		}
	}

	return collision;
}

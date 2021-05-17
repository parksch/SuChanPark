#include "GameScene.h"
#include "InputManager.h"
#include "FBXModelLoader.h"
#define PI 3.14159265358979f

GameScene::GameScene()
{
	isLoad = false;
	m_IB = NULL;
	m_VB = NULL;
	pDiffuseTexture = NULL;
}

GameScene::~GameScene()
{
}

void GameScene::Init(LPDIRECT3DDEVICE9 device, HWND hWnd)
{
	m_Device = device;
	m_hWnd = hWnd;
	m_Camera = new Camera;
	m_Character = new Character;
	FreeCameraMode = true;
	m_Character->Init(m_Camera, FBXModelLoader::GetInstance()->GetModel("maria.fbx"),m_Device);
	
	InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	InputManager::GetInstance()->RegistKeyCode(VK_RBUTTON);
	InputManager::GetInstance()->RegistKeyCode('W');
	InputManager::GetInstance()->RegistKeyCode('A');
	InputManager::GetInstance()->RegistKeyCode('S');
	InputManager::GetInstance()->RegistKeyCode('D');

	if (FAILED(m_Device->CreateVertexBuffer(100 * 100 * sizeof(Vertex),
		0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_VB, NULL))) {
		printf("hi");
	}
	 
	// Lock() �Լ��� ���� ���� ���ۿ� ������ ������ �� �ִ� �ּҰ��� ��´�.
	VOID *pVertexBuffer = nullptr;
	if (FAILED(m_VB->Lock(0, 100 * 100 * sizeof(Vertex), &pVertexBuffer, 0))) {
		printf("hi");
	}

	// ������ ��ǥ���� �Ҵ��ϴ� ������ �˰���
	// (0, 0, 0)�� ��ġ�� ������ �����߽����� �ϱ� ���� �۾�
	Vertex v;
	Vertex *pv = (Vertex *)pVertexBuffer;
	pV = pv;
	for (DWORD z = 0; z < 100; ++z) {
		for (DWORD x = 0; x < 100; ++x) {
			// ������ ��ǥ���� �����Ѵ�.
			v.pos.x = (float)x - 100 / 2.f;
			v.pos.y = 0.f;
			v.pos.z = -((float)z - 100 / 2.f);

			// ������ ���� ���͸� �����Ѵ�.
			v.normal.x = v.pos.x;
			v.normal.y = v.pos.y;
			v.normal.z = v.pos.z;
			D3DXVec3Normalize(&v.normal, &v.normal);

			// �ؽ�ó ������ ���� u, v ��ǥ���� �����Ѵ�.
			v.uv.x = (float)x / (100 - 1);
			v.uv.y = (float)z / (100 - 1);

			// ������ ���� ������ CUSTOMVERTEX��
			// ���� ���ۿ� �����Ѵ�.
			// ���� �� ���� ���� ��ġ�� ����Ű����
			// ������ ������ �����Ѵ�.(���� �������� ó��)
			*pv++ = v;
		}
	}

	// Lock() - Unlock()
	m_VB->Unlock();

	if (FAILED(m_Device->CreateIndexBuffer((100 - 1)*(100 - 1) * 2 * sizeof(MYINDEX),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_IB, NULL))) {
		printf("hi");
	}

	// �ε��� ���ۿ� ������ �ε����� �����ϴ� �˰���
	MYINDEX  i;
	MYINDEX *pi;
	if (FAILED(m_IB->Lock(0, (100 - 1)*(100 - 1) * 2 * sizeof(MYINDEX), (void**)&pi, 0)))
		printf("hi");
	pI = pi;

	for (DWORD z = 0; z < 100 - 1; z++) {
		for (DWORD x = 0; x < 100 - 1; x++) {

			// ���� �ε����� CW �������� �����ϰ� �ִ�.
			// ���� CW �������� �ø� ��带 �����ϸ� �ƹ��͵� �׷����� ���� ���̴�.
			// g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) �� ��� 
			// �׷����� ���� ����.

			// �»� ��ġ�� �ﰢ��
			i._0 = (z * 100 + x);
			i._1 = (z * 100 + x + 1);
			i._2 = ((z + 1) * 100 + x);
			// ������ ������ ���� ���� �ε��� ������ġ ����
			*pi++ = i;

			// ���� ��ġ�� �ﰢ��
			i._0 = ((z + 1) * 100 + x);
			i._1 = (z * 100 + x + 1);
			i._2 = ((z + 1) * 100 + x + 1);
			// ������ ������ ���� ���� �ε��� ������ġ ����
			*pi++ = i;
		}
	}
	// Lock() - Unlock()
	m_IB->Unlock();


	if (FAILED(D3DXCreateTextureFromFile(m_Device, "Objects/terrain.png", &pDiffuseTexture)))
		printf("hi");

	SetUpLight();
	SetUpCamera();

	isLoad = true;
}

void GameScene::Release()
{
	if (isLoad)
	{
		InputManager::GetInstance()->Clear();
		delete m_Camera;
		delete m_Character;
		m_cRay.destoryRay();

		if (m_IB != NULL)
		{
			m_IB->Release();
		}

		if (m_VB != NULL)
		{
			m_VB->Release();
		}

	}
}

void GameScene::Render()
{
	D3DXMATRIXA16 matWorld;
	

	m_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&m_matTMParent);
	D3DXMatrixIdentity(&m_matRParent);

	D3DXMatrixRotationYawPitchRoll(&m_matRParent, PI, 0.0f, 0);

	matWorld = m_matTMParent * m_matRParent;

	D3DXMatrixScaling(&scale, 10.0f, 0, 10.0f);

	m_Camera->LookAtView(m_Device);

	if (SUCCEEDED(m_Device->BeginScene()))
	{
		m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_Device->SetTexture(0, pDiffuseTexture);

		m_Device->SetTransform(D3DTS_WORLD, &scale);
		m_Device->SetStreamSource(0, m_VB, 0, sizeof(Vertex));
		m_Device->SetIndices(m_IB);
		m_Device->SetFVF(D3DFVF_CUSTOMVERTEX);

		m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 100 * 100, 0, (100 - 1)*(100 - 1) * 2);

		m_Character->Render(m_Device, matWorld);
		m_Device->EndScene();
	}

	m_Device->Present(NULL, NULL, NULL, NULL);
}

bool GameScene::Input(float curtime)
{
	if (!FreeCameraMode)
	{
		m_Character->MouseMove(m_Device, m_hWnd);
	}

	if (InputManager::GetInstance()->isKeyPress('W'))
	{
		if (FreeCameraMode)
		{
			m_Camera->MoveLocalZ(5.0f);
		}
		else
		{
			m_Character->MoveLocalZ(5.0f);
		}
	}

	if (InputManager::GetInstance()->isKeyPress('A'))
	{
		if (FreeCameraMode)
		{
			m_Camera->MoveLocalX(-5.0f);
		}
		else
		{
			m_Character->MoveLocalX(-5.0f);
		}
	}

	if (InputManager::GetInstance()->isKeyPress('S'))
	{
		if (FreeCameraMode)
		{
			m_Camera->MoveLocalZ(-5.0f);
		}
		else
		{
			m_Character->MoveLocalZ(-5.0f);
		}
	}

	if (InputManager::GetInstance()->isKeyPress('D'))
	{
		if (FreeCameraMode)
		{
			m_Camera->MoveLocalX(5.0f);
		}
		else
		{
			m_Character->MoveLocalX(5.0f);
		}
	}

	if (InputManager::GetInstance()->isKeyPress(VK_RBUTTON))
	{
		if (FreeCameraMode)
		{
			m_Camera->Rotate(m_Device, m_hWnd);
		}
	}

	if (InputManager::GetInstance()->isKeyDown(VK_LBUTTON))
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(m_hWnd, &point);

		cRay::LPRAY ray = m_cRay.InitRay(m_Camera->getProj(), m_Camera->getView(),point,m_Device);

		if (FreeCameraMode)
		{
			if (m_Character->Collision(ray->orign,ray->direction))
			{
				FreeCameraMode = false;
			}
			else
			{
				FLOAT u, v, t;
				D3DXVECTOR3 pos[4];
				pos[0] = { -500,0,-500 };
				pos[1] = {	500,0,-500 };
				pos[2] = { -500,0, 500 };
				pos[3] = {  500,0, 500 };

				if (D3DXIntersectTri(&pos[0], &pos[1], &pos[2], &ray->orign, &ray->direction, &u, &v, &t))
				{
					m_Character->SetPos(-(ray->orign + (ray->direction * t)));
				}

				if (D3DXIntersectTri(&pos[1], &pos[2], &pos[3], &ray->orign, &ray->direction, &u, &v, &t))
				{
					m_Character->SetPos(-(ray->orign + (ray->direction * t)));
				}

			}
		}
		else
		{
			FreeCameraMode = true;
		}

	}

	return true;
}

bool GameScene::Update(float curtime)
{
	return true;
}

void GameScene::SetUpLight()
{
	D3DMATERIAL9 mat;
	ZeroMemory(&mat, sizeof(D3DMATERIAL9));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 0.8f;
	mat.Diffuse.a = 1.0f;

	// Set the RGBA for ambient reflection.
	mat.Ambient.r = 1.0f;
	mat.Ambient.g = 1.0f;
	mat.Ambient.b = 0.8f;
	mat.Ambient.a = 1.0f;

	// Set the color and sharpness of specular highlights.
	mat.Specular.r = 1.0f;
	mat.Specular.g = 1.0f;
	mat.Specular.b = 1.0f;
	mat.Specular.a = 1.0f;
	mat.Power = 50.0f;

	// Set the RGBA for emissive color.
	mat.Emissive.r = 0.0f;
	mat.Emissive.g = 0.0f;
	mat.Emissive.b = 0.0f;
	mat.Emissive.a = 0.0f;

	m_Device->SetMaterial(&mat);

	//���� ����
	D3DXVECTOR3 vecDir;
	//���⼺ ����(directional light)�� ���� ���� ����
	//���� ����ü
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	//������ Ȯ�걤 ������ ��⸦ �����Ѵ�.
	//������ ������ �����Ѵ�(����Ʈ ����Ʈ, ���̷��� ����Ʈ, ����Ʈ ����Ʈ)
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	//������ ���� ����
	vecDir = D3DXVECTOR3(-1.0f, 0, 1.0f);

	//������ ������ ���� ���ͷ� �����.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f; // ������ �ٴٸ� �� �ִ� �ִ�Ÿ�
	m_Device->SetLight(0, &light); // ����̽��� ���� 0���� ��ġ
	m_Device->LightEnable(0, TRUE); // ���� 0���� Ȱ��ȭ �Ѵ�.
	m_Device->SetRenderState(D3DRS_LIGHTING, TRUE);// ���� ������ Ȱ��ȭ �Ѵ�.

	//ȯ�� ������ �� ����
	m_Device->SetRenderState(D3DRS_AMBIENT, 0x00909090);
}

void GameScene::SetUpCamera()
{
	D3DXVECTOR3 vEyePt(0.0f, 280.0f, 300.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 80.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	m_Camera->SetView(&vEyePt, &vLookatPt, &vUpVec);
}

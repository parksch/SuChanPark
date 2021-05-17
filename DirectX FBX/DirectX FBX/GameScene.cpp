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
	 
	// Lock() 함수를 통해 정점 버퍼에 정점을 저장할 수 있는 주소값을 얻는다.
	VOID *pVertexBuffer = nullptr;
	if (FAILED(m_VB->Lock(0, 100 * 100 * sizeof(Vertex), &pVertexBuffer, 0))) {
		printf("hi");
	}

	// 정점의 좌표값을 할당하는 간단한 알고리즘
	// (0, 0, 0)의 위치를 지형의 무게중심으로 하기 위한 작업
	Vertex v;
	Vertex *pv = (Vertex *)pVertexBuffer;
	pV = pv;
	for (DWORD z = 0; z < 100; ++z) {
		for (DWORD x = 0; x < 100; ++x) {
			// 정점의 좌표값을 설정한다.
			v.pos.x = (float)x - 100 / 2.f;
			v.pos.y = 0.f;
			v.pos.z = -((float)z - 100 / 2.f);

			// 정점의 수직 벡터를 설정한다.
			v.normal.x = v.pos.x;
			v.normal.y = v.pos.y;
			v.normal.z = v.pos.z;
			D3DXVec3Normalize(&v.normal, &v.normal);

			// 텍스처 맵핑을 위한 u, v 좌표값을 설정한다.
			v.uv.x = (float)x / (100 - 1);
			v.uv.y = (float)z / (100 - 1);

			// 설정한 값을 가지는 CUSTOMVERTEX를
			// 정점 버퍼에 저장한다.
			// 저장 후 다음 저장 위치를 가리키도록
			// 포인터 연산을 수행한다.(후위 연산으로 처리)
			*pv++ = v;
		}
	}

	// Lock() - Unlock()
	m_VB->Unlock();

	if (FAILED(m_Device->CreateIndexBuffer((100 - 1)*(100 - 1) * 2 * sizeof(MYINDEX),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_IB, NULL))) {
		printf("hi");
	}

	// 인덱스 버퍼에 저정할 인덱스를 생성하는 알고리즘
	MYINDEX  i;
	MYINDEX *pi;
	if (FAILED(m_IB->Lock(0, (100 - 1)*(100 - 1) * 2 * sizeof(MYINDEX), (void**)&pi, 0)))
		printf("hi");
	pI = pi;

	for (DWORD z = 0; z < 100 - 1; z++) {
		for (DWORD x = 0; x < 100 - 1; x++) {

			// 정점 인덱스를 CW 방향으로 설정하고 있다.
			// 만약 CW 방향으로 컬링 모드를 설정하면 아무것도 그려지지 않을 것이다.
			// g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) 인 경우 
			// 그려지는 것이 없다.

			// 좌상 위치의 삼각형
			i._0 = (z * 100 + x);
			i._1 = (z * 100 + x + 1);
			i._2 = ((z + 1) * 100 + x);
			// 포인터 연산을 통해 다음 인덱스 저장위치 설정
			*pi++ = i;

			// 우하 위치의 삼각형
			i._0 = ((z + 1) * 100 + x);
			i._1 = (z * 100 + x + 1);
			i._2 = ((z + 1) * 100 + x + 1);
			// 포인터 연산을 통해 다음 인덱스 저장위치 설정
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

	//광원 설정
	D3DXVECTOR3 vecDir;
	//방향성 광원(directional light)이 향한 빛의 방향
	//광원 구조체
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	//광원의 확산광 색깔의 밝기를 지정한다.
	//광원의 종류를 설정한다(포인트 라이트, 다이렉션 라이트, 스포트 라이트)
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	//광원의 방향 설정
	vecDir = D3DXVECTOR3(-1.0f, 0, 1.0f);

	//광원의 방향을 단위 벡터로 만든다.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f; // 광원이 다다를 수 있는 최대거리
	m_Device->SetLight(0, &light); // 디바이스에 광원 0번을 설치
	m_Device->LightEnable(0, TRUE); // 광원 0번을 활성화 한다.
	m_Device->SetRenderState(D3DRS_LIGHTING, TRUE);// 광원 설정을 활성화 한다.

	//환경 광원의 값 설정
	m_Device->SetRenderState(D3DRS_AMBIENT, 0x00909090);
}

void GameScene::SetUpCamera()
{
	D3DXVECTOR3 vEyePt(0.0f, 280.0f, 300.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 80.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	m_Camera->SetView(&vEyePt, &vLookatPt, &vUpVec);
}

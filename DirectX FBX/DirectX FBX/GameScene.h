#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Character.h"
#include "CRay.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void Init(LPDIRECT3DDEVICE9 device, HWND hWnd);
	void Release();
	void Render();
	bool Input(float curtime);
	bool Update(float curtime);
private:
	void SetUpLight();
	void SetUpCamera();
private:
	bool isLoad;
	bool FreeCameraMode;
	D3DXMATRIXA16 scale;
	MYINDEX* pI;
	Vertex* pV;
	cRay	   m_cRay;
	Camera    *m_Camera;
	Character *m_Character;
	LPDIRECT3DDEVICE9 m_Device;
	HWND m_hWnd;
	LPDIRECT3DTEXTURE9      pDiffuseTexture;
	LPDIRECT3DINDEXBUFFER9 m_IB;
	LPDIRECT3DVERTEXBUFFER9 m_VB;
	D3DXMATRIXA16			m_matTMParent;
	D3DXMATRIXA16			m_matRParent;
};


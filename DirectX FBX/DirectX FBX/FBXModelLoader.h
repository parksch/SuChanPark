#pragma once
#include <fbxsdk.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <map>
#include "Singleton.h"
#include "Model.h"
#include "Camera.h"

struct FBXFileNames
{
	FBXFileNames(std::string fbxname, std::string diffuse, std::string normal, std::string specular)
		: FBXName(fbxname), diffuseTexture(diffuse), normalTexture(normal), specularTexture(specular)
	{}
	std::string FBXName;
	std::string diffuseTexture;
	std::string normalTexture;
	std::string specularTexture;
};

class FBXModelLoader : public Singleton<FBXModelLoader>
{
public:
	FBXModelLoader();
	~FBXModelLoader();
	bool Init(LPDIRECT3DDEVICE9 device, HWND hWnd);
	void Release();
	bool Import();
	Model* GetModel(std::string strFileName);
private:
	void LoadNode(FbxNode* node, Model* model);
	void LoadMesh(FbxMesh* mesh, Model* model);
private:

	HWND m_hWnd;
	LPDIRECT3DDEVICE9 m_devicePtr;
	D3DXMATRIXA16			m_matTMParent;
	D3DXMATRIXA16			m_matRParent;
	FbxManager *m_Manager;
	FbxIOSettings *m_Ios;
	FbxImporter *m_Importer;
	std::vector<FBXFileNames> m_Names;
	std::map<std::string, Model*> m_Models;
};


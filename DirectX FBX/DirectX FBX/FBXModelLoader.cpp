#include "FBXModelLoader.h"

FBXModelLoader* FBXModelLoader::m_pThis = nullptr;

FBXModelLoader::FBXModelLoader()
{
	m_Manager = NULL;
	m_Ios = NULL;
	m_Importer = NULL;

	m_Names.push_back(FBXFileNames("maria.fbx", "maria.fbm/maria_diffuse.png", "maria.fbm/maria_normal.png", "maria.fbm/maria_specular.png"));
}

FBXModelLoader::~FBXModelLoader()
{
}

bool FBXModelLoader::Init(LPDIRECT3DDEVICE9 device, HWND hWnd)
{
	m_hWnd = hWnd;
	m_devicePtr = device;
	m_Manager = FbxManager::Create();
	m_Ios = FbxIOSettings::Create(m_Manager, IOSROOT);
	m_Manager->SetIOSettings(m_Ios);
	m_Importer = FbxImporter::Create(m_Manager, "");

	if (!Import())
		return false;

	return true;
}

void FBXModelLoader::Release()
{
	for (auto iter = m_Models.begin(); iter != m_Models.end(); iter++)
	{
		auto del = (*iter).second;
		delete del;
	}

	if (m_Ios != NULL)
	{
		m_Ios->Destroy();
	}

	if (m_Manager != NULL)
	{
		m_Manager->Destroy();
	}

}

bool FBXModelLoader::Import()
{
	for (int i = 0; i < m_Names.size(); i++)
	{
		std::string filePath = "Objects/";

		bool status = m_Importer->Initialize((filePath + m_Names[i].FBXName).c_str(), -1, m_Manager->GetIOSettings());

		if (!status)
			return false;

		FbxScene *scene;

		scene = FbxScene::Create(m_Manager, "scene");

		m_Importer->Import(scene);
		m_Importer->Destroy();

		FbxAxisSystem SceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
		FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);

		if (SceneAxisSystem != OurAxisSystem)
			OurAxisSystem.ConvertScene(scene);

		FbxGeometryConverter geometryConverter(m_Manager);
		geometryConverter.Triangulate(scene, true);

		FbxNode *rootNode = scene->GetRootNode();
		Model*model = new Model;

		LoadNode(rootNode, model);

		if (FAILED(D3DXCreateTextureFromFile(m_devicePtr, (filePath + m_Names[i].diffuseTexture).c_str(), &model->getPartsP()->pDiffuseTexture)))
			return false;

		if (FAILED(D3DXCreateTextureFromFile(m_devicePtr, (filePath + m_Names[i].normalTexture).c_str(), &model->getPartsP()->pNormalTexture)))
			return false;

		if (FAILED(D3DXCreateTextureFromFile(m_devicePtr, (filePath + m_Names[i].specularTexture).c_str(), &model->getPartsP()->pSpecularTexture)))
			return false;

		if (!model->SetGeometry(m_devicePtr))
			return false;

		m_Models.insert(make_pair(m_Names[i].FBXName,model));
		scene->Destroy();

	}

	return true;
}

Model * FBXModelLoader::GetModel(std::string strFileName)
{
	return m_Models.find(strFileName)->second;
}

void FBXModelLoader::LoadNode(FbxNode * node, Model * model)
{
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();

	if (nodeAttribute)
	{
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			LoadMesh(node->GetMesh(), model);
		}

		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{

		}
	}

	const int childCount = node->GetChildCount();

	for (int i = 0; i < childCount; i++)
		LoadNode(node->GetChild(i), model);
}

void FBXModelLoader::LoadMesh(FbxMesh * mesh, Model * model)
{
	bool allByControlPoint = true;
	int polygonCount = mesh->GetPolygonCount();

	Parts* parts = model->getPartsP();

	FbxVector4* controlPoints = mesh->GetControlPoints();
	FbxVector4 currentVertex;
	FbxVector4 currentNormal;
	FbxVector2 currentUV;

	FbxGeometryElement::EMappingMode normalMappingMode = mesh->GetElementNormal(0)->GetMappingMode();
	FbxGeometryElement::EMappingMode uvMappingMode = mesh->GetElementUV(0)->GetMappingMode();
	FbxLayerElementArrayTemplate<int>* materialIndice = &mesh->GetElementMaterial()->GetIndexArray();
	FbxGeometryElement::EMappingMode lMaterialMappingMode = mesh->GetElementMaterial()->GetMappingMode();

	FbxStringList uvNames;
	mesh->GetUVSetNames(uvNames);
	const char* uvName = NULL;

	if (uvNames.GetCount() != 0)
	{
		uvName = uvNames[0];
	}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 dxNormal;
	D3DXVECTOR2 uv;
	int normalIndex = 0;
	Vertex vertex;
	long  lVertexCount = 0;

	for (int i = 0; i < polygonCount; i++)
	{
		MYINDEX index;
		long materialIndex = 0;

		for (int j = 0; j < 3; j++)
		{

			int controlPointIndex = mesh->GetPolygonVertex(i, j);

			currentVertex = controlPoints[controlPointIndex];

			pos.x = (FLOAT)controlPoints[controlPointIndex].mData[0];
			pos.y = (FLOAT)controlPoints[controlPointIndex].mData[1];
			pos.z = (FLOAT)controlPoints[controlPointIndex].mData[2];
			vertex.pos = pos;

			mesh->GetPolygonVertexNormal(i, j, currentNormal);
			dxNormal = D3DXVECTOR3(
				static_cast<FLOAT>(currentNormal[0]),
				static_cast<FLOAT>(currentNormal[1]),
				static_cast<FLOAT>(currentNormal[2]));
			vertex.normal = dxNormal;

			bool unmappedUV;

			mesh->GetPolygonVertexUV(i, j, uvName, currentUV, unmappedUV);
			uv = D3DXVECTOR2(
				static_cast<float>(currentUV[0]),
				1.0f - static_cast<float>(currentUV[1])
			);
			vertex.uv = uv;

			parts->indices.push_back(parts->vertices.size());

			switch (j)
			{
			case 0:
				index._0 = parts->vertices.size();
				break;
			case 1:
				index._1 = parts->vertices.size();
				break;
			case 2:
				index._2 = parts->vertices.size();
				parts->myindex.push_back(index);
				break;
			default:
				break;
			}

			parts->vertices.push_back(vertex);


		}
	}

	parts->polyCount += polygonCount;
	parts->vertexCount += (polygonCount * 3);
}

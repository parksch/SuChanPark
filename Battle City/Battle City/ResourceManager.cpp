#include "ResourceManager.h"

ResourceManager* ResourceManager::m_pThis = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto iter = m_mapBitmap.begin(); iter != m_mapBitmap.end(); iter++)
	{
		auto del = (*iter).second;
		delete del;
	}
	delete m_Back;
}

void ResourceManager::initBitmap(HDC hdc)
{
	char chr[1024];
	vector<string> str;
	DWORD dwRead;
	string copy;
	HANDLE file = CreateFile(TEXT("Image/Images.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &chr, 1024, &dwRead, NULL);
	CloseHandle(file);

	chr[dwRead] = '\0';
	copy = chr;

	while (copy != "")
	{
		str.push_back(copy.substr(0, copy.find("\r")));
		copy = copy.substr(copy.find("\n") + 1);
	}

	BitMap *bMap;

	for (int i = 0; i < str.size(); i++)
	{
		bMap = new BitMap();
		bMap->Init(hdc, str[i]);
		m_mapBitmap.insert(make_pair(str[i], bMap));
	}
}

void ResourceManager::initBack(HDC hdc, int width, int height)
{
	m_Back = new BitMap();
	m_Back->InitBack(hdc, width, height);
}

HDC ResourceManager::GetBackDC()
{
	return m_Back->GetMapDC();
}

BitMap * ResourceManager::CreateBack(HDC hdc, int width, int height)
{
	BitMap* back = new BitMap();
	back->InitBack(hdc, width, height);
	return back;
}

BitMap * ResourceManager::GetBitmap(string strFileName)
{
	return  m_mapBitmap.find(strFileName)->second;
}

void ResourceManager::DrawBack(HDC hdc)
{
	m_Back->DrawBack(hdc);
}

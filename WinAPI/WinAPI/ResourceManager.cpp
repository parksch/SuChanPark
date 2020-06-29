#include "ResourceManager.h"

ResourceManager * ResourceManager::m_pThis = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < 10; i++)
	{
		delete m_BitMaps[i];
	}

	vector<BitMap*>().swap(m_BitMaps);
}

void ResourceManager::Init(HWND hWnd, HINSTANCE hInstance)
{
	BitMap *temp;
	hdc = GetDC(hWnd);
	
	for (int i = IDB_BITMAP1; i < 111; i++)
	{
		temp = new BitMap();
		temp->Init(hdc, hInstance,i);
		m_BitMaps.push_back(temp);
	}

	ReleaseDC(hWnd, hdc);
}

void ResourceManager::Draw(HWND hWnd,int wndSizeX, int wndSizeY)
{
	hdc = BeginPaint(hWnd, &ps);

	for (int i = 0;  i < 2; i++)
	{
		for (int j = 0; j < 5 ; j++)
		{
			BitBlt(
				hdc,
				150 + (j * 200), 
				100 + (i * 250), 
				m_BitMaps[j + (i * 5)]->GetSize().cx, 
				m_BitMaps[j + (i * 5)]->GetSize().cy, 
				m_BitMaps[j + (i * 5)]->GetMemDC(), 
				0, 
				0, 
				SRCCOPY);
			m_BitMaps[j + (i * 5)]->Point(150 + (j * 200),100 + (i * 250));
		}
	}

	EndPaint(hWnd, &ps);
}

void ResourceManager::CollisonCheck(HWND hWnd, int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_BitMaps[i]->CollisionCheck(x, y))
		{
			string name;
			switch (i)
			{
			case 0:
				name = "������";
				break;
			case 1:
				name = "ȣ����";
				break;
			case 2:
				name = "����";
				break;
			case 3:
				name = "�ڳ���";
				break;
			case 4:
				name = "��";
				break;
			case 5:
				name = "��";
				break;
			case 6:
				name = "�����";
				break;
			case 7:
				name = "������";
				break;
			case 8:
				name = "������";
				break;
			case 9:
				name = "��";
				break;
			default:
				break;
			}

			MessageBox(hWnd, TEXT(name.c_str()), TEXT("�����̸�"),MB_OK);
		}
	}
}


#include "ResourceManager.h"

ResourceManager* ResourceManager::m_pThis = nullptr;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < Bits.size(); i++)
	{
		delete Bits[i];
	}

	std::vector<BitMap*>().swap(Bits);
}

void ResourceManager::Init(HWND hWnd, HINSTANCE hInstance)
{
	BitMap *temp;
	HDC hdc = GetDC(hWnd);
	temp = new BitMap();
	temp->Init(hdc, hInstance, BLACK_PAWN  , "block_b_00.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, BLACK_KNIGHT, "block_b_01.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, BLACK_BISHOP, "block_b_02.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, BLACK_ROOK  , "block_b_03.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, BLACK_QUEEN , "block_b_04.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, BLACK_KING  , "block_b_05.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, WHITE_PAWN  , "block_w_00.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, WHITE_KNIGHT, "block_w_01.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, WHITE_BISHOP, "block_w_02.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, WHITE_ROOK  , "block_w_03.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, WHITE_QUEEN , "block_w_04.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, WHITE_KING  , "block_w_05.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, TILE_BROWN  , "block01.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, TILE_ALPHA  , "block02.bmp");
	Bits.push_back(temp);
	temp = new BitMap();
	temp->Init(hdc, hInstance, TILE_MOVE   , "block03.bmp");
	Bits.push_back(temp);
}

SIZE  ResourceManager::GetSize(int id)
{
	for (int i = 0; i < Bits.size(); i++)
	{
		if (Bits[i]->Getid() == id)
		{
			return Bits[i]->GetSize();
		}
	}
}

void ResourceManager::Draw(int id, HDC hdc, POINT point, bool invisible)
{
	for (int i = 0; i < Bits.size(); i++)
	{
		if (Bits[i]->Getid() == id)
		{
			Bits[i]->Draw(hdc, point.x, point.y, invisible);
			break;
		}
	}
}

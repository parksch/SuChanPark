#pragma once

#include <Windows.h>
#include <vector>
#include "Singleton.h"
#include "BitMap.h"
#include "Macro.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();
	void Init(HWND hWnd, HINSTANCE hInstance);
	SIZE GetSize(int id);
	void Draw(int id, HDC hdc, POINT point, bool invisible);
private:
	std::vector<BitMap*> Bits;
};


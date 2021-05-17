#pragma once
#include "EngineHeader.h"

class EditScene : public Scene
{
public:
	EditScene();
	~EditScene();
	void Init(HWND hWnd, int width, int height);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();
private:
	void Load(string path);
	void Save(string path,int size);
	void ListUpdate(string fileName,string path);
	HWND m_hWnd;
	Animation *m_Blocks[15];
	Animation *m_Save;
	Animation *m_Load;
	RECT m_SelectPos[16];
	RECT m_BlockPos[13][13];
	RECT m_SaveBox;
	RECT m_LoadBox;
	SIZE m_MapSize;
	string m_FilePath;
	bool isLoad;
	int curCode;
	int m_BlockCodes[13][13];
};

 
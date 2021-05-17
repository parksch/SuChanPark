#include "EditScene.h"

EditScene::EditScene()
{
	isLoad = false;
}

EditScene::~EditScene()
{
}

void EditScene::Init(HWND hWnd, int width, int height)
{
	string code;
	curCode = 15;
	m_hWnd = hWnd;
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Save = new Animation();
	m_Save->Push(ResourceManager::GetInstance()->GetBitmap("Save.bmp"),(m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f, m_MapSize.cy - m_MapSize.cy * 0.9f);
	m_Load = new Animation();
	m_Load->Push(ResourceManager::GetInstance()->GetBitmap("Load.bmp"),(m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f, m_MapSize.cy - m_MapSize.cy * 0.9f);

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			m_BlockCodes[y][x] = curCode;
		}
	}

	for (int i = 0; i < 15; i++)
	{
		if (i < 10)
		{
			code = "block0" + to_string(i) + ".bmp";
		}
		else
		{
			code = "block" + to_string(i) + ".bmp";
		}

		m_Blocks[i] = new Animation();
		m_Blocks[i]->Push(ResourceManager::GetInstance()->GetBitmap(code), ((m_MapSize.cx * 0.8f) / 13), (m_MapSize.cy / 13));
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			m_SelectPos[(y * 2) + x].left =
				(m_MapSize.cx * 0.8f) + ((m_MapSize.cx - m_MapSize.cx * 0.8f) * 0.5f - (m_MapSize.cx * 0.8f) / 13) + (x * (m_MapSize.cx * 0.8f) / 13);
			m_SelectPos[(y * 2) + x].top =
				10 + (y * (m_MapSize.cy / 13) * 1.3f);
			m_SelectPos[(y * 2) + x].right =
				(((m_MapSize.cx * 0.8f) / 13) * 0.8f) + (m_MapSize.cx * 0.8f) + ((m_MapSize.cx - m_MapSize.cx * 0.8f) * 0.5f - (m_MapSize.cx * 0.8f) / 13) + (x * (m_MapSize.cx * 0.8f) / 13);
			m_SelectPos[(y * 2) + x].bottom =
				((m_MapSize.cy / 13) * 0.8f) + 10 + (y * (m_MapSize.cy / 13 * 1.3f));
		}
	}

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			m_BlockPos[y][x].left = ((m_MapSize.cx * 0.8f) / 13) * x;
			m_BlockPos[y][x].top = (m_MapSize.cy / 13) * y;
			m_BlockPos[y][x].right = ((m_MapSize.cx * 0.8f) / 13) + ((m_MapSize.cx * 0.8f) / 13) * x;
			m_BlockPos[y][x].bottom = (m_MapSize.cy / 13) + (m_MapSize.cy / 13) * y;
		}
	}

	m_SaveBox.left = m_MapSize.cx *0.79f + ((m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f) * 0.5f;
	m_SaveBox.top = m_MapSize.cy *0.81f;
	m_SaveBox.right = m_MapSize.cx *0.8f + ((m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f) * 0.5f + (m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f;
	m_SaveBox.bottom = m_MapSize.cy *0.8f + m_MapSize.cy - m_MapSize.cy * 0.91f;

	m_LoadBox.left = m_MapSize.cx *0.79f + ((m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f) * 0.5f;
	m_LoadBox.top = m_MapSize.cy *0.91f;
	m_LoadBox.right = m_MapSize.cx *0.8f + ((m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f) * 0.5f + (m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f;
	m_LoadBox.bottom = m_MapSize.cy *0.91f + m_MapSize.cy - m_MapSize.cy * 0.92f;

	InputManager::GetInstance()->Clear();
	InputManager::GetInstance()->RegistKeyCode(MK_LBUTTON);
	InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	isLoad = true;
}

bool EditScene::Input(float fETime)
{
	if (InputManager::GetInstance()->isKeyDown(VK_ESCAPE))
	{
		SceneManager::GetInstance()->ChangeScene("Menu");
		return true;
	}

	if (InputManager::GetInstance()->isKeyDown(MK_LBUTTON))
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(m_hWnd, &mousePos);

		if (PtInRect(&m_SaveBox,mousePos))
		{
			OPENFILENAME OFN;
			char str[300];
			char lpstrFile[MAX_PATH] = "";
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = m_hWnd;
			OFN.lpstrFilter = "Text File\0*.txt;";
			OFN.lpstrFile = lpstrFile;
			OFN.lpstrDefExt = ".txt";
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = "\\Battle City\\Stage";

			if (GetSaveFileName(&OFN) != 0) {
				wsprintf(str, "%s", OFN.lpstrFile);
				Save(OFN.lpstrFile,OFN.nFileOffset);
				MessageBox(m_hWnd, str, TEXT("파일 저장 성공"), MB_OK);
			}

			return false;
		}

		if (PtInRect(&m_LoadBox,mousePos))
		{
			OPENFILENAME OFN;
			char str[300];
			char lpstrFile[MAX_PATH] = "";
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = m_hWnd;
			OFN.lpstrFilter = "Text File\0*.txt;";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = "\\Battle City\\Stage";

			if (GetOpenFileName(&OFN) != 0) {
				wsprintf(str, "%s", OFN.lpstrFile);
				Load(OFN.lpstrFile);
				MessageBox(m_hWnd, str, TEXT("파일 열기 성공"), MB_OK);
			}


			return false;
		}

		for (int i = 0; i < 16; i++)
		{
			if (PtInRect(&m_SelectPos[i],mousePos))
			{
				curCode = i;
				return false;
			}
		}
	}

	if (InputManager::GetInstance()->isKeyPress(MK_LBUTTON))
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(m_hWnd, &mousePos);

		for (int y = 0; y < 13; y++)
		{
			for (int x = 0; x < 13; x++)
			{
				if (PtInRect(&m_BlockPos[y][x], mousePos))
				{
					m_BlockCodes[y][x] = curCode;
					return false;
				}
			}
		}
	}
	return false;
}

void EditScene::Update(float fETime)
{

}

void EditScene::Draw(HDC hdc)
{
	Rectangle(hdc, 0, 0, m_MapSize.cx, m_MapSize.cy);

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 2; x++)
		{

			Rectangle(hdc,
				(m_MapSize.cx * 0.8f) + ((m_MapSize.cx - m_MapSize.cx * 0.8f) * 0.5f - (m_MapSize.cx * 0.8f) / 13) + (x * (m_MapSize.cx * 0.8f) / 13),
				10 + (y * (m_MapSize.cy / 13) * 1.3f),
				(((m_MapSize.cx * 0.8f) / 13) * 0.8f) + (m_MapSize.cx * 0.8f) + ((m_MapSize.cx - m_MapSize.cx * 0.8f) * 0.5f - (m_MapSize.cx * 0.8f) / 13) + (x * (m_MapSize.cx * 0.8f) / 13),
				((m_MapSize.cy / 13) * 0.8f) + 10 + (y * (m_MapSize.cy / 13 * 1.3f)));

			if ((y * 2) + x < 15)
			{
				m_Blocks[(y * 2) + x]->Draw(hdc,
					(m_MapSize.cx * 0.8f) + ((m_MapSize.cx - m_MapSize.cx * 0.8f) * 0.5f - (m_MapSize.cx * 0.8f) / 13) + (x * (m_MapSize.cx * 0.8f) / 13),
					10 + (y * (m_MapSize.cy / 13) * 1.3f));

			}
		}
	}

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			Rectangle(hdc,
				((m_MapSize.cx * 0.8f)/13) * x,
				(m_MapSize.cy/13) * y,
				((m_MapSize.cx * 0.8f) / 13) + ((m_MapSize.cx * 0.8f) / 13) * x,
				(m_MapSize.cy / 13) + (m_MapSize.cy/13) * y);
		}
	}

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			if (m_BlockCodes[y][x] != 15)
			{
				m_Blocks[m_BlockCodes[y][x]]->Draw(hdc, ((m_MapSize.cx * 0.8f) / 13) * x, (m_MapSize.cy / 13) * y);
			}
		}
	}

	m_Save->Draw(hdc, m_MapSize.cx *0.8f + ((m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f) * 0.5f, m_MapSize.cy *0.8f);
	m_Load->Draw(hdc, m_MapSize.cx *0.8f + ((m_MapSize.cx - m_MapSize.cx *0.8f) * 0.5f) * 0.5f, m_MapSize.cy *0.9f);
	DrawFocusRect(hdc, &m_SaveBox);
	DrawFocusRect(hdc, &m_LoadBox);

}

void EditScene::Release()
{
	if (isLoad)
	{
		for (int i = 0; i < 15; i++)
		{
			delete m_Blocks[i];
		}

		delete m_Save;
		delete m_Load;

		isLoad = false;
	}
}

void EditScene::Load(string path)
{
	HANDLE hFile = CreateFile(TEXT(path.c_str()),GENERIC_READ,0,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD dwRead;
	char chr[1024];
	string str;
	ReadFile(hFile, chr, 1024, &dwRead, NULL);
	CloseHandle(hFile);
	str = chr;

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			m_BlockCodes[y][x] = stoi(str.substr(0,str.find(" ")));
			str = str.substr(str.find(" ") + 1);
		}
		str = str.substr(1);
	}
}

void EditScene::Save(string path, int size)
{
	HANDLE hFile = CreateFile(TEXT(path.c_str()), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWrite;
	string str;

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 13; x++)
		{
			str  += to_string(m_BlockCodes[y][x]);
			str += " ";
		}

		str += '\n';
	}

	WriteFile(hFile, str.c_str(), str.size(), &dwWrite, NULL);
	CloseHandle(hFile);
	ListUpdate(path.substr(size),path.substr(0,size));
}

void EditScene::ListUpdate(string fileName, string path)
{
	HANDLE hFile = CreateFile(TEXT((path+"StageList.txt").c_str()), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwReadWirte;
	vector<string> names;
	string str;
	char chr[1024];
	bool comp = true;

	if (hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, chr, 1024, &dwReadWirte, NULL);
		chr[dwReadWirte] = '\0';
		str = chr;
		CloseHandle(hFile);

		while (str != "")
		{
			names.push_back(str.substr(0, str.find('\n')));
			str = str.substr(str.find('\n')+1);
		}

		str = "";

		for (int i = 0; i < names.size(); i++)
		{
			if (names[i] == fileName)
			{
				comp = false;
			}
			str += names[i];
			str += '\n';
		}
	}

	if (comp)
	{
		str += fileName;
		str += '\n';
	}
	
	hFile = CreateFile(TEXT((path+"StageList.txt").c_str()), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, str.c_str(), str.size(), &dwReadWirte, NULL);
	CloseHandle(hFile);

}

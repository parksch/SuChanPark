#include "MenuScene.h"

void MenuScene::Init(HWND hWnd, int width, int height)
{
	m_hWnd = hWnd;

	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_Waiting_room = new Animation();
	m_Waiting_room->Init(0);
	m_Waiting_room->Push("Waiting_room.bmp", m_MapSize.cx, m_MapSize.cy);

	m_CreateRoomRect.left = m_MapSize.cx * 0.305f;
	m_CreateRoomRect.top = m_MapSize.cy * 0.04f;
	m_CreateRoomRect.right = m_MapSize.cx * 0.385f;
	m_CreateRoomRect.bottom = m_MapSize.cy * 0.085f;

	m_JoinRoomRect.left = m_MapSize.cx * 0.22;
	m_JoinRoomRect.top = m_MapSize.cy * 0.04f;
	m_JoinRoomRect.right = m_MapSize.cx * 0.3f;
	m_JoinRoomRect.bottom = m_MapSize.cy * 0.085f;

	m_curRoom = "Non";

	InputManager::GetInstance()->RegistKeyCode(MK_LBUTTON);

	std::string login;
	login = "0 Login";

	ServerManager::GetInstance()->Send(login.c_str() , login.size());

	isLoad = true;
}

bool MenuScene::Input(float fETime)
{
	bool isInput = false;

	if (InputManager::GetInstance()->isKeyDown(MK_LBUTTON))
	{
		isInput = false;

		if (PtInRect(&m_JoinRoomRect, InputManager::GetInstance()->getMousePos()))
		{
			if (m_curRoom != "Non")
			{
				sc_JoinRoom message;
				message.type = JOIN_ROOM;
				strcpy(message.roomName, m_curRoom.c_str());
				ServerManager::GetInstance()->Send((char*)&message, sizeof(message));
				SceneManager::GetInstance()->ChangeScene("Game");
				return true;
			}
		}

		for (std::list<Room>::iterator i = m_RoomStr.begin(); i != m_RoomStr.end(); i++)
		{
			if (PtInRect((&(*i).rect), InputManager::GetInstance()->getMousePos()))
			{
				m_curRoom = (*i).name;
				isInput = true;
			}
		}

		if (PtInRect(&m_CreateRoomRect, InputManager::GetInstance()->getMousePos()))
		{
			std::string str = "1 CreateRoom";

			ServerManager::GetInstance()->Send(str.c_str(),str.size());
			SceneManager::GetInstance()->ChangeScene("Game");
		}

		if (!isInput)
		{
			m_curRoom = "Non";
		}
	}

	return false;
}

void MenuScene::Draw(HDC hdc)
{
	m_Waiting_room->Draw(hdc);

	DrawFocusRect(hdc, &m_CreateRoomRect);
	DrawFocusRect(hdc, &m_JoinRoomRect);

	for (std::list<Room>::iterator i = m_RoomStr.begin(); i != m_RoomStr.end(); i++)
	{
		DrawFocusRect(hdc, &(*i).rect);
		DrawText(hdc, (*i).name.c_str(), -1, &(*i).rect, DT_LEFT);
	}
}

void MenuScene::Release()
{
	if (!isLoad)
	{
		return;
	}

	delete m_Waiting_room;
	InputManager::GetInstance()->Clear();
	isLoad = false;
}

void MenuScene::ObjectMessage(char type, LPVOID message)
{

	switch ((Game_Behavior)type)
	{
	case ROOM_LIST:
		UpdateRoomList((char*)message);
		break;
		
	case GAME_CHAT:
		break;
	default:
		break;
	}
}

void MenuScene::UpdateRoomList(char* rList)
{
	std::string roomNames = &rList[1];
	Room room;
	RECT rect;
	int count = 0;

	for (std::list<Room>::iterator i = m_RoomStr.begin(); i != m_RoomStr.end();)
	{
		i = m_RoomStr.erase(i);
	}

	while (roomNames != "")
	{
		room.name = roomNames.substr(0, roomNames.find(","));
		room.rect.left = m_MapSize.cx *0.05f;
		room.rect.top = (count * (m_MapSize.cy * 0.02f)) + m_MapSize.cy * 0.19f;
		room.rect.right = m_MapSize.cx * 0.63f;
		room.rect.bottom = (count * (m_MapSize.cy * 0.02f)) + m_MapSize.cy * 0.22f;
		m_RoomStr.push_back(room);
		roomNames = roomNames.substr(roomNames.find(",") + 1);
		count++;
	}
}

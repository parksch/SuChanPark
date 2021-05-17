#pragma once
#include "EngineHeader.h"

struct Room
{
	std::string name;
	RECT rect;
};

class MenuScene : public Scene
{
public:
	void Init(HWND hWnd, int width, int height);
	bool Input(float fETime);
	bool Update(float fETime) { return false; };
	void Draw(HDC hdc);
	void Release();
	void ObjectMessage(char type, LPVOID message);
private:
	void UpdateRoomList(char* rList);
	std::string m_curRoom;
	HWND m_hWnd;
	std::list<Room> m_RoomStr;
	SIZE m_MapSize;
	Animation *m_Waiting_room;
	RECT m_CreateRoomRect;
	RECT m_JoinRoomRect;
};


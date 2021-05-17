#pragma once
#pragma comment(lib,"ws2_32")
#include "SingleTon.h"
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <list>

#define SERVERPORT 9000
#define BUFSIZE 1024
#define MAX_NAME 80

enum Game_Behavior
{
	ROOM_LIST = '0',
	CREATE_ROOM = '1',
	JOIN_ROOM = '2',
	ROOM_INFO = '3',
	LEAVE_ROOM = '4',
	GAME_DATA = '5',
	GAME_PLAY = '6',
	GAME_RESET = '7',
	GAME_TEXT = '8',
	GAME_CHAT = '9'
};

struct Thread_Message
{
	bool isOn = false;
	bool isConnect = false;
	SOCKET sock;
};

#pragma pack(push, 1) 

struct sc_RoomInfo
{
	char type;
	int curIndex;
	bool slot[8];
};

struct sc_JoinRoom
{
	char type;
	char roomName[255];
};

struct sc_Draw
{
	char type;
	int drawType;
	int StartX;
	int StartY;
	int EndX;
	int EndY;
};

struct sc_GameStart
{
	char type;
	int curIndex;
	char buf[80];
};

struct sc_GameChat
{
	char type;
	char buf[80];
};

#pragma pack(pop) 

class ServerManager : public Singleton<ServerManager>
{
public:
	ServerManager();
	~ServerManager();
	bool Init();
	void Send(const char* message, const int size);
	bool isConnect() { return m_Message.isConnect; }
private:
	WSADATA m_Wsa;
	Thread_Message m_Message;
	SOCKADDR_IN addr;
	HANDLE m_rThread;
};

DWORD WINAPI Recv(LPVOID arg);
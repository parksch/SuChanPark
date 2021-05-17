#pragma once
#pragma comment(lib,"ws2_32")

#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <mutex>

#define SERVERPORT 9000
#define BUFSIZE 512
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
	GAME_TEXT = '8'
};

struct SOCKETINFO
{
	OVERLAPPED overlapped;
	WSABUF wsabuf;
	SOCKET sock;
	char buf[BUFSIZE + 1];
};

struct Slot
{
	bool isEmpty = true;
	bool isGame = false;
	SOCKETINFO *info;
};

struct Room
{
	bool isGameOn = false;
	int curPlayer = 0;
	int index = 0;
	std::string room_Name;
	std::string curQstr;
	Slot player_Slot[8];
};

struct Thread_Message
{
	bool isOn = true;
	HANDLE hCp;
	std::list<SOCKETINFO*> info_List;
	std::list<Room*> room_List;
	std::vector<std::string> p_str;
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

class ServerManager
{
public:
	ServerManager();
	~ServerManager();
	int Init();
	int Error(std::string str);
private:
	int m_Retval;
	SOCKET m_listen_sock;
	WSADATA m_Wsa;
	SYSTEM_INFO m_Si;
	Thread_Message m_Message;
	std::vector<HANDLE> m_Threads;
};

DWORD WINAPI WorkerThread(LPVOID arg);

void Send_Packet(SOCKETINFO *client, const char* msg, int size);

void RoomList(Thread_Message * message, SOCKETINFO * client);

void CreateRoom(Thread_Message *message, SOCKETINFO *client);

void JoinRoom(Thread_Message *message, SOCKETINFO *client, sc_JoinRoom* join);

void RoomInfo(Thread_Message *message, SOCKETINFO *client);

void RoomUpdate(Room *room);

void DrawMessage(Thread_Message *message, SOCKETINFO*client);

void DisconnectClient(Thread_Message *message, SOCKETINFO *client);

void LeaveRoom(Thread_Message * message, SOCKETINFO * client);

void GameDataSend(Room *room,char*buf,int size);

void GamePlay(Thread_Message *message, Room *room);

void ChatComp(Thread_Message *message, SOCKETINFO *client);

Room* RoomFind(Thread_Message *message, std::string name);

Room* RoomFind(Thread_Message *message, SOCKETINFO *client);

void err_display(const char* msg);
#pragma once
#include <winsock2.h>
#include <list>
#include "Singleton.h"

#pragma comment(lib,"ws2_32")

#define SERVERPORT 9000
#define BUFSIZE 512
#define WM_SOCKET (WM_USER + 1)

struct SOCKETINFO
{
	SOCKET sock;
	SOCKET des_sock;
	char buf[BUFSIZE + 1];
	int recvbytes;
	int sendbytes;
	BOOL recvdelayed;
};

class ServerManager : public Singleton<ServerManager>
{
public:
	int Init(HWND hWnd);
	void Release();
	void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,bool *isOn);
	BOOL AddSocketInfo(SOCKET sock);
	SOCKETINFO* GetSocketInfo(SOCKET sock);
	void RemoveSocketInfo(SOCKET sock);
private:
	void err_quit(const char* msg);
	void err_display(const char* msg);
	void err_display(int errcode);
private:
	HWND m_hWnd;
	WSADATA m_wsa;
	SOCKET m_listen_sock;
	SOCKADDR_IN m_Serveraddr;
	std::list<SOCKETINFO*> m_Info;
	SOCKETINFO *temp;
	int retval;
};


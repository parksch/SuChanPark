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
	SOCKADDR_IN addr;
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
	void Send(std::string str);
	void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	void err_quit(const char* msg);
	void err_display(const char* msg);
	void err_display(int errcode);
private:
	HWND m_hWnd;
	WSADATA m_wsa;
	SOCKETINFO m_Client_info;
	int retval;
};


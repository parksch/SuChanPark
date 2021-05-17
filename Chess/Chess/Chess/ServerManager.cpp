#include "ServerManager.h"
#include "GameManager.h"

int ServerManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	m_Client_info.recvbytes = 0;
	m_Client_info.sendbytes = 0;
	m_Client_info.recvdelayed = FALSE;

	if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0)
	{
		return -1;
	}

	m_Client_info.sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_Client_info.sock == INVALID_SOCKET)
	{
		err_quit("socket()");
		return -1;
	}

	ZeroMemory(&m_Client_info.addr, sizeof(m_Client_info.addr));
	m_Client_info.addr.sin_family = AF_INET;
	m_Client_info.addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_Client_info.addr.sin_port = htons(SERVERPORT);

	retval = connect(m_Client_info.sock, (SOCKADDR*)&m_Client_info.addr, sizeof(m_Client_info.addr));

	if (retval == SOCKET_ERROR)
	{
		err_quit("connect()");
		return -1;
	}

	retval = WSAAsyncSelect(m_Client_info.sock, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);

	if (retval == SOCKET_ERROR)
	{
		err_quit("WSAAsyncSelect()");
		return -1;
	}

	return 0;
}

void ServerManager::Release()
{
	closesocket(m_Client_info.sock);
	WSACleanup();
}

void ServerManager::Send(std::string str)
{
	send(m_Client_info.sock, str.c_str(), BUFSIZE, 0);
}

void ServerManager::err_quit(const char * msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void ServerManager::err_display(const char * msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(m_hWnd, TEXT((const char*)lpMsgBuf), TEXT(msg), MB_OK);
	LocalFree(lpMsgBuf);
}

void ServerManager::err_display(int errcode)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(m_hWnd, TEXT((const char*)lpMsgBuf), TEXT("ERROR"), MB_OK);
	LocalFree(lpMsgBuf);
}

void ServerManager::ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//데이터 통신에 사용할 변수
	SOCKADDR_IN clientaddr;
	int addrlen, retval;

	//오류 발생 여부 확인
	if (WSAGETSELECTERROR(lParam))
	{
		err_display(WSAGETSELECTERROR(lParam));
		return;
	}

	//메시지 처리
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:

		retval = recv(m_Client_info.sock, m_Client_info.buf, BUFSIZE, 0);

		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			Release();
			return;
		}

		m_Client_info.recvbytes = retval;

		//받은 데이터 출력
		m_Client_info.buf[retval] = '\0';

		GameManager::GetInstance()->Recv(m_Client_info.buf);

		break;
	case FD_CLOSE:
		Release();
		break;
	}
}


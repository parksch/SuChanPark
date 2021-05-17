#include "ServerManager.h"


int ServerManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0)
	{
		return -1;
	}

	m_listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (m_listen_sock == INVALID_SOCKET)
	{
		err_quit("socket()");
		return -1;
	}

	ZeroMemory(&m_Serveraddr, sizeof(m_Serveraddr));
	m_Serveraddr.sin_family = AF_INET;
	m_Serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_Serveraddr.sin_port = htons(SERVERPORT);

	retval = bind(m_listen_sock, (SOCKADDR*)&m_Serveraddr, sizeof(m_Serveraddr));

	if (retval == SOCKET_ERROR)
	{	
		err_quit("bind()");
		return -1;
	}
	
	retval = listen(m_listen_sock, SOMAXCONN);

	if (retval == SOCKET_ERROR)
	{
		err_quit("listen()");
		return -1;
	}

	retval = WSAAsyncSelect(m_listen_sock, m_hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

	if (retval == SOCKET_ERROR)
	{
		err_quit("WSAAsyncSelect()");
		return -1;
	}

	return 0;
}

void ServerManager::Release()
{
	closesocket(m_listen_sock);
	WSACleanup();
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

void ServerManager::ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,bool *isOn)
{
	//������ ��ſ� ����� ����
	SOCKETINFO *ptr;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen, retval;

	//���� �߻� ���� Ȯ��
	if (WSAGETSELECTERROR(lParam))
	{
		err_display(WSAGETSELECTERROR(lParam));
		RemoveSocketInfo(wParam);
		return;
	}

	//�޽��� ó��
	switch (WSAGETSELECTEVENT(lParam))
	{
		//accept() �Լ��� ȣ���ϰ� ���� ���� Ȯ���Ͽ� ������ ó���Ѵ�.
	case FD_ACCEPT:

		addrlen = sizeof(clientaddr);
		client_sock = accept(wParam, (SOCKADDR*)&clientaddr, &addrlen);

		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			return;
		}

		//������ Ŭ���̾�Ʈ ������ ����Ѵ�.
		AddSocketInfo(client_sock);

		//FD_READ, FD_WRITE, FD_CLOSE�� ����Ѵ�.
		retval = WSAAsyncSelect(client_sock, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);

		if (retval == SOCKET_ERROR)
		{
			err_display("SWAAsyncSelect()");
			RemoveSocketInfo(client_sock);
		}

		if (!*isOn)
		{
			send(client_sock, "1p", sizeof("1p"), 0);
			temp = GetSocketInfo(client_sock);
			*isOn = true;
		}
		else
		{
			send(client_sock, "2p", BUFSIZE, 0);
			temp->des_sock = client_sock;
			GetSocketInfo(client_sock)->des_sock = temp->sock;
			send(client_sock, "Game", BUFSIZE, 0);
			send(temp->sock, "Game", BUFSIZE, 0);
		}

		break;
	case FD_READ:

		//���� ���� ����ü�� �޴´�.
		ptr = GetSocketInfo(wParam);

		//�̹��� �޾����� ���� ������ ���� ����Ŀ�� �ִٸ� �޾Ҵٴ� ��Ǹ� ����ϰ� �����Ѵ�.
		if (ptr->recvbytes > 0)
		{
			ptr->recvdelayed = TRUE;
			return;
		}

		//�����͹ޱ�
		retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);

		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			RemoveSocketInfo(wParam);
			return;
		}

		ptr->recvbytes = retval;

		//���� ������ ���
		ptr->buf[retval] = '\0';

	case FD_WRITE:

		ptr = GetSocketInfo(wParam);

		if (ptr->recvbytes <= ptr->sendbytes)
			return;

		//������ ������
		retval = send(ptr->des_sock, ptr->buf + ptr->sendbytes,
			ptr->recvbytes - ptr->sendbytes, 0);

		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
			RemoveSocketInfo(wParam);
			return;
		}

		ptr->sendbytes += retval;

		//���� �����͸� ��� ���´��� üũ
		//�޾����� ������ ���� ���� �� TRUE�θ� ������ �����͵��� ������
		if (ptr->recvbytes == ptr->sendbytes)
		{
			ptr->recvbytes = ptr->sendbytes = 0;

			if (ptr->recvdelayed)
			{
				ptr->recvdelayed = FALSE;
				PostMessage(hWnd, WM_SOCKET, wParam, FD_READ);
			}
		}

		break;
	case FD_CLOSE:
		RemoveSocketInfo(wParam);
		break;
	}
}

BOOL ServerManager::AddSocketInfo(SOCKET sock)
{
	SOCKETINFO* ptr = new SOCKETINFO;

	if (ptr == NULL)
	{
		printf("[����] �޸𸮰� �����մϴ�\n");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	ptr->recvdelayed = FALSE;

	m_Info.push_back(ptr);

	return TRUE;
}

SOCKETINFO * ServerManager::GetSocketInfo(SOCKET sock)
{
	for (std::list<SOCKETINFO*>::iterator i = m_Info.begin(); i != m_Info.end() ;)
	{
		if ((*i)->sock == sock)
		{
			return (*i);
		}
		else
		{
			i++;
		}
	}

	return NULL;
}

void ServerManager::RemoveSocketInfo(SOCKET sock)
{
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(sock, (SOCKADDR*)&clientaddr, &addrlen);

	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	for (std::list<SOCKETINFO*>::iterator i = m_Info.begin(); i != m_Info.end();)
	{
		if ((*i)->sock == sock)
		{
			closesocket((*i)->sock);
			delete (*i);
			i = m_Info.erase(i);
		}
		else
		{
			i++;
		}
	}

}

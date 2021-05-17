#include "ServerManager.h"
#include "SceneManager.h"

ServerManager* ServerManager::m_pThis = nullptr;

ServerManager::ServerManager()
{
}

ServerManager::~ServerManager()
{
	if (m_Message.isOn)
	{
		m_Message.isOn = false;
		CloseHandle(m_rThread);
	}

	WaitForSingleObject(m_rThread, INFINITE);
	closesocket(m_Message.sock);
	WSACleanup();
}

bool ServerManager::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &m_Wsa) != 0)
		return false;

	m_Message.sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_Message.sock == INVALID_SOCKET)
	{
		return false;
	}

	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(SERVERPORT);

	if (connect(m_Message.sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		return false;
	}

	m_Message.isOn = true;
	m_Message.isConnect = true;

	m_rThread = CreateThread(NULL, 0, Recv, (LPVOID)&m_Message, 0, NULL);

	return true;
}

void ServerManager::Send(const char * message, const int size)
{
	send(m_Message.sock, message, size, 0);
}

DWORD WINAPI Recv(LPVOID arg)
{
	Thread_Message *message = (Thread_Message*)arg;
	char buf[BUFSIZE];
	int retval;

	while (true)
	{
		retval = recv(message->sock, buf, BUFSIZE, 0);

		if (!message->isOn)
		{
			break;
		}

		if (retval == 0 || retval == -1)
		{
			message->isConnect = false;
			break;
		}

		SceneManager::GetInstance()->SendObjectMessage(buf[0], (LPVOID)&buf);
	}
	 
	return 0;
}

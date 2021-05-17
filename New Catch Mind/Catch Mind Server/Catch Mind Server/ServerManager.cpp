#include "ServerManager.h"

std::mutex mu;

void err_display(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	//화면에 출력해야 하지만 현재 윈도우로 서버를 만들었기 때문에 Window에 표시되는 함수로 변경해보자!!
	printf("[%s] %s ", msg, (const char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

ServerManager::ServerManager()
{
	m_Message.p_str.push_back("딸기");
	m_Message.p_str.push_back("유리병");
	m_Message.p_str.push_back("치킨");
	m_Message.p_str.push_back("밥");
	m_Message.p_str.push_back("피자");
	m_Message.p_str.push_back("라면");
	m_Message.p_str.push_back("떡볶이");
	m_Message.p_str.push_back("짜장면");
	m_Message.p_str.push_back("탕수육");
	m_Message.p_str.push_back("아파트");
}

ServerManager::~ServerManager()
{
	for (int i = 0; i < m_Threads.size(); i++)
	{
		WaitForSingleObject(m_Threads[i], INFINITE);
	}

	for (std::list<SOCKETINFO*>::iterator i = m_Message.info_List.begin(); i != m_Message.info_List.end(); i++)
	{
		closesocket((*i)->sock);
		delete (*i);
		i = m_Message.info_List.erase(i);
	}

	for (std::list<Room*>::iterator i = m_Message.room_List.begin(); i != m_Message.room_List.end(); )
	{
		delete (*i);
		i = m_Message.room_List.erase(i);
	}

	std::vector<HANDLE>().swap(m_Threads);
	std::vector<std::string>().swap(m_Message.p_str);
	closesocket(m_listen_sock);
	CloseHandle(m_Message.hCp);
	WSACleanup();

}

int ServerManager::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &m_Wsa) != 0)
		return Error("WSAStartup");

	//입출력 완료 포트 생성
	m_Message.hCp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (m_Message.hCp == NULL)
		return Error("CreateIoCompletionPort");

	//CPU 개수 확인
	GetSystemInfo(&m_Si);

	//(CPU 개수 * 2)개의 작접자 Thread 생성

	HANDLE hThread;

	for (int i = 0; i < (int)m_Si.dwNumberOfProcessors * 2; i++)
	{
		hThread = CreateThread(NULL, 0, WorkerThread, (LPVOID)&m_Message, 0, NULL);

		if (hThread == NULL)
			return Error("CreateThread");

		m_Threads.push_back(hThread);
	}

	m_listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_listen_sock == INVALID_SOCKET)
		return Error("socket");

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	m_Retval = bind(m_listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	if (m_Retval == SOCKET_ERROR)
		return Error("bind");

	//listen()
	m_Retval = listen(m_listen_sock, SOMAXCONN);

	if (m_Retval == SOCKET_ERROR)
		return Error("listen");

	//데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	DWORD recvbytes, flags;

	while (1)
	{
		//accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(m_listen_sock, (SOCKADDR*)&clientaddr, &addrlen);


		if (client_sock == INVALID_SOCKET)
		{
			return Error("accept()");
		}

		printf("[TCP 서버] 클라이언트 접속: IP 주소 = %s, 포트번호 = %d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		//소켓과 입출력 완료 포트 연결
		CreateIoCompletionPort((HANDLE)client_sock, m_Message.hCp, client_sock, 0);

		//소켓 정보 구조체 할당
		SOCKETINFO* ptr = new SOCKETINFO;

		ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
		ptr->sock = client_sock;
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		m_Message.info_List.push_back(ptr);
		//비동기 입출력 시작
		flags = 0;



		m_Retval = WSARecv(client_sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, NULL);
		


		if (m_Retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				Error("WSARecv()");
				break;
			}

			continue;
		}

	}


	//윈속 종료

	for (int i = 0; i < m_Threads.size(); i++)
	{
		CloseHandle(m_Threads[i]);
	}

	m_Message.isOn = false;
	return 0;
}

int ServerManager::Error(std::string str)
{
	std::cout << str + " Error" << std::endl;
	return -1;
}

DWORD WINAPI WorkerThread(LPVOID arg)
{
	Thread_Message *message = (Thread_Message*)arg;
	int retval;

	while (true)
	{
		DWORD cbTransferred;
		SOCKET client_sock;
		SOCKETINFO* ptr;

		retval = GetQueuedCompletionStatus(message->hCp, &cbTransferred, (LPDWORD)&client_sock, (LPOVERLAPPED*)&ptr, INFINITE);
		

		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);

		if (retval == 0 || cbTransferred == 0)
		{

			if (retval == 0)
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock, &ptr->overlapped, &temp1, FALSE, &temp2);
			}


			DisconnectClient(message, ptr);
			closesocket(ptr->sock);

			printf("[TCP 서버] 클라이언트 종료 : IP 주소 = %s, 포트 번호 = %d\n",
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			
			delete ptr;
			continue;
		}


		ptr->buf[cbTransferred] = '\0';

		switch ((Game_Behavior)ptr->buf[0])
		{
		case ROOM_LIST:
			RoomList(message, ptr);
			break;
		case CREATE_ROOM:
			CreateRoom(message, ptr);
			break;
		case JOIN_ROOM:
			JoinRoom(message, ptr,(sc_JoinRoom*)ptr->buf);
			break;
		case ROOM_INFO:
			RoomInfo(message, ptr);
			break;
		case LEAVE_ROOM:
			LeaveRoom(message, ptr);
			break;
		case GAME_DATA:
			DrawMessage(message, ptr);
			break;
		case GAME_TEXT:
			ChatComp(message, ptr);
			break;
		default:
			break;
		}

		ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		DWORD recvbytes;
		DWORD flags = 0;


		retval = WSARecv(ptr->sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, NULL);
		
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				err_display("WSARecv()");
			}

			continue;
		}
	}

	return 0;
}

void Send_Packet(SOCKETINFO *client, const char* msg,int size)
{
	SOCKET sock = client->sock;
	WSABUF buf;
	
	DWORD sendbytes;

	buf.buf = (CHAR*)msg;
	buf.len = size + 1;

	WSASend(sock, &buf, 1, &sendbytes, 0, NULL, NULL);

	if (WSAGetLastError() != WSA_IO_PENDING)
	{
		err_display("WSASend()");
	}

}


void RoomList(Thread_Message * message, SOCKETINFO * client)
{
	std::string rList;
	rList = ROOM_LIST;

	for (std::list<Room*>::iterator i = message->room_List.begin(); i != message->room_List.end(); i++)
	{
		rList += (*i)->room_Name;
		rList += ",";
	}

	Send_Packet(client, rList.c_str(),rList.size());
}

void CreateRoom(Thread_Message * message, SOCKETINFO * client)
{
	Room *room = new Room;
	sc_JoinRoom joinRoom;
	room->room_Name = std::to_string(client->sock) + " 의 방";
	joinRoom.type = JOIN_ROOM;
	strcpy(joinRoom.roomName, room->room_Name.c_str());
	message->room_List.push_back(room);

	std::cout << "Create Room : " << room->room_Name << std::endl;

	for (std::list<SOCKETINFO*>::iterator i = message->info_List.begin(); i != message->info_List.end();)
	{
		if ((*i)->sock == client->sock)
		{
			i = message->info_List.erase(i);
		}
		else
		{
			RoomList(message, (*i));
			i++;
		}
	}

	JoinRoom(message, client, &joinRoom);

}

void JoinRoom(Thread_Message *message, SOCKETINFO *client, sc_JoinRoom* join)
{
	Room *room = RoomFind(message, join->roomName);
	
	std::cout << "Join Room : " << join->roomName << std::endl;

	if (room != NULL)
	{
		if (room->curPlayer < 8)
		{
			for (int i = 0; i < 8; i++)
			{
				if (room->player_Slot[i].isEmpty)
				{
					room->player_Slot[i].info = client;
					room->player_Slot[i].isEmpty = false;
					room->curPlayer++;

					if (room->curPlayer > 2)
					{
						if (!room->isGameOn)
						{
							room->isGameOn = true;

							for (int i = 0; i < 8; i++)
							{
								if (!room->player_Slot[i].isEmpty)
								{
									room->player_Slot[i].isGame = true;
								}
							}

							GamePlay(message, room);
						}
					}
					break;
				}
			}
		}

	}

}

void RoomInfo(Thread_Message * message, SOCKETINFO * client)
{
	Room *room = RoomFind(message, client);

	RoomUpdate(room);
}

void RoomUpdate(Room * room)
{
	sc_RoomInfo info;
	info.type = ROOM_INFO;

	for (int i = 0; i < 8; i++)
	{
		info.slot[i] = room->player_Slot[i].isEmpty;
	}

	for (int i = 0; i < 8; i++)
	{
		if (!room->player_Slot[i].isEmpty)
		{
			info.curIndex = i;
			Send_Packet(room->player_Slot[i].info, (char*)&info,sizeof(info));
		}
	}

}

void DrawMessage(Thread_Message * message, SOCKETINFO * client)
{
	Room *room = RoomFind(message, client);

	for (int i = 0; i < 8; i++)
	{
		if (!room->player_Slot[i].isEmpty)
		{
			if (room->player_Slot[i].info->sock != client->sock)
			{
				Send_Packet(room->player_Slot[i].info, client->buf,client->wsabuf.len);
			}
		}
	}
}

void DisconnectClient(Thread_Message *message, SOCKETINFO *client)
{
	bool isDelete;

	for (std::list<Room*>::iterator iter = message->room_List.begin(); iter != message->room_List.end();)
	{
		isDelete = false;

		for (int i = 0; i < 8; i++)
		{
			if (!(*iter)->player_Slot[i].isEmpty)
			{
				if ((*iter)->player_Slot[i].info->sock == client->sock)
				{
					(*iter)->player_Slot[i].isEmpty = true;
					(*iter)->player_Slot[i].info = nullptr;
					(*iter)->player_Slot[i].isGame = false;
					(*iter)->curPlayer--;

					std::cout << "Leave Room : " << (*iter)->room_Name << std::endl;

					if ((*iter)->curPlayer == 0)
					{
						std::cout << "Delete Room : " << (*iter)->room_Name << std::endl;
						isDelete = true;
						delete (*iter);
						iter = message->room_List.erase(iter);

						for (std::list<SOCKETINFO*>::iterator iter = message->info_List.begin(); iter != message->info_List.end(); iter++)
						{
							RoomList(message, (*iter));
						}

						break;
					}
					else
					{
						RoomUpdate((*iter));

						if ((*iter)->isGameOn)
						{
							if ((*iter)->curPlayer <= 1)
							{
								(*iter)->isGameOn = false;

								for (int i = 0; i < 8; i++)
								{
									if (!(*iter)->player_Slot[i].isEmpty)
									{
										(*iter)->player_Slot[i].isGame = false;
									}
								}

								GameDataSend((*iter), (char*) "7 GameReset", sizeof("7 GameReset"));
							}
							else
							{
								GamePlay(message, (*iter));
							}
						}

					}


				}
			}
		}

		if (!isDelete)
		{
			iter++;
		}
	}

	for (std::list<SOCKETINFO*>::iterator i = message->info_List.begin(); i != message->info_List.end();)
	{
		if ((*i)->sock == client->sock)
		{
			i = message->info_List.erase(i);
			return;
		}
		else
		{
			RoomList(message, (*i));
			i++;
		}
	}


}

void LeaveRoom(Thread_Message * message, SOCKETINFO * client)
{
	bool isDelete;

	for (std::list<Room*>::iterator iter = message->room_List.begin(); iter != message->room_List.end();)
	{
		isDelete = false;
		for (int i = 0; i < 8; i++)
		{
			if (!(*iter)->player_Slot[i].isEmpty)
			{
				if ((*iter)->player_Slot[i].info->sock == client->sock)
				{
					(*iter)->player_Slot[i].isEmpty = true;
					(*iter)->player_Slot[i].info = nullptr;
					(*iter)->player_Slot[i].isGame = false;
					(*iter)->curPlayer--;
					message->info_List.push_back(client);

					std::cout << "Leave Room : " << (*iter)->room_Name << std::endl;

					if ((*iter)->curPlayer == 0)
					{
						std::cout << "Delete Room : " << (*iter)->room_Name << std::endl;
						isDelete = true;
						delete (*iter);
						iter = message->room_List.erase(iter);

						for (std::list<SOCKETINFO*>::iterator iter = message->info_List.begin(); iter != message->info_List.end(); iter++)
						{
							RoomList(message, (*iter));
						}

						break;
					}
					else
					{
						RoomUpdate((*iter));

						if ((*iter)->isGameOn)
						{
							if ((*iter)->curPlayer <= 2)
							{
								(*iter)->isGameOn = false;

								for (int i = 0; i < 8; i++)
								{
									if (!(*iter)->player_Slot[i].isEmpty)
									{
										(*iter)->player_Slot[i].isGame = false;
									}
								}

								GameDataSend((*iter),(char*) "7 GameReset", sizeof("7 GameReset"));
							}
							else
							{
								GamePlay(message, (*iter));
							}
						}

					}

				}
			}
		}

		if (!isDelete)
		{
			iter++;
		}
	}
}

void GameDataSend(Room *room, char *buf, int size)
{
	for (int i = 0; i < 8; i++)
	{
		if (!room->player_Slot[i].isEmpty)
		{
			Send_Packet(room->player_Slot[i].info, buf, size);
		}
	}
}

void GamePlay(Thread_Message *message, Room *room)
{
	sc_GameStart game;
	srand(time(NULL));
	int index = rand() % 10;
	room->curQstr = message->p_str[index];

	while (room->player_Slot[room->index].isEmpty || !room->player_Slot[room->index].isGame)
	{
		room->index = (room->index + 1) % 8;
	}

	game.type = GAME_PLAY;
	game.curIndex = room->index;
	strcpy(game.buf, room->curQstr.c_str());

	GameDataSend(room, (char*)&game, sizeof(game));
}

void ChatComp(Thread_Message * message, SOCKETINFO * client)
{
	Room *room = RoomFind(message, client);
	sc_GameChat *chat = (sc_GameChat*)client->buf;
	std::string str = chat->buf;

	if (room->curQstr == str)
	{
		for (int i = 0; i < 8; i++)
		{
			if (!room->player_Slot[i].isEmpty)
			{
				if (room->player_Slot[i].info->sock == client->sock && room->player_Slot[i].isGame && room->index != i)
				{
					room->index = (room->index + 1) % 8;
					GamePlay(message, room);
				}
			}
		}
	}
	
}

Room* RoomFind(Thread_Message *message, std::string name)
{
	for (std::list<Room*>::iterator iter = message->room_List.begin(); iter != message->room_List.end(); iter++)
	{
		if ((*iter)->room_Name == name)
		{
			return (*iter);
		} 
	}

	return NULL;
}

Room * RoomFind(Thread_Message * message, SOCKETINFO * client)
{
	for (std::list<Room*>::iterator iter = message->room_List.begin(); iter != message->room_List.end(); iter++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (!(*iter)->player_Slot[i].isEmpty)
			{
				if ((*iter)->player_Slot[i].info->sock == client->sock)
				{
					return (*iter);
				}
			}
		}
	}

	return NULL;
}



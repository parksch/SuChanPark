#include "GameScene.h"

void GameScene::Init(HWND hWnd, int width, int height)
{
	m_hWnd = hWnd;
	m_MapSize.cx = width;
	m_MapSize.cy = height;

	m_GameScene = new Animation;
	m_GameScene->Push("Waiting_room_ingame.bmp", m_MapSize.cx, m_MapSize.cy);

	InputManager::GetInstance()->RegistKeyCode(MK_LBUTTON);

	m_LeaveRect.left = m_MapSize.cx * 0.810f;
	m_LeaveRect.top = m_MapSize.cy * 0.04f;
	m_LeaveRect.right = m_MapSize.cx * 0.895f;
	m_LeaveRect.bottom = m_MapSize.cy * 0.085f;

	m_DrawRect.left = m_MapSize.cx * 0.25f;
	m_DrawRect.top = m_MapSize.cy * 0.2f;
	m_DrawRect.right = m_MapSize.cx * 0.75f;
	m_DrawRect.bottom = m_MapSize.cy * 0.64f;
	
	m_ResetRect.left = m_MapSize.cx *0.555f;
	m_ResetRect.top = m_MapSize.cy *0.669f;
	m_ResetRect.right = m_MapSize.cx *0.64f;
	m_ResetRect.bottom = m_MapSize.cy *0.71f;

	m_EraseRect.left = m_MapSize.cx * 0.47f;
	m_EraseRect.top = m_MapSize.cy * 0.67f;
	m_EraseRect.right = m_MapSize.cx * 0.51f;
	m_EraseRect.bottom = m_MapSize.cy * 0.7f;

	m_Text.left = m_MapSize.cx *0.485f;
	m_Text.top = m_MapSize.cy *0.832f;
	m_Text.right = m_MapSize.cx *0.705f;
	m_Text.bottom = m_MapSize.cy *0.865f;

	curColor = 0;

	for (int i = 0; i < 6; i++)
	{
		m_ColorRect[i].left = m_MapSize.cx *0.265f + (i * m_MapSize.cx *0.0315f);
		m_ColorRect[i].top = m_MapSize.cy *0.67f;
		m_ColorRect[i].right = m_MapSize.cx *0.29f + (i * m_MapSize.cx *0.0315f);
		m_ColorRect[i].bottom = m_MapSize.cy *0.7f;
	}

	for (int i = 0; i < 8; i++)
	{
		m_Player[i].isConnect = false;
		m_Player[i].character = new Animation;
		m_Player[i].character->Push("Character_Onion.bmp", m_MapSize.cx * 0.076f, m_MapSize.cy * 0.11f);
	}

	text = "";
	sc_RoomInfo info;
	info.type = ROOM_INFO;
	ServerManager::GetInstance()->Send((char*)&info, sizeof(info));

	time = 0;
	isClick = false;
	isErase = false;
	isTurn = false;
	isLoad = true;
	isGameStart = false;
}

bool GameScene::Input(float fETime)
{
	POINT pos = InputManager::GetInstance()->getMousePos();
	sc_Draw draw;
	draw.type = GAME_DATA;

	if (InputManager::GetInstance()->isKeyDown(MK_LBUTTON))
	{

		if (PtInRect(&m_LeaveRect, pos))
		{
			std::string str;
			str = "4 leaveRoom";
			ServerManager::GetInstance()->Send(str.c_str(), str.size());
			SceneManager::GetInstance()->ChangeScene("Menu");
			return true;
		}

		if (isTurn && !isGameStart)
		{

			if (PtInRect(&m_DrawRect, pos))
			{
				isClick = true;
				m_startPos.x = pos.x;
				m_startPos.y = pos.y;
			}

			for (int i = 0; i < 6; i++)
			{
				if (PtInRect(&m_ColorRect[i], pos))
				{
					isErase = false;
					curColor = i;
				}
			}

			if (PtInRect(&m_ResetRect, pos))
			{
				draw.drawType = 7;
				ServerManager::GetInstance()->Send((char*)&draw, sizeof(draw));
				ResetPaint();
			}

			if (PtInRect(&m_EraseRect, pos))
			{
				isErase = true;
			}
		}
	}

	if (InputManager::GetInstance()->isKeyPress(MK_LBUTTON))
	{
		if (isTurn)
		{
			if (PtInRect(&m_DrawRect, pos))
			{
				if (isErase)
				{
					draw.drawType = 6;
					draw.StartX = pos.x;
					draw.StartY = pos.y;
					ServerManager::GetInstance()->Send((char*)&draw, sizeof(draw));

					EraseDot(pos);
				}
				else
				{
					draw.drawType = curColor;
					draw.StartX = m_startPos.x;
					draw.StartY = m_startPos.y;
					draw.EndX = pos.x;
					draw.EndY = pos.y;
					ServerManager::GetInstance()->Send((char*)&draw, sizeof(draw));
					DrawPaint(m_startPos, pos, curColor);
				}
			}
		}
	}

	if (InputManager::GetInstance()->isKeyUp(MK_LBUTTON))
	{
		isClick = false;
	}

	return false;
}

bool GameScene::Update(float fETime)
{
	if (isGameStart)
	{
		time += fETime;
		if (time >= 3.0f)
		{
			isGameStart = false;
			time = 3.0f;
		}
	}
	return false;
}

void GameScene::Draw(HDC hdc)
{
	m_GameScene->Draw(hdc);

	DrawFocusRect(hdc, &m_LeaveRect);
	DrawFocusRect(hdc, &m_DrawRect);
	DrawFocusRect(hdc, &m_EraseRect);
	DrawFocusRect(hdc, &m_Text);
	DrawFocusRect(hdc, &m_ResetRect);

	for (int i = 0; i < 6; i++)
	{
		DrawFocusRect(hdc, &m_ColorRect[i]);
	}

	if (isGameStart)
	{
		TextOut(hdc, m_MapSize.cx *0.45f, m_MapSize.cy*0.4f, "GAME START", sizeof("GAME START") - 1);
	}

	if (text != "")
	{
		DrawText(hdc, text.c_str(), -1, &m_Text, DT_LEFT);
	}

	if (isTurn && !isGameStart)
	{
		TextOut(hdc, m_MapSize.cx * 0.3f, m_MapSize.cy * 0.14f, qstr.c_str(), qstr.size());
	}

	for (std::list<DrawDot>::iterator i = m_Draw.begin(); i != m_Draw.end(); i++)
	{	
		SetColor((*i).colorIndex,hdc);
		MoveToEx(hdc, (*i).startPos.x, (*i).startPos.y, NULL);
		LineTo(hdc, (*i).endPos.x, (*i).endPos.y);
		SelectObject(hdc, oldPEN);
		DeleteObject(myPEN);
	}

	for (int i = 0; i < 8; i++)
	{
		if (m_Player[i].isConnect)
		{
			RECT rect;
			rect.left = m_MapSize.cx * 0.06f + (i % 2 * (m_MapSize.cx * 0.84f));
			rect.top = m_MapSize.cy * 0.215f + (i / 2 * (m_MapSize.cy * 0.15f));
			rect.right = m_MapSize.cx * 0.1f + (i % 2 * (m_MapSize.cx * 0.84f));
			rect.bottom = m_MapSize.cy * 0.265f + (i / 2 * (m_MapSize.cy * 0.15f));
			DrawText(hdc, "Player", -1, &rect, DT_CENTER);
			m_Player[i].character->Draw(hdc, m_MapSize.cx * 0.125f + (i % 2 * (m_MapSize.cx * 0.674f)), m_MapSize.cy * 0.196f + (i / 2) * (m_MapSize.cy * 0.15f));
		}
	}
}

void GameScene::Release()
{
	if (!isLoad)
	{
		return;
	}

	delete m_GameScene;

	for (int i = 0; i < 8; i++)
	{
		delete m_Player[i].character;
	}
	isLoad = false;
}

void GameScene::ObjectMessage(char type, LPVOID message)
{
	switch (type)
	{
	case ROOM_INFO:
		RoomUpdate((sc_RoomInfo*)message);
		break;
	case GAME_CHAT:
		GameText((char*)message);
		break;
	case GAME_TEXT:
		SendTEXT((char*)message);
		break;
	case GAME_DATA:
		DrawMessage((sc_Draw*)message);
		break;
	case GAME_PLAY:
		ResetPaint();
		SetGame((sc_GameStart*)message);
		break;
	case GAME_RESET:
		Reset();
		break;
	default:
		break;
	}
}

void GameScene::Reset()
{
	ResetPaint();

	isTurn = false;
	isGameStart = false;
	time = 0;
	qstr = "";

}

void GameScene::SendTEXT(char * str)
{
	sc_GameChat chat;
	chat.type = GAME_TEXT;
	strcpy(chat.buf, str);
	ServerManager::GetInstance()->Send((char*)&chat, sizeof(chat));
	text.clear();
}

void GameScene::GameText(char * str)
{
	text = str;
}

void GameScene::DrawPaint(POINT startPos, POINT endPos, int color)
{
	DrawDot dot;

	dot.colorIndex = color;

	dot.startPos.x = startPos.x;
	dot.startPos.y = startPos.y;

	dot.endPos.x = endPos.x;
	dot.endPos.y = endPos.y;

	m_startPos.x = endPos.x;
	m_startPos.y = endPos.y;

	m_Draw.push_back(dot);
}

void GameScene::EraseDot(POINT pos)
{
	RECT eraseRect;
	RECT dotStartRect;
	RECT dotEndRect;

	for (std::list<DrawDot>::iterator iter = m_Draw.begin(); iter != m_Draw.end(); )
	{
		dotStartRect.left = (*iter).startPos.x - 3;
		dotStartRect.top = (*iter).startPos.y - 3;
		dotStartRect.right = (*iter).startPos.x + 3;
		dotStartRect.bottom = (*iter).startPos.y + 3;

		dotEndRect.left = (*iter).endPos.x - 3;
		dotEndRect.top = (*iter).endPos.y - 3;
		dotEndRect.right = (*iter).endPos.x + 3;
		dotEndRect.bottom = (*iter).endPos.y + 3;

		eraseRect.left = pos.x - 10;
		eraseRect.top = pos.y - 10;
		eraseRect.right = pos.x + 10;
		eraseRect.bottom = pos.y + 10;

		if (IntersectRect(&RECT(), &eraseRect, &dotStartRect))
		{
			iter = m_Draw.erase(iter);
		}
		else if (IntersectRect(&RECT(), &eraseRect, &dotEndRect))
		{
			iter = m_Draw.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void GameScene::RoomUpdate(sc_RoomInfo *info)
{
	m_CurIndex = info->curIndex;

	for (int i = 0; i < 8; i++)
	{
		if (!info->slot[i])
		{
			m_Player[i].isConnect = true;
		}
		else
		{
			m_Player[i].isConnect = false;
		}
	}
}

void GameScene::SetColor(int index, HDC hdc)
{

	if (index == 0)
	{
		myPEN = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		oldPEN = (HPEN)SelectObject(hdc, myPEN);
	}

	if (index == 1)
	{
		myPEN = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		oldPEN = (HPEN)SelectObject(hdc, myPEN);
	}

	if (index == 2)
	{
		myPEN = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		oldPEN = (HPEN)SelectObject(hdc, myPEN);
	}

	if (index == 3)
	{
		myPEN = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
		oldPEN = (HPEN)SelectObject(hdc, myPEN);
	}

	if (index == 4)
	{
		myPEN = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
		oldPEN = (HPEN)SelectObject(hdc, myPEN);
	}

	if (index == 5)
	{
		myPEN = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		oldPEN = (HPEN)SelectObject(hdc, myPEN);
	}
}


void GameScene::SetGame(sc_GameStart* start)
{
	if (start->curIndex == m_CurIndex)
	{
		isTurn = true;
		qstr = start->buf;
	}
	else
	{
		isTurn = false;
		qstr = "";
	}

	if (time < 0.1f)
	{
		isGameStart = true;
	}

}

void GameScene::ResetPaint()
{
	for (std::list<DrawDot>::iterator iter = m_Draw.begin(); iter != m_Draw.end(); )
	{
		iter = m_Draw.erase(iter);
	}
}

void GameScene::DrawMessage(sc_Draw * draw)
{
	POINT start, end;
	start.x = draw->StartX;
	start.y = draw->StartY;
	end.x = draw->EndX;
	end.y = draw->EndY;

	if (draw->drawType < 6)
	{
		DrawPaint(start, end, draw->drawType);
	}
	else if (draw->drawType < 7)
	{
		EraseDot(start);
	}
	else if (draw->drawType < 8)
	{
		ResetPaint();
	}
}

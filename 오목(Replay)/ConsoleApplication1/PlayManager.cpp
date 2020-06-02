#include "PlayManager.h"

PlayManager* PlayManager::m_This = NULL;

PlayManager::PlayManager()
{
}

void PlayManager::SetGame(int x, int y)
{
	m_iWidth = x;
	m_iHeight = y;
	m_Cursor.x = m_iWidth / 2;
	m_Cursor.y = m_iHeight / 2;
	m_P1.SetStone("○");
	m_P2.SetStone("●");
	m_iTurn = 1;
	m_bPlayState = false;
	m_bGameOver = false;
}

void PlayManager::Option()
{
	int Select;
	int Width, Height;
	char buf[256];
	while (1)
	{
		system("cls");
		MapDrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
		MapDrawManager.DrawMidText("---옵     션---", m_iWidth, m_iHeight* 0.1);
		MapDrawManager.DrawMidText("1.맵 사이즈 변경", m_iWidth, (m_iHeight* 0.1) + 2);
		MapDrawManager.DrawMidText("2.커서 커스텀", m_iWidth, (m_iHeight* 0.1) + 4);
		MapDrawManager.DrawMidText("3.돌 커스텀", m_iWidth, (m_iHeight* 0.1) + 6);
		MapDrawManager.DrawMidText("4.물리기 설정", m_iWidth, (m_iHeight* 0.1) + 8);
		MapDrawManager.DrawMidText("5.돌아가기", m_iWidth, (m_iHeight* 0.1) + 10);
		MapDrawManager.DrawMidText("선택 : ", m_iWidth, (m_iHeight* 0.1) + 12);
		cin >> Select;
		system("cls");
		MapDrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
		switch (Select)
		{
		case 1:
			if (!m_bPlayState)
			{
				Width = m_iWidth;
				Height = m_iHeight;
				while (1)
				{
					MapDrawManager.DrawMidText("맵 크기 설정", Width, Height* 0.1);
					MapDrawManager.DrawMidText("가로 : ", Width, (Height* 0.1) + 2);
					cin >> m_iWidth;
					MapDrawManager.DrawMidText("세로 : ", Width, (Height* 0.1) + 4);
					cin >> m_iHeight;
					if ((m_iHeight >= 20 && m_iHeight <= 45) && (m_iWidth >= 20 && m_iWidth <= 90))
						break;
					system("cls");
					MapDrawManager.BoxDraw(0, 0, Width, Height);
					MapDrawManager.DrawMidText("변경 불가능", Width, (Height* 0.1) + 4);
					MapDrawManager.DrawMidText("(가로 : 20 ~ 90 , 세로 :20 ~ 45)", Width, (Height* 0.1) + 6);
					MapDrawManager.gotoxy(0, Height);
					system("pause");
				}
				sprintf(buf, "mode con: lines=%d cols=%d", m_iHeight + 4, (m_iWidth * 2) + 1);
				system(buf);
				m_Cursor.x = m_iWidth / 2;
				m_Cursor.y = m_iHeight / 2;
			}
			else
			{
				MapDrawManager.DrawMidText("Play중입니다.", m_iWidth, (m_iHeight* 0.1) + 2);
				MapDrawManager.DrawMidText("(접근 실패)", m_iWidth, (m_iHeight* 0.1) + 4);
				MapDrawManager.gotoxy(0, m_iHeight);
				system("pause");
			}
			break;
		case 2:
			MapDrawManager.DrawMidText("1.(○,●)  2.(♧,♣)", m_iWidth, (m_iHeight* 0.1) + 2);
			MapDrawManager.DrawMidText("3.(♡,♥) 4.(☞,☜) 5.기타", m_iWidth, (m_iHeight* 0.1) + 4);
			MapDrawManager.DrawMidText("6.돌아가기", m_iWidth, (m_iHeight* 0.1) + 6);
			MapDrawManager.DrawMidText("선택 : ", m_iWidth, (m_iHeight* 0.1) + 8);
			cin >> Select;
			switch (Select)
			{
			case 1:
				m_Cursor.P1_Icon = "●";
				m_Cursor.P2_Icon = "○";
				break;
			case 2:
				m_Cursor.P1_Icon = "♣";
				m_Cursor.P2_Icon = "♧";
				break;
			case 3:
				m_Cursor.P1_Icon = "♥";
				m_Cursor.P2_Icon = "♡";
				break;
			case 4:
				m_Cursor.P1_Icon = "☞";
				m_Cursor.P2_Icon = "☜";
				break;
			case 5:
				while (1)
				{
					system("cls");
					MapDrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
					MapDrawManager.DrawMidText("P1커서 : ", m_iWidth, (m_iHeight* 0.1) + 4);
					cin >> m_Cursor.P1_Icon;
					MapDrawManager.DrawMidText("P2커서 : ", m_iWidth, (m_iHeight* 0.1) + 6);
					cin >> m_Cursor.P2_Icon;
					if (m_Cursor.P1_Icon.size() == 2 && m_Cursor.P2_Icon.size() == 2)
						break;
					MapDrawManager.DrawMidText("커서는 특수문자 1개만 가능합니다.", m_iWidth, (m_iHeight* 0.1) + 8);
					system("pause");
				}
				break;
			}
			break;
		case 3:
			MapDrawManager.DrawMidText("1.(○,●)  2.(☆,★)", m_iWidth, (m_iHeight* 0.1) + 2);
			MapDrawManager.DrawMidText("3.(♤,♠) 4.(☏,☎)", m_iWidth, (m_iHeight* 0.1) + 4);
			MapDrawManager.DrawMidText("5.돌아가기", m_iWidth, (m_iHeight* 0.1) + 6);
			MapDrawManager.DrawMidText("선택 : ", m_iWidth, (m_iHeight* 0.1) + 8);
			cin >> Select;
			switch (Select)
			{
			case 1:
				m_P1.SetStone("●");
				m_P2.SetStone("○");
				break;
			case 2:
				m_P1.SetStone("☆");
				m_P2.SetStone("★");
				break;
			case 3:
				m_P1.SetStone("♤");
				m_P2.SetStone("♠");
				break;
			case 4:
				m_P1.SetStone("☏");
				m_P2.SetStone("☎");
				break;
			}
			break;
		case 4:
			if (!m_bPlayState)
			{
				MapDrawManager.DrawMidText("게임 설정", m_iWidth, m_iHeight* 0.1);
				MapDrawManager.DrawMidText("1.물리기 횟수 조절", m_iWidth, (m_iHeight* 0.1) + 2);
				MapDrawManager.DrawMidText("2.물리기 OFF", m_iWidth, (m_iHeight* 0.1) + 4);
				MapDrawManager.DrawMidText("3.돌아가기", m_iWidth, (m_iHeight* 0.1) + 6);
				MapDrawManager.DrawMidText("선택 : ", m_iWidth, (m_iHeight* 0.1) + 8);
				cin >> Select;
				switch (Select)
				{
				case 1:
					MapDrawManager.DrawMidText("물리기 횟수 입력 : ", m_iWidth, (m_iHeight* 0.1) + 10);
					cin >> Select;
					m_P1.Return_Set(Select);
					m_P2.Return_Set(Select);
					break;
				case 2:
					m_P1.Return_Set(0);
					m_P2.Return_Set(0);
					break;
				}
			}
			else
			{
				MapDrawManager.DrawMidText("Play중입니다.", m_iWidth, (m_iHeight* 0.1) + 2);
				MapDrawManager.DrawMidText("(접근 실패)", m_iWidth, (m_iHeight* 0.1) + 4);
				MapDrawManager.gotoxy(0, m_iHeight);
				system("pause");
			}
			break;
		case 5:
			return;
		default:
			break;
		}
	}
	return;
}

void PlayManager::OmokSave()
{
	ofstream fSave;
	int P1Count = 0, P2Count = 0;
	Stone* tmpStone;
	fSave.open("Replay.txt");
	if (fSave.is_open())
	{
		fSave << m_iTurn << endl;
		fSave << m_P1.GetName() << " " << m_P2.GetName() << endl;
		fSave << m_P1.GetStone() << " " << m_P2.GetStone() << endl;
		for (int i = 1; i <= m_iTurn; i++)
		{
			if (i % 2 == 1)
				tmpStone = m_P1.GetStonePosition(P1Count++);
			else
				tmpStone = m_P2.GetStonePosition(P2Count++);
			fSave << tmpStone->x << " " << tmpStone->y << endl;
		}
		fSave.close();
	}
}

void PlayManager::OmokLoad()
{
	ifstream fLoad;
	string tmpstr;
	string Stone[2];
	int TmpTurn;
	int x, y;
	system("cls");
	fLoad.open("Replay.txt");
	if (fLoad.is_open())
	{
		fLoad >> TmpTurn;
		fLoad >> tmpstr;
		m_P1.SetName(tmpstr);
		fLoad >> tmpstr;
		m_P2.SetName(tmpstr);
		fLoad >> Stone[1];
		fLoad >> Stone[0];
		MapDrawManager.Draw(m_iWidth, m_iHeight);
		MapDrawManager.gotoxy(0, m_iHeight + 1);
		cout << "돌 놓기 : z , 무르기 : x, 종료 : ESC" << endl << "옵션 : p";
		for (m_iTurn = 1; m_iTurn <= TmpTurn; m_iTurn++)
		{
			Sleep(1000);
			MapDrawManager.DrawMidText("              ", m_iWidth*1.5, m_iHeight + 3);
			if (m_iTurn % 2 == 1)
				MapDrawManager.DrawMidText(m_P1.GetName(), m_iWidth*1.5, m_iHeight + 3);
			else
				MapDrawManager.DrawMidText(m_P2.GetName(), m_iWidth*1.5, m_iHeight + 3);
			fLoad >> x >> y;
			MapDrawManager.DrawPoint(Stone[m_iTurn%2], x, y);
		}
		fLoad.close();
	}
	else
	{
		MapDrawManager.DrawMidText("저장된 기록이 없습니다.", m_iWidth, m_iHeight / 2);
		getch();
	}
	MapDrawManager.gotoxy(1, m_iHeight + 4);
	system("pause");
}

void PlayManager::TitleDraw()
{
	MapDrawManager.DrawMidText("●○오  목○●", m_iWidth, m_iHeight / 4);
	MapDrawManager.DrawMidText("1.게임 시작", m_iWidth, 2 + (m_iHeight / 4));
	MapDrawManager.DrawMidText("2.Replay", m_iWidth, 4 + (m_iHeight / 4));
	MapDrawManager.DrawMidText("3.게임 설정", m_iWidth, 6 + (m_iHeight / 4));
	MapDrawManager.DrawMidText("4. 종료", m_iWidth, 8 + (m_iHeight / 4));
	return;
}

void PlayManager::Input()
{
	char ch;
	char buf[256];
	bool Backing_State = false;
	Stone* tmpStone;
	ch = getch();
	MapDrawManager.Erase(m_Cursor.x, m_Cursor.y, m_iWidth, m_iHeight);
	if(m_P1.Compare_Stone(m_Cursor.x,m_Cursor.y))
		MapDrawManager.DrawPoint(m_P1.GetStone(), m_Cursor.x, m_Cursor.y);
	if (m_P2.Compare_Stone(m_Cursor.x, m_Cursor.y))
		MapDrawManager.DrawPoint(m_P2.GetStone(), m_Cursor.x, m_Cursor.y);
	switch (ch)
	{
	case LEFT:
		if (m_Cursor.x - 1 >= 0)
			m_Cursor.x--;
		break;
	case RIGHT:
		if (m_Cursor.x + 1 < m_iWidth)
			m_Cursor.x++;
		break;
	case UP:
		if (m_Cursor.y - 1 >= 0)
			m_Cursor.y--;
		break;
	case DOWN:
		if (m_Cursor.y + 1 < m_iHeight)
			m_Cursor.y++;
		break;
	case DROP:
		if (!m_P1.Compare_Stone(m_Cursor.x, m_Cursor.y) && !m_P2.Compare_Stone(m_Cursor.x, m_Cursor.y))
		{
			if (m_iTurn % 2 == 1)
			{
				m_P1.Create_Stone(m_Cursor.x, m_Cursor.y);
				MapDrawManager.DrawPoint(m_P1.GetStone(), m_Cursor.x, m_Cursor.y);
			}
			else
			{
				m_P2.Create_Stone(m_Cursor.x, m_Cursor.y);
				MapDrawManager.DrawPoint(m_P2.GetStone(), m_Cursor.x, m_Cursor.y);
			}
			if (Result())
				m_bGameOver = true;

			if (m_bGameOver)
			{
				if (m_Win_Team_Name == "무승부")
					sprintf(buf, "무 승 부");
				else
					sprintf(buf, "%s 승리!!", m_Win_Team_Name.c_str());
				MapDrawManager.DrawMidText(buf, m_iWidth, m_iHeight / 2);
				MapDrawManager.gotoxy(0, m_iHeight);
				getch();
				break;
			}
			m_iTurn++;
		}
		break;
	case BACK:
		if (m_iTurn > 1)
		{
			m_iTurn--;
			if (m_iTurn % 2 == 1)
				tmpStone = m_P1.Stone_Backing();
			else
				tmpStone = m_P2.Stone_Backing();
			if (tmpStone == NULL)
				Backing_State = true;
			else
			{
				MapDrawManager.Erase(tmpStone->x, tmpStone->y, m_iWidth, m_iHeight);
				delete tmpStone;
			}
			if (Backing_State)
			{
				MapDrawManager.DrawMidText("무르기 불가", 0, m_iHeight + 3);
				Sleep(1000);
				MapDrawManager.DrawMidText("                 ", 0, m_iHeight + 3);
				m_iTurn++;
			}
		}
		break;
	case ESC:
		m_bGameOver = true;
		break;
	case OPTION:
		Option();
		system("cls");
		MapDrawManager.Draw(m_iWidth, m_iHeight);
		MapDrawManager.gotoxy(0, m_iHeight + 1);
		cout << "돌 놓기 : z , 무르기 : x, 종료 : ESC" << endl << "옵션 : p";
		break;
	}
	return;
}

bool PlayManager::Result()
{
	bool Win_state = false;
	if (m_iTurn % 2 == 0)
	{
		if (m_P2.Omok_Win(m_Cursor.x, m_Cursor.y))
		{
			Win_state = true;
			m_Win_Team_Name = m_P2.GetName();
		}
	}
	else
	{
		if (m_P1.Omok_Win(m_Cursor.x, m_Cursor.y))
		{
			Win_state = true;
			m_Win_Team_Name = m_P1.GetName();
		}
	}
	return Win_state;
}

void PlayManager::Playing()
{
	string str;
	m_bPlayState = true;
	system("cls");
	MapDrawManager.BoxDraw(0, 0, m_iWidth, m_iHeight);
	MapDrawManager.DrawMidText("팀 이름 설정", m_iWidth, m_iHeight* 0.1);
	MapDrawManager.DrawMidText("P1 이름 : ", m_iWidth, (m_iHeight* 0.1) + 2);
	cin >> str;
	m_P1.SetName(str);
	MapDrawManager.DrawMidText("P2 이름 : ", m_iWidth, (m_iHeight* 0.1) + 4);
	cin >> str;
	m_P2.SetName(str);
	system("cls");
	MapDrawManager.Draw(m_iWidth, m_iHeight);
	MapDrawManager.gotoxy(0, m_iHeight + 1);
	cout << "돌 놓기 : z , 무르기 : x, 종료 : ESC" << endl << "옵션 : p";
	while (!m_bGameOver)
	{
		MapDrawManager.DrawMidText("              ", m_iWidth*1.5, m_iHeight + 3);
		if(m_iTurn % 2 == 0)
			MapDrawManager.DrawMidText(m_P2.GetName(), m_iWidth*1.5, m_iHeight + 3);
		else
			MapDrawManager.DrawMidText(m_P1.GetName(), m_iWidth*1.5, m_iHeight + 3);
		if (m_iTurn % 2 == 0)
		{
			MapDrawManager.DrawPoint(m_Cursor.P1_Icon, m_Cursor.x, m_Cursor.y);
			MapDrawManager.gotoxy(0, m_iHeight + 3);
			cout << "무르기 횟수 : " << setw(2) << left << m_P1.Get_Return_Count();
		}
		else
		{
			MapDrawManager.DrawPoint(m_Cursor.P2_Icon, m_Cursor.x, m_Cursor.y);
			MapDrawManager.gotoxy(0, m_iHeight + 3);
			cout << "무르기 횟수 : " << setw(5) << left << m_P2.Get_Return_Count();
		}
		MapDrawManager.gotoxy(0, m_iHeight);
		cout << "Turn : " << setw(10) << left << m_iTurn;
		Input();
	}
	OmokSave();
	return;
}

void PlayManager::ReSet()
{
	m_P1.Release();
	m_P2.Release();
	m_Cursor.x = m_iWidth / 2;
	m_Cursor.y = m_iHeight / 2;
	m_iTurn = 1;
	m_bPlayState = false;
	m_bGameOver = false;
}

void PlayManager::Display()
{
	int Select;
	while (1)
	{
		system("cls");
		MapDrawManager.Draw(m_iWidth, m_iHeight);
		TitleDraw();
		MapDrawManager.BoxDraw(m_iWidth, 10 + (m_iHeight / 4), 7, 3);
		MapDrawManager.gotoxy(m_iWidth, 11 + (m_iHeight / 4));
		cin >> Select;
		switch (Select)
		{
		case 1:
			Playing();
			ReSet();
			break;
		case 2:
			OmokLoad();
			break;
		case 3:
			Option();
			break;
		case 4:
			MapDrawManager.gotoxy(0, m_iHeight);
			return;
		}
	}
	return;
}


PlayManager::~PlayManager()
{
}

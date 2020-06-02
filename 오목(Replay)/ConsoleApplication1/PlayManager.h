#pragma once
#include "Singleton.h"
#include"MapDraw.h"
#include"Player.h"
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define DROP 'z'
#define BACK 'x'
#define OPTION 'p'
struct Cursor
{
	int x;
	int y;
	string P1_Icon = "¡Ü";
	string P2_Icon = "¡Û";
};

class PlayManager : public Singleton<PlayManager>
{
private:
	MapDraw		MapDrawManager;
	bool		m_bPlayState;
	bool		m_bGameOver;
	int			m_iWidth;
	int			m_iHeight;
	Cursor		m_Cursor;
	Player		m_P1;
	Player		m_P2;
	int			m_iTurn;
	string		m_Win_Team_Name;
	void		Playing();
	void		TitleDraw();
	void		Input();
	bool		Result();
	void		Option();
	void		ReSet();
	void		OmokSave();
	void		OmokLoad();
public:	
	void SetGame(int x = 20, int y = 20);
	void Display();
	PlayManager();
	~PlayManager();
};



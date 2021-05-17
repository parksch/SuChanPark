#pragma once
#include "EngineHeader.h"

struct sc_Player
{
	bool isConnect;
	Animation *character;
};

struct DrawDot
{
	int colorIndex;
	POINT startPos;
	POINT endPos;
};

class GameScene : public Scene
{
public:
	void Init(HWND hWnd, int width, int height);
	bool Input(float fETime);
	bool Update(float fETime);
	void Draw(HDC hdc);
	void Release();
	void ObjectMessage(char type, LPVOID message);
	void Reset();
private:
	void SendTEXT(char*str);
	void GameText(char *str);
	void DrawPaint(POINT startPos,POINT endPos, int color);
	void EraseDot(POINT pos);
	void RoomUpdate(sc_RoomInfo *info);
	void SetColor(int index, HDC hdc);
	void SetGame(sc_GameStart *start);
	void ResetPaint();
	void DrawMessage(sc_Draw *draw);
private:
	float time;
	int curColor;
	int m_CurIndex;
	bool isGameStart;
	bool isClick;
	bool isTurn;
	bool isDraw;
	bool isErase;
	std::string text;
	std::string qstr;
	sc_Player m_Player[8];
	POINT m_startPos;
	HWND m_hWnd;
	SIZE m_MapSize;
	RECT m_Text;
	RECT m_LeaveRect;
	RECT m_DrawRect;
	RECT m_ColorRect[6];
	RECT m_ResetRect;
	RECT m_EraseRect;
	HPEN myPEN, oldPEN;
	std::list<DrawDot> m_Draw;
	Animation *m_GameScene;
};


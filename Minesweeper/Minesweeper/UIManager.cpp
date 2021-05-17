#include "UIManager.h"

UIManager* UIManager::m_pThis = nullptr;

UIManager::UIManager()
{
}

UIManager::~UIManager()
{

}

void UIManager::Init(HWND hWnd, int width, int height, int difficulty)
{

	if (difficulty == 1)
	{
		mine = 10;
		timePos.x = width * 0.2f;
		timePos.y = height * 0.935f;
		minePos.x = width * 0.75f;
		minePos.y = height * 0.935f;
	}

	if (difficulty == 2)
	{
		mine = 40;
		timePos.x = width * 0.21f;
		timePos.y = height * 0.935f;
		minePos.x = width * 0.77f;
		minePos.y = height * 0.935f;
	}

	if (difficulty == 3)
	{
		mine = 99;
		timePos.x = width * 0.22f;
		timePos.y = height * 0.935f;
		minePos.x = width * 0.77f;
		minePos.y = height * 0.935f;
	}

	time = 0;
	curtime = 0;
	pause = false;
}

void UIManager::Update(float eTime)
{
	if (!pause)
	{
		curtime += eTime;

		if (curtime >= 1)
		{
			curtime = 0;
			time++;
		}
	}
}


void UIManager::Draw(HDC hdc)
{
	TextOut(hdc, timePos.x, timePos.y, TEXT(to_string(time).c_str()), strlen(to_string(time).c_str()));
	TextOut(hdc, minePos.x , minePos.y, TEXT(to_string(mine).c_str()), strlen(to_string(mine).c_str()));
}

void UIManager::Change(int offset)
{
	mine += offset;

	if (offset == 0)
	{
		mine = 0;
	}
}

void UIManager::Reset(int difficulty)
{
	if (difficulty == 1)
	{
		mine = 10;
	}

	if (difficulty == 2)
	{
		mine = 40;

	}

	if (difficulty == 3)
	{
		mine = 99;

	}

	time = 0;
	curtime = 0;
	pause = false;
}

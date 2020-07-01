#pragma once
#include "Card.h"

Card::Card()
{
}

void Card::drawAll(HDC hdc)
{
	dog.Draw(hdc, 50, 50);
	tiger.Draw(hdc, 200, 50);
	duck.Draw(hdc, 350, 50);
	cow.Draw(hdc, 500, 50);
	horse.Draw(hdc, 650, 50);
	elephant.Draw(hdc, 50, 300);
	cat.Draw(hdc, 200, 300);
	monkey.Draw(hdc, 350, 300);
	frog.Draw(hdc, 500, 300);
	chicken.Draw(hdc, 650, 300);
}

void Card::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);

	dog.Init(hdc, hInst, IDB_BITMAP1);
	tiger.Init(hdc, hInst, IDB_BITMAP2);
	duck.Init(hdc, hInst, IDB_BITMAP3);
	cow.Init(hdc, hInst, IDB_BITMAP5);
	horse.Init(hdc, hInst, IDB_BITMAP6);
	elephant.Init(hdc, hInst, IDB_BITMAP4);
	cat.Init(hdc, hInst, IDB_BITMAP7);
	monkey.Init(hdc, hInst, IDB_BITMAP8);
	frog.Init(hdc, hInst, IDB_BITMAP9);
	chicken.Init(hdc, hInst, IDB_BITMAP10);

	ReleaseDC(hWnd, hdc);
}

void Card::clickMessage(HWND hWnd, int mouseX, int mouseY)
{
	if (mouseY > 50 && mouseY < 285)
	{
		if (mouseX > 50 && mouseX < 195)
			(MessageBox(hWnd, "개", "동물", MB_OK));
		else if (mouseX > 200 && mouseX < 345)
			(MessageBox(hWnd, "호랑이", "동물", MB_OK));
		else if (mouseX > 350 && mouseX < 495)
			(MessageBox(hWnd, "오리", "동물", MB_OK));
		else if (mouseX > 500 && mouseX < 645)
			(MessageBox(hWnd, "소", "동물", MB_OK));
		else if (mouseX > 650 && mouseX < 795)
			(MessageBox(hWnd, "말", "동물", MB_OK));
	}
	else if (mouseY > 300 && mouseY < 535)
	{
		if (mouseX > 50 && mouseX < 195)
			(MessageBox(hWnd, "코끼리", "동물", MB_OK));
		else if (mouseX > 200 && mouseX < 345)
			(MessageBox(hWnd, "고양이", "동물", MB_OK));
		else if (mouseX > 350 && mouseX < 495)
			(MessageBox(hWnd, "원숭이", "동물", MB_OK));
		else if (mouseX > 500 && mouseX < 645)
			(MessageBox(hWnd, "개구리", "동물", MB_OK));
		else if (mouseX > 650 && mouseX < 795)
			(MessageBox(hWnd, "닭", "동물", MB_OK));
	}
}

Card::~Card()
{
}

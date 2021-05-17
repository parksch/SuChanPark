#include "UIManager.h"

UIManager* UIManager::m_pThis = nullptr;

UIManager::UIManager()
{
	isLoad = false;
}

UIManager::~UIManager()
{
	if (isLoad)
	{
		delete life;
		isLoad = false;
	}
}

void UIManager::Init(HWND hWnd, int width, int height)
{
	if (!isLoad)
	{
		life = new Animation();
		life->images.push_back(ResourceManager::GetInstance()->GetBitmap("icon.bmp"));
	}

	map_Size.x = width;
	map_Size.y = height;
	curTime = 0;
	isLoad = true;
	isEnd = false;
	isAcetive = false;

}

void UIManager::Update(float eTime)
{
	if (isAcetive)
	{
		curTime += eTime;
		
		if (isEnd && bonus > 0)
		{
			bonus -= 10;
			score += 10;
		}
		else if (curTime >= 1 && bonus > 0)
		{
		curTime = 0;
		bonus -= 10;
		}
	}

}

void UIManager::UpScore(int result)
{
	score += result;
}

void UIManager::Set()
{
	score = 0;
	lifeScore = 4;
	bonus = 3000;
	isAcetive = false;
	isEnd = false;
}

void UIManager::Ready()
{
	isAcetive = true;
}

void UIManager::End()
{
	isEnd = true;
}

void UIManager::DownLife()
{
	lifeScore--;
	isAcetive = false;
}

void UIManager::Draw(HDC hdc)
{
	string text = "Score : " + to_string(score);
	TextOut(hdc, map_Size.x * 0.4f, map_Size.y * 0.05f, TEXT(text.c_str()), text.size());
	text = "Bonus : " + to_string(bonus);
	TextOut(hdc, map_Size.x * 0.3f, map_Size.y * 0.05f, TEXT(text.c_str()), text.size());

	for (int i = 0; i < lifeScore; i++)
	{
		life->images[0]->Draw(hdc, map_Size.x*0.6f + (i * (life->images[0]->GetSize().cx * 2 + 10) ), map_Size.y *0.05f, 2);
	}
}

#include "Charlie.h"
#define PI 3.14159265358979f

Charlie::Charlie()
{
	isLoad = false;
}

Charlie::~Charlie()
{
}

void Charlie::Init(int width, int height,int multiple)
{
	if (!isLoad)
	{
		charlie_Move = new Animation();
		charlie_Win = new Animation();
		charlie_Die = new Animation();
		charlie_Move->images.push_back(ResourceManager::GetInstance()->GetBitmap("player0.bmp"));
		charlie_Move->images.push_back(ResourceManager::GetInstance()->GetBitmap("player1.bmp"));
		charlie_Move->images.push_back(ResourceManager::GetInstance()->GetBitmap("player2.bmp"));
		charlie_Win->images.push_back(ResourceManager::GetInstance()->GetBitmap("win.bmp"));
		charlie_Win->images.push_back(ResourceManager::GetInstance()->GetBitmap("win2.bmp"));
		charlie_Die->images.push_back (ResourceManager::GetInstance()->GetBitmap("die.bmp"));
	}

	CollisionManager::GetInstance()->Push(this);

	charlie_Move->delayTime = 0.2f;
	charlie_Move->max = charlie_Move->images.size();
	charlie_Move->offset = 0;

	charlie_Win->delayTime = 0.1f;
	charlie_Win->max = charlie_Win->images.size();

	size.cx = (charlie_Move->images[0]->GetSize().cx * 2);
	size.cy = (charlie_Move->images[0]->GetSize().cy * 2);

	curAni = charlie_Move;
	jumpOffset = 0;
	curTime = 0;
	aniSize = 3;
	input = 0;
	m_Multiple = multiple;

	pos.x = 10;
	pos.y = height * 0.69f;
	
	lion.bottom = 0;
	lion.left = 0;
	lion.right = 0;
	lion.top = 0;

	human.bottom = 0;
	human.left = 0;
	human.right = 0;
	human.top = 0;

	isJump = false;
	isLoad = true;
	isDead = false;
	isWin = false;
}

bool Charlie::Update(float eTime)
{
	curTime += eTime;

	if (isDead)
	{
		return false;
	}

	if (isWin)
	{
		pos.x = 1024 - size.cx *1.4f;
		if (curTime - charlie_Win->oldTime >= 0.1f)
		{
			charlie_Win->oldTime = curTime = 0;
			charlie_Win->offset = (charlie_Win->offset + 1) % charlie_Win->max;
		}

		return false;
	}

	if (isJump)
	{
		pos.y -= cos((jumpOffset / 65.0f)* PI) * 10;
		if (pos.x + (input * 8) < 1024 - size.cx)
		{
			pos.x += (input * 8);
		}

		jumpOffset++;
		charlie_Move->offset = 2;

			if (jumpOffset == 65)
			{
				input = 0;
				pos.y = 524;
				jumpOffset = 0;
				charlie_Move->offset = 0;
				isJump = false;
			}
	}
	else
	{
		if (input != 0)
		{
			if (curTime - charlie_Move->oldTime >= 0.1f)
			{
				charlie_Move->oldTime = curTime = 0;
				charlie_Move->offset = (charlie_Move->offset + 1) % charlie_Move->max;
			}
		}
	}

	if (pos.x < 100)
	{
		if(SceneManager::GetInstance()->getCurScene()->Moving(VK_LEFT))
			pos.x += 8;
	}

	if (pos.x > 450)
	{
		if (SceneManager::GetInstance()->getCurScene()->Moving(VK_RIGHT))
			pos.x -= 8;
	}

	lion.left = pos.x + size.cx * 0.1f;
	lion.top = pos.y + size.cy *0.6;
	lion.right = pos.x + size.cx;
	lion.bottom = pos.y + size.cy * 0.95f;

	human.left = (pos.x + size.cx *0.4f);
	human.top = (pos.y);
	human.right = (pos.x + size.cx * 0.7f);
	human.bottom = (pos.y + size.cy * 0.5f);

	string tag = CollisionManager::GetInstance()->CollisionCheck(this, lion);
	string tag2 = CollisionManager::GetInstance()->CollisionCheck(this, human);

	if (tag != "Non")
	{
		if (tag == "Obstacle")
		{
			isDead = true;
			UIManager::GetInstance()->DownLife();
			curAni = charlie_Die;
			return false;
		}

		if (tag == "End")
		{
			isWin = true;
			UIManager::GetInstance()->End();
			curAni = charlie_Win;
			return false;
		}

		if (tag == "Score")
		{
			UIManager::GetInstance()->UpScore(300);

		}
	}

	if (tag2 != "Non")
	{
		if (tag2 == "Obstacle")
		{
			isDead = true;
			UIManager::GetInstance()->DownLife();
			curAni = charlie_Die;
			return false;
		}

		if (tag2 == "End")
		{
			isWin = true;
			UIManager::GetInstance()->End();
			curAni = charlie_Win;
			return false;
		}

		if (tag2 == "Score")
		{
			UIManager::GetInstance()->UpScore(300);

		}
	}

	return true;
}

void Charlie::Release()
{
	if (isLoad)
	{
		delete charlie_Move;
		delete charlie_Win;
		delete charlie_Die;
		isLoad = false;
	}
}

bool Charlie::Input(float eTime)
{

	if (isDead || isWin)
	{
		return false;
	}

	if (InputManager::GetInstance()->isKeyDown(VK_SPACE))
	{
		isJump = true;
	}
	
	if (!isJump && InputManager::GetInstance()->isKeyPress(VK_RIGHT) && InputManager::GetInstance()->isKeyPress(VK_LEFT))
	{
		input = 0;
		charlie_Move->offset = 0;
	}
	else if (!isJump && InputManager::GetInstance()->isKeyPress(VK_LEFT))
	{
		input = -1;
		Move(VK_LEFT);
	}
	else if (!isJump &&InputManager::GetInstance()->isKeyPress(VK_RIGHT))
	{
		input = 1;
		Move(VK_RIGHT);
	}


	if (!isJump&&InputManager::GetInstance()->isKeyUp(VK_LEFT))
	{
		input = 0;
		charlie_Move->offset = 0;
	}

	if (!isJump&&InputManager::GetInstance()->isKeyUp(VK_RIGHT))
	{
		input = 0;
		charlie_Move->offset = 0;
	}

	return 0;
}

void Charlie::Draw(HDC hdc)
{
	curAni->images[curAni->offset]->Draw(hdc, pos.x, pos.y, m_Multiple);
	DrawFocusRect(hdc, &lion);
	DrawFocusRect(hdc, &human);
}

void Charlie::Move(int keyCode)
{
	if (keyCode == VK_LEFT)
	{
		if (pos.x -8 > 0)
		{
			pos.x -= 8;
		}
	}

	if (keyCode == VK_RIGHT)
	{
		if (pos.x + 8 < 1024 - size.cx)
		{
			pos.x += 8;
		}
	}
}

string Charlie::CollisionCheck(RECT rect)
{
	if (IntersectRect(&RECT(),&lion,&rect))
	{
		return "Charlie";
	}

	if (IntersectRect(&RECT(),&human,&rect))
	{
		return "Charlie";
	}

	return "Non";
}

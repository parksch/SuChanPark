#include "FireRing.h"

FireRing::FireRing()
{
	isLoad = false;
}

FireRing::~FireRing()
{
}

void FireRing::Init(int width, int height, int multiple)
{
	if (!isLoad)
	{
		leftRing = new Animation();
		rightRing = new Animation();
		leftRing->images.push_back(ResourceManager::GetInstance()->GetBitmap("enemy_b.bmp"));
		leftRing->images.push_back(ResourceManager::GetInstance()->GetBitmap("enemy_1b.bmp"));
		rightRing->images.push_back(ResourceManager::GetInstance()->GetBitmap("enemy_f.bmp"));
		rightRing->images.push_back(ResourceManager::GetInstance()->GetBitmap("enemy_1f.bmp"));
	}

	CollisionManager::GetInstance()->Push(this);

	leftRing->delayTime = 0.2f;
	leftRing->offset = 0;
	leftRing->oldTime = 0;
	leftRing->max = leftRing->images.size();

	rightRing->delayTime = 0.2f;
	rightRing->offset = 0;
	rightRing->oldTime = 0;
	rightRing->max = rightRing->images.size();

	size.cx = (leftRing->images[0]->GetSize().cx + rightRing->images[0]->GetSize().cx);
	size.cy = (leftRing->images[0]->GetSize().cy  + rightRing->images[0]->GetSize().cy);

	map_Size = width + size.cx ;

	pos.x = width + size.cx;
	pos.y = height * 0.36f;

	box.bottom = 0;
	box.left = 0;
	box.top = 0;
	box.right = 0;

	scoreBox.bottom = 0;
	scoreBox.left = 0;
	scoreBox.top = 0;
	scoreBox.right = 0;

	m_Multiple = multiple;
	curTime = 0;
	setTime = 0;

	cash.Init(pos.x * 0.98f, pos.y * 1.25f , 2);

	isCash = true;
	isScoreColl = false;
	isMove = false;
	leftDraw = false;
	isLoad = true;
}

bool FireRing::Update(float eTime)
{
	curTime += eTime;

	if (!isMove)
	{
		return false;
	}

	if (curTime - leftRing->oldTime >= leftRing->delayTime)
	{
		leftRing->oldTime = curTime;
		leftRing->offset = (leftRing->offset + 1) % leftRing->max;
	}

	pos.x -= 4;
	box.left = pos.x + size.cx*0.3f;
	box.top = pos.y + size.cy * 0.9f;
	box.right = pos.x + size.cx * 0.9f;
	box.bottom = pos.y + size.cy;

	scoreBox.left = pos.x + (size.cx / 2);
	scoreBox.top = pos.y + size.cy * 0.1f;
	scoreBox.right = pos.x + size.cx;
	scoreBox.bottom = pos.y + size.cy * 0.8f;

	if (isCash)
	{
		cash.Move(-4);
	}

	if (pos.x < -size.cx)
	{
		isMove = false;
		isCash = false;
		pos.x = map_Size + size.cx;
		size.cx = (leftRing->images[0]->GetSize().cx + rightRing->images[0]->GetSize().cx);
		size.cy = (leftRing->images[0]->GetSize().cy + rightRing->images[0]->GetSize().cy);
	}

	return false;
}

void FireRing::Release()
{
	if (isLoad)
	{
		delete leftRing;
		delete rightRing;
		isLoad = false;
	}
}

void FireRing::Draw(HDC hdc)
{
	if (!leftDraw)
	{
		leftRing->images[leftRing->offset]->Draw(hdc, pos.x - (size.cx/2), pos.y, m_Multiple);
		leftDraw = !leftDraw;

		if (isCash)
		{
			cash.Draw(hdc);
		}
	}
	else
	{
		rightRing->images[leftRing->offset]->Draw(hdc, pos.x + (size.cx/2), pos.y, m_Multiple);
		leftDraw = !leftDraw;
		DrawFocusRect(hdc, &box);
		DrawFocusRect(hdc, &scoreBox);
	}

}

void FireRing::Move(int offset)
{
	if (isMove)
	{
		pos.x += offset;
		box.left = pos.x + size.cx*0.3f;
		box.top = pos.y + size.cy * 0.9f;
		box.right = pos.x + size.cx * 0.9f;
		box.bottom = pos.y + size.cy;

		scoreBox.left = pos.x + (size.cx / 2);
		scoreBox.top = pos.y + size.cy * 0.1f;
		scoreBox.right = pos.x + size.cx;
		scoreBox.bottom = pos.y + size.cy * 0.8f;
		cash.Move(offset);
	}
}

void FireRing::Set()
{
	if (!isMove)
	{
		float randSize  = (5 + (rand() % 6)) * 0.1f;
		
		isMove = true;
		isScoreColl = false;
		pos.x = map_Size;
		m_Multiple = 1 + randSize;
		size.cx = (size.cx/2) +  (size.cx/2) * randSize;
		size.cy = (size.cy / 2) + (size.cy / 2) * randSize;

		if (rand() % 10 > 4)
		{
			isCash = true;
			cash.Init(pos.x -size.cx, pos.y * 1.25f, 2);
		}
		else
		{
			isCash = false;
		}
	}
}

string FireRing::CollisionCheck(RECT rect)
{

	if (IntersectRect(&RECT(), &box, &rect))
	{
		return "Obstacle";
	}

	if (IntersectRect(&RECT(),&scoreBox,&rect))
	{
		if (!isScoreColl)
		{
			isScoreColl = true;
			return "Score";
		}
	}

	return "Non";
}

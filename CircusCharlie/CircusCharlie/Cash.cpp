#include "Cash.h"

Cash::Cash()
{
	isLoad = false;
}

Cash::~Cash()
{
}

void Cash::Init(int width, int height,int multiple)
{
	if (!isLoad)
	{
		cash = new Animation();
		cash->images.push_back(ResourceManager::GetInstance()->GetBitmap("cash.bmp"));
	}

	CollisionManager::GetInstance()->Push(this);

	size.cx = cash->images[0]->GetSize().cx * 2;
	size.cy = cash->images[0]->GetSize().cy * 2;
	
	pos.x = width  + size.cx/2;
	pos.y = height ;
	
	box.bottom = 0;
	box.left = 0;
	box.right = 0;
	box.top = 0;

	m_Multiple = multiple;

	isLoad = true;
	isActive = true;
}

bool Cash::Update(float eTime)
{
	return false;
}

void Cash::Release()
{
	if (isLoad)
	{
		delete cash;
		isLoad = false;
	}
}

void Cash::Draw(HDC hdc)
{
	if (isActive)
	{
		cash->images[0]->Draw(hdc, pos.x, pos.y, m_Multiple);
		DrawFocusRect(hdc, &box);
	}
}

void Cash::Move(int offset)
{
	pos.x += offset;
	box.left = pos.x;
	box.top = pos.y;
	box.right = pos.x + size.cx;
	box.bottom = pos.y + size.cy;
}

void Cash::Set(int width)
{
	isActive = true;
	pos.x = width;
}

string Cash::CollisionCheck(RECT rect)
{
	if (!isActive)
	{
		return "Non";
	}

	if (IntersectRect(&RECT(),&box,&rect))
	{
		isActive = false;
		return "Score";
	}

	return "Non";
}

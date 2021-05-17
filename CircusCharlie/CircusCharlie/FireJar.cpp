#include "FireJar.h"

FireJar::FireJar()
{
	isLoad = false;
}

FireJar::~FireJar()
{

}

void FireJar::Init(int width, int height,int multiple)
{
	if (!isLoad)
	{
		fireJar = new Animation();
		fireJar->images.push_back(ResourceManager::GetInstance()->GetBitmap("front.bmp"));
		fireJar->images.push_back(ResourceManager::GetInstance()->GetBitmap("front2.bmp"));
	}
	
	CollisionManager::GetInstance()->Push(this);
	
	map_Size = width;
	curTime = 0;
	m_Multiple = multiple;

	fireJar->delayTime = 0.5f;
	fireJar->oldTime = 0;
	fireJar->offset = 0;
	fireJar->max = fireJar->images.size();	
	
	size.cx = fireJar->images[0]->GetSize().cx * 2;
	size.cy = fireJar->images[0]->GetSize().cy * 2;
	
	box.bottom = 0;
	box.left = 0;
	box.top = 0;
	box.right = 0;
	
	pos.x = width - size.cx * 0.8f;
	pos.y = height * 0.72f;

	cash.Init(pos.x, pos.y - pos.y * 0.1f, multiple);

	isLoad = true;
}

bool FireJar::Update(float eTime)
{
	curTime += eTime;

	if (curTime - fireJar->oldTime >= fireJar->delayTime)
	{
		fireJar->oldTime = curTime;
		fireJar->offset = (fireJar->offset + 1) % fireJar->max;
	}

	return true;
}

void FireJar::Release()
{
	if (isLoad)
	{
		cash.Release();
		delete fireJar;
		isLoad = false;
	}
}

void FireJar::Draw(HDC hdc)
{
	if (pos.x > -fireJar->images[0]->GetSize().cx*2 && pos.x < map_Size)
	{
		fireJar->images[fireJar->offset]->Draw(hdc, pos.x, pos.y, m_Multiple);
		cash.Draw(hdc);
		DrawFocusRect(hdc, &box);
	}
}

void FireJar::Move(int offset)
{
	pos.x += offset;
	cash.Move(offset);
	box.left = pos.x + size.cx * 0.3f;
	box.top = pos.y;
	box.right = pos.x + (size.cx * 0.75f);
	box.bottom = pos.y + size.cy;
}

string FireJar::CollisionCheck(RECT rect)
{
	if (IntersectRect(&RECT(), &box, &rect))
	{
		return "Obstacle";
	}

	return "Non";
}


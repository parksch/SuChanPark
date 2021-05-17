#include "End.h"

End::End()
{
	isLoad = false;
}

End::~End()
{
}

void End::Init(int width, int height,int multiple)
{
	if (!isLoad)
	{
		end = new Animation();
		end->images.push_back(ResourceManager::GetInstance()->GetBitmap("end.bmp"));
	}
	
	CollisionManager::GetInstance()->Push(this);

	size.cx = end->images[0]->GetSize().cx * 2;
	size.cy = end->images[0]->GetSize().cy * 2;

	pos.x = width + size.cx * 0.15f;
	pos.y = height * 0.73f;

	box.bottom = 0;
	box.left = 0;
	box.right = 0;
	box.top = 0;

	m_Multiple = multiple;
	isLoad = true;
}

bool End::Update(float eTime)
{
	return false;
}

void End::Release()
{
	if (isLoad)
	{
		delete end;
		isLoad = true;
	}
}

void End::Draw(HDC hdc)
{
	end->images[0]->Draw(hdc, pos.x, pos.y, m_Multiple);
	DrawFocusRect(hdc, &box);
}

void End::Move(int offset)
{
	pos.x += offset;
	box.left = pos.x;
	box.top = pos.y;
	box.right = pos.x + size.cx;
	box.bottom = pos.y + size.cy *0.3f;
}

string End::CollisionCheck(RECT rect)
{
	if (IntersectRect(&RECT(),&rect,&box))
	{
		return "End";
	}
	return "Non";
}

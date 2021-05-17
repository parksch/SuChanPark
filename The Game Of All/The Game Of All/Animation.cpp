#include "Animation.h"

Animation::Animation()
{
	oldTime = 0;
	offset = 0;
	delayTime = 0;
	max = 0;
}

Animation::~Animation()
{
	vector<BitMap*>().swap(images);
	vector<SIZE>().swap(m_Size);
}

void Animation::Init(float delay)
{
	delayTime = delay;
}

void Animation::Reset()
{
	oldTime = 0;
	offset = 0;
}

void Animation::Push(BitMap * bitmap, int SizeX, int SizeY)
{
	SIZE size;
	size.cx = SizeX;
	size.cy = SizeY;
	images.push_back(bitmap);
	m_Size.push_back(size);
	max = images.size();
}

void Animation::Push(BitMap * bitmap)
{
	SIZE size;
	images.push_back(bitmap);
	size.cx = images[images.size() - 1]->GetSize().cx;
	size.cy = images[images.size() - 1]->GetSize().cy;
	m_Size.push_back(size);
	max = images.size();
}

void Animation::Update(float eTime)
{
	oldTime += eTime;

	if (oldTime >= delayTime)
	{
		oldTime = 0;
		offset = (offset + 1) % max;
	}
}

void Animation::Draw(HDC hdc, int posX, int posY)
{
	images[offset]->Draw(hdc, posX, posY, m_Size[offset].cx, m_Size[offset].cy);
}

void Animation::Draw(HDC hdc, int posX, int posY, int gage, int max)
{
	images[offset]->Draw(hdc, posX, posY, m_Size[offset].cx, m_Size[offset].cy, gage,max);
}

void Animation::Draw(HDC hdc, int x, int y, SIZE size, RECT * rect)
{
	images[offset]->Draw(hdc, x, y, size, rect);
}

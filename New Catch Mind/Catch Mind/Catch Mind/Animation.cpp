#include "Animation.h"

Animation::Animation()
{
	m_DelayTime = 0;
	m_OldTime = 0;
	m_Offset = 0;
	m_Max = 0;
}

Animation::~Animation()
{
	std::vector<BitMap*>().swap(m_Images);
	std::vector<SIZE>().swap(m_Size);
}

void Animation::Init(float delay)
{
	m_DelayTime = delay;
}

void Animation::Push(std::string str, int sizeX, int sizeY)
{
	SIZE size;
	size.cx = sizeX;
	size.cy = sizeY;

	m_Images.push_back(ResourceManager::GetInstance()->GetBitmap(str));
	m_Size.push_back(size);
	m_Max = m_Images.size();
}

void Animation::Push(std::string str)
{
	SIZE size;
	m_Images.push_back(ResourceManager::GetInstance()->GetBitmap(str));
	size.cx = m_Images[m_Images.size() - 1]->GetSize().cx;
	size.cy = m_Images[m_Images.size() - 1]->GetSize().cy;
	m_Size.push_back(size);
	m_Max = m_Images.size();
}

void Animation::Update(float eTime)
{
	m_OldTime += eTime;

	if (m_OldTime >= m_DelayTime)
	{
		m_OldTime = 0;
		m_Offset = (m_Offset + 1) % m_Max;
	}
}

void Animation::Draw(HDC hdc, int posX, int posY)
{
	m_Images[m_Offset]->Draw(hdc, posX, posY, m_Size[m_Offset].cx, m_Size[m_Offset].cy);
}

void Animation::Draw(HDC hdc, int x, int y, SIZE size, RECT * rect)
{
	m_Images[m_Offset]->Draw(hdc, x, y, size, rect);
}

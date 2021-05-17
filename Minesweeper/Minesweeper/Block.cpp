#include "Block.h"
#include "ResourceManager.h"
#include "UIManager.h"

void Block::Init(int width, int height)
{
	pos.x = width;
	pos.y = height;

	hide = ResourceManager::GetInstance()->GetBitmap("block.bmp");
	mine = ResourceManager::GetInstance()->GetBitmap("mine.bmp");
	flag = ResourceManager::GetInstance()->GetBitmap("flag.bmp");

	isHide = true;
	isFlag = false;
	isMine = false;
	isNonBlock = false;
}

void Block::Draw(HDC hdc, int offsetX, int offsetY)
{
	if (isHide)
	{
		if (isFlag)
		{
			flag->Draw(hdc, pos.x * hide->GetSize().cx + offsetX, pos.y * hide->GetSize().cy + offsetY);
		}
		else
		{
			hide->Draw(hdc, pos.x * hide->GetSize().cx + offsetX, pos.y * hide->GetSize().cy + offsetY);
		}
	}
	else
	{
		if (isMine)
		{
			mine->Draw(hdc, pos.x * hide->GetSize().cx + offsetX, pos.y * hide->GetSize().cy + offsetY);
		}
		else
		{
			block->Draw(hdc, pos.x * hide->GetSize().cx + offsetX, pos.y * hide->GetSize().cy + offsetY);
		}
	}

}

void Block::ChanageState(string code)
{
	if (code == "BlockOpen")
	{
		isHide = false;
	}

	if (code == "MineOpen")
	{
		if (isMine)
		{
			isHide = false;
		}
	}

	if (code == "Flag")
	{
		if (isMine)
		{
			isFlag = true;
		}
	}
}

void Block::Numbering(int number)
{
	string str = "block_";
	str = str + to_string(number) + ".bmp";
	block = ResourceManager::GetInstance()->GetBitmap(str);

	if (number == 0)
	{
		isNonBlock = true;
	}
}

string Block::CollisionCheck(POINT mousePos, POINT offset, int key_Code)
{
	RECT rect =
	{
		offset.x + (pos.x * hide->GetSize().cy),
		offset.y + (pos.y * hide->GetSize().cy),
		offset.x + (pos.x * hide->GetSize().cy) + hide->GetSize().cy,
		offset.y + (pos.y * hide->GetSize().cy) + hide->GetSize().cy

	};

	if (PtInRect(&rect, mousePos))
	{
		if (key_Code == MK_LBUTTON)
		{
			if (isFlag)
			{
				return "Blocked";
			}

			if (isMine)
			{
				return "Mine";
			}

			if (isNonBlock)
			{
				return "NonBlock";
			}
			else
			{
				return "NumBlock";
			}
		}

		if (key_Code == MK_RBUTTON)
		{
			if (isHide)
			{
				if (isFlag)
				{
					UIManager::GetInstance()->Change(1);
				}
				else
				{
					UIManager::GetInstance()->Change( -1);
				}
				isFlag = !isFlag;
			}
		}

	}

	return "Blocked";
}


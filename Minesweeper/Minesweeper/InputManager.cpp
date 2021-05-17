#include "InputManager.h"
#include "SceneManager.h"
InputManager* InputManager::m_pThis = nullptr;

InputManager::InputManager()
{
	keyValues.clear();
}

InputManager::~InputManager()
{
	vector<KEY_INFO>().swap(keyValues);
}

void InputManager::RegistKeyCode(int code)
{
	if (isExistKey(code))
	{
		return;
	}
	else
	{
		KEY_INFO key_code;
		key_code.keyCode = code;
		key_code.KeyDown = false;
		key_code.KeyPress = false;
		key_code.KeyUp = false;
		keyValues.push_back(key_code);
	}
}

void InputManager::Update()
{
	for (int i = 0; i < keyValues.size(); i++)
	{
		if (GetKeyState(keyValues[i].keyCode) & 0x8000)
		{
			if (keyValues[i].KeyPress == false)
			{
				keyValues[i].KeyDown = true;
			}
			else
			{
				keyValues[i].KeyDown = false;
			}

			keyValues[i].KeyPress = true;
			keyValues[i].KeyUp = false;
		}
		else
		{
			if (keyValues[i].KeyPress)
			{
				keyValues[i].KeyUp = true;
			}
			else
			{
				keyValues[i].KeyUp = false;
			}

			keyValues[i].KeyDown = false;
			keyValues[i].KeyPress = false;
		}
	}
}

bool InputManager::isExistKey(int key)
{
	for (int i = 0; i < keyValues.size(); i++)
	{
		if (key == keyValues[i].keyCode)
		{
			return true;
		}
	}

	return false;
}

bool InputManager::isKeyUp(int key)
{
	for (int i = 0; i < keyValues.size(); i++)
	{
		if (key == keyValues[i].keyCode)
		{
			return keyValues[i].KeyUp;
		}
	}

	return false;
}

bool InputManager::isKeyDown(int key)
{
	for (int i = 0; i < keyValues.size(); i++)
	{
		if (key == keyValues[i].keyCode)
		{
			return keyValues[i].KeyDown;
		}
	}

	return false;
}

bool InputManager::isKeyPress(int key)
{
	for (int i = 0; i < keyValues.size(); i++)
	{
		if (key == keyValues[i].keyCode)
		{
			return keyValues[i].KeyPress;
		}
	}

	return false;
}

void InputManager::Clear()
{
	vector<KEY_INFO>().swap(keyValues);
}

POINT InputManager::GetMouse()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(SceneManager::GetInstance()->getHWND(), &mouse);
	return mouse;
}

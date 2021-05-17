#pragma once
#include <vector>
#include <Windows.h>
#include "Singleton.h"

class InputManager :public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();
	void RegistKeyCode(int key);
	void Update();
	bool isExistKey(int key);
	bool isKeyUp(int key);
	bool isKeyDown(int key);
	bool isKeyPress(int key);
	void Clear();
	POINT getMousePos();
private:

	struct KEY_INFO
	{
		int keyCode;
		bool KeyPress;
		bool KeyUp;
		bool KeyDown;
	};

	std::vector<InputManager::KEY_INFO> keyValues;
};



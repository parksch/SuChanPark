#pragma once
#include <vector>
#include <Windows.h>
#include "Singleton.h"
using namespace std;

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
	POINT GetMouse();
private:

	struct KEY_INFO
	{
		int keyCode;
		bool KeyPress;
		bool KeyUp;
		bool KeyDown;
	};

	vector<InputManager::KEY_INFO> keyValues;
};


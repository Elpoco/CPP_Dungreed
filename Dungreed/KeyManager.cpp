#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init(void)
{
	_isTyping = FALSE;

	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
	}

	return S_OK;
}

BOOL KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return TRUE;
		}
	}
	else this->setKeyDown(key, false);

	return FALSE;
}

BOOL KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else 
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return TRUE;
	return FALSE;
}

BOOL KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return TRUE;
	return FALSE;
}

void KeyManager::typing(char ch)
{
	int len = strlen(_str);
	if (ch == 8)
	{
		if(len > 0) _str[len - 1] = 0;
	}
	else if (ch == 13)
	{
		_isTyping = FALSE;
	}
	else
	{
		_str[len] = ch;
	}
}

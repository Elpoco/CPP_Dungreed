#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init(void)
{
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

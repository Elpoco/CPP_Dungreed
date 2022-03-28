#include "Stdafx.h"
#include "MessageBoxManager.h"

MessageBoxManager::MessageBoxManager()
{
}

MessageBoxManager::~MessageBoxManager()
{
}

HRESULT MessageBoxManager::init()
{
	return S_OK;
}

void MessageBoxManager::release()
{
}

void MessageBoxManager::showMessage(char* str, char* strTitle)
{
	_ptMouse = { -1,-1 };
	MessageBox(_hWnd, str, strTitle, MB_OK);
}

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

bool KeyManager::isOnceKeyDown(int key)
{
	/*
	GetAsyncKeyState: API �����Լ�
	- � Ű�� �ԷµȰ��� üũ or ���α׷����� Ű�� �Է¹ް� ������
	����Ѵ�. -> �޼��� ť�� �ִ� Ű�� ������ Ȯ��(����)�Ѵ�

	0x0000: ������ �������� ���� ȣ�� �������� �������� ���� ����
	0x0001: ������ �������� �ְ� ȣ�� �������� �������� ���� ����
	0x8000: ������ �������� ���� ȣ�� �������� �����ִ� ����
	0x8001: ������ �������� �ְ� ȣ�� �������� �����ִ� ����
	*/
	// AND ����: & ������
	// ��Ʈ ������ AND ������ �ϰڴ�.
	//	�� �Ѵ� 1�϶��� ����� 1�̰�, �ƴϸ� ����� 0�̴�.
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
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
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}

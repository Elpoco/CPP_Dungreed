#include "Stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init(void)
{
	_timer = new Timer;
	_timer->init();

	return S_OK;
}

void TimeManager::release(void)
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}

void TimeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}

void TimeManager::render(HDC hdc)
{
	char str[256];

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));

	/*
	_DEBUG
	- Release Mode�� �ƴ� Debug�϶��� ����
	�� ������ �ϸ鼭 �׽�Ʈ�� �뵵�� ���ϴ�.
	*/

#ifdef _DEBUG
	// ����� �Ҷ��� assert()�� �̾ƶ�
	if (_timer != nullptr)
	{
		// ������ FramePerSec
		sprintf_s(str, "FPS : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		// ���� �ð�
		sprintf_s(str, "WorldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		// ���� �ð�
		sprintf_s(str, "ElapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}

#else // Release
	if (_timer != nullptr)
	{
		// ������
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}

#endif

}

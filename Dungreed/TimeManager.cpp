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
	- Release Mode가 아닌 Debug일때만 실행
	ㄴ 개발을 하면서 테스트의 용도가 강하다.
	*/

#ifdef _DEBUG
	// 디버그 할때는 assert()로 뽑아라
	if (_timer != nullptr)
	{
		// 프레임 FramePerSec
		sprintf_s(str, "FPS : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		// 월드 시간
		sprintf_s(str, "WorldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		// 갱신 시간
		sprintf_s(str, "ElapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}

#else // Release
	if (_timer != nullptr)
	{
		// 프레임
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}

#endif

}

#include "Stdafx.h"
#include "PlayerManager.h"

using namespace PlayerManagerSet;

PlayerManager::PlayerManager() 
	: _coin(0)
{
}

PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::init()
{
	_dashMaxCnt = _dashCnt = DEFAULT_DASH_CNT;
	_dashChargeTime = DEFAULT_DASH_TIME;

	return S_OK;
}

void PlayerManager::release()
{
}

void PlayerManager::update()
{
	chargeDash();
}

void PlayerManager::render()
{
}

void PlayerManager::dash()
{
	_dashCnt--;
	_dashTime = TIMEMANAGER->getWorldTime();
}

void PlayerManager::chargeDash()
{
	if (_dashMaxCnt == _dashCnt) return;
	if (_dashTime + _dashChargeTime < TIMEMANAGER->getWorldTime() || _isDebug)
	{
		_dashTime = TIMEMANAGER->getWorldTime();
		_dashCnt++;
	}
}

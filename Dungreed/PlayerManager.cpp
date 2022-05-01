#include "Stdafx.h"
#include "PlayerManager.h"

using namespace PlayerManagerSet;

PlayerManager::PlayerManager() 
	: _coin(100)
{
}

PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::init()
{
	_dashMaxCnt = _dashCnt = DEFAULT_DASH_CNT;
	_dashChargeTime = DEFAULT_DASH_TIME;

	_maxHp = _curHp = DEFAULT_HP;


	UIMANAGER->initPlayerHpBar(&_maxHp, &_curHp);

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

void PlayerManager::hit(int dmg)
{
	_curHp -= dmg;
	if (_curHp < 0) _curHp = 0;
}

void PlayerManager::recovery(int hp)
{
	_curHp += hp;
	if (_curHp > _maxHp) _curHp = _maxHp;
}

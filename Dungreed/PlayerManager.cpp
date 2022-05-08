#include "Stdafx.h"
#include "PlayerManager.h"

using namespace PlayerManagerSet;

PlayerManager::PlayerManager()
	: _level(1)
	, _coin(0)
	, _isTrueDmg(FALSE)
	, _power(0)
	, _bulletPower(0)
	, _wrath(0)
	, _patience(0)
	, _greed(0)
	, _atkSpeed(1.0f)
	, _shootSpeed(1.0f)
	, _reloadSpeed(0.0f)
	, _skillCooltime(1.0f)
	, _isDie(FALSE)
	, _isReturn(FALSE)
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
	if (IsOnceKeyDown(KEY::P)) levelUp(1);

	chargeDash();
	
	if (_isDie)
	{
		if (_dieTime + 3.5f < TIMEMANAGER->getWorldTime())
		{
			_isReturn = TRUE;
		}
	}
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
	if (_dashMaxCnt <= _dashCnt)
	{
		_dashCnt = _dashMaxCnt;
		return;
	}
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

void PlayerManager::setDie(BOOL b)
{ 
	_isDie = b; 
	_dieTime = TIMEMANAGER->getWorldTime();
}

void PlayerManager::returnTown()
{
	_isReturn = FALSE;
	_isDie = FALSE;
	updateMaxHp();
}

void PlayerManager::levelUp(int level)
{
	_level += level;
	UIMANAGER->showLevelUp(_level);
}

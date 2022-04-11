#include "Stdafx.h"
#include "Enemy.h"

#include "EnemyHpBar.h"
#include "Effect.h"

Enemy::Enemy()
	: _isAutoLeft(true)
	, _hp(1)
	, _maxHp(1)
	, _startSpawn(FALSE)
	, _isSpawn(FALSE)
	, _rcScan({ 0,0,0,0 })
	, _ptPlayer({ 0,0 })
	, _rcPlayer({ 0,0,0,0 })
	, _isPlayerScan(FALSE)
	, _isDead(FALSE)
	, _isAttack(false)
{
}

Enemy::~Enemy()
{
}

HRESULT Enemy::init()
{
	Unit::init();
	_hpBar = new EnemyHpBar;
	_hpBar->init();

	return S_OK;
}

void Enemy::release()
{
	Unit::release();
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void Enemy::update()
{
	if (!_isSpawn) return;

	Unit::update();
	this->move();
	this->animation();
	_rcScan = RectMakeCenter(_x, _y, _imgWidth * _scanScale.x, _imgHeight * _scanScale.y);
	_hpBar->update(_x, _rc.bottom + ENEMY_HP_BAR_H, _hp / _maxHp);
}

void Enemy::render(HDC hdc)
{
	if (!_startSpawn)
	{
		_startSpawn = true;

		OBJECTMANAGER->addObject(
			ObjectEnum::TYPE::EFFECT_BACK,
			new Effect(
				ImageName::Enemy::enemySpawn,
				_x,
				_y
			)
		);

		doneSpawn();
	}

	if (!_isSpawn) return;

	Unit::render(hdc);

	if(_maxHp != _hp)
		_hpBar->render(hdc);
}

void Enemy::deleteEffect()
{
	OBJECTMANAGER->addObject(
		ObjectEnum::TYPE::EFFECT,
		new Effect(
			ImageName::Enemy::enemyDieSmall,
			_x,
			_y
		)
	);
}

void Enemy::move()
{
	if (_isAutoLeft)
	{
		if (_x < _ptPlayer.x) _isLeft = false;
		else _isLeft = true;
	}
}

void Enemy::animation()
{

}

void Enemy::hitAttack(int dmg)
{
	_hp -= dmg;
	if (_hp < 1)
	{
		_isLive = FALSE;
	}
}

void Enemy::scanPlayer(POINT ptPlayer, RECT rcPlayer)
{
	_isPlayerScan = TRUE;
	_ptPlayer = ptPlayer;
	_rcPlayer = rcPlayer;
}

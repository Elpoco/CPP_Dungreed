#include "Stdafx.h"
#include "Enemy.h"

#include "EnemyHpBar.h"

Enemy::Enemy()
	: _isAutoLeft(true)
	, _curHp(1)
	, _maxHp(1)
	, _startSpawn(FALSE)
	, _isSpawn(FALSE)
	, _rcScan({ 0,0,0,0 })
	, _ptPlayer({ 0,0 })
	, _rcPlayer({ 0,0,0,0 })
	, _isPlayerScan(FALSE)
	, _isDead(FALSE)
	, _isAttack(false)
	, _moveHpBarX(0.0f)
	, _moveHpBarY(0.0f)
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
	_hpBar->update(_x + _moveHpBarX, _rc.bottom + ENEMY_HP_BAR_H + _moveHpBarY, _curHp / _maxHp);
}

void Enemy::render(HDC hdc)
{
	if (!_startSpawn)
	{
		_startSpawn = true;

		SOUNDMANAGER->play(SoundName::Enemy::SpawnEnemy, _sound);

		OBJECTMANAGER->addEffect(
			ImageName::Enemy::sapwn,
			_x,
			_y,
			0,
			ObjectEnum::OBJ_TYPE::EFFECT_BACK
		);

		doneSpawn();
	}

	if (!_isSpawn) return;

	Unit::render(hdc);

	if(_maxHp != _curHp)
		_hpBar->render(hdc);
}

void Enemy::deleteEffect()
{
	SOUNDMANAGER->play(SoundName::Enemy::MonsterDie, _sound);
	ITEMMANAGER->dropItem(Code::ITEM::COIN, _x, _rc.top - 20);
	OBJECTMANAGER->addEffect(
		ImageName::Enemy::dieSmall,
		_x,
		_y
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

void Enemy::hitAttack(int dmg, int dir)
{
	_curHp -= dmg;

	OBJECTMANAGER->addDynamicImageFont(_x, _rc.top, dmg, dir);

	if (_curHp < 1)
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

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

	return S_OK;
}

void Enemy::release()
{
	Unit::release();
}

void Enemy::update()
{
	if (!_isSpawn) return;

	Unit::update();
	this->move();
	this->animation();
	_rcScan = RectMakeCenter(_x, _y, _imgWidth * _scanScale.x, _imgHeight * _scanScale.y);
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
}

void Enemy::deleteEffect()
{
	MAPMANAGER->dieMonster();
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
	if(!PLAYERMANAGER->getTrueDmg())
		dmg -= _info.def;

	if (dmg < 1) dmg = 1;

	_curHp -= dmg;

	OBJECTMANAGER->addDynamicImageFont(_x + RND->getInt(10) - 5, _rc.top + RND->getInt(10) - 5, dmg, dir);
	SOUNDMANAGER->play(SoundName::Enemy::hit, _sound);
	if (_curHp < 1)
	{
		_isLive = FALSE;
		int coinCnt = RND->getInt(5);
		for (int i = 0; i < coinCnt; i++)
		{
			ITEMMANAGER->dropItem(Code::ITEM::COIN, _x, _rc.top - 20, TRUE);
		}
		SOUNDMANAGER->play(SoundName::Enemy::MonsterDie, _sound);
		OBJECTMANAGER->addEffect(
			ImageName::Enemy::dieSmall,
			_x,
			_y
		);
	}
}

void Enemy::settingHpBar()
{
	EnemyHpBar* hpBar = new EnemyHpBar(&_x, &_y, &_maxHp, &_curHp);
	hpBar->settingY(_imgHeight * 0.5f);
	OBJECTMANAGER->addUI(hpBar);
	if (_info.code > Code::UNIT::BOSS) hpBar->setBossHpBar();
}

void Enemy::scanPlayer(POINT ptPlayer, RECT rcPlayer)
{
	_isPlayerScan = TRUE;
	_ptPlayer = ptPlayer;
	_rcPlayer = rcPlayer;
}

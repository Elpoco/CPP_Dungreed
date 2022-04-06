#include "Stdafx.h"
#include "Enemy.h"

Enemy::Enemy() :
	_hp(1),
	_isAutoLeft(true),
	_rcScan({ 0,0,0,0 }),
	_ptPlayer({ 0,0 }),
	_rcPlayer({ 0,0,0,0 }),
	_isPlayerScan(FALSE),
	_isDead(FALSE),
	_state(0),
	_isAttack(false)
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
	Unit::update();
	this->move();
	this->animation();
}

void Enemy::render(HDC hdc)
{
	Unit::render(hdc);
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

void Enemy::scanPlayer(POINT ptPlayer, RECT rcPlayer)
{
	_isPlayerScan = TRUE;
	_ptPlayer = ptPlayer;
	_rcPlayer = rcPlayer;
}

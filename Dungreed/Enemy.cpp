#include "Stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
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
}

void Enemy::render(HDC hdc)
{
	Unit::render(hdc);
}

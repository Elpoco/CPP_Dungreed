#include "Stdafx.h"
#include "BelialBullet.h"

BelialBullet::BelialBullet(string imgName, float x, float y, float moveX, float moveY, float speed, float distance)
	: Bullet(imgName, x, y, moveX, moveY, speed, distance)
{
	this->init();
}

BelialBullet::~BelialBullet()
{
}

HRESULT BelialBullet::init()
{
	Bullet::init();

	return S_OK;
}

void BelialBullet::release()
{
	Bullet::release();
}

void BelialBullet::update()
{
	Bullet::update();
}

void BelialBullet::render(HDC hdc)
{
	Bullet::render(hdc);
}

void BelialBullet::move()
{
}

void BelialBullet::animation()
{
}

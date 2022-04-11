#include "Stdafx.h"
#include "NiflheimPillar.h"

#include "Bullet.h"

NiflheimPillar::NiflheimPillar(float x, float y)
	: _shootAngle(0.0f)
{
	_x = x;
	_y = y;

	_startSpawn = TRUE;
	_isSpawn = TRUE;
}

NiflheimPillar::~NiflheimPillar()
{
}

HRESULT NiflheimPillar::init()
{
	Enemy::init();
	this->initAnimation();

	_isFlying = true;
	
	_bossAngle = GetAngle(_x, _y, *_niflheimX, *_niflheimY);
	_bossDistance = GetDistance(_x, _y, *_niflheimX, *_niflheimY);

	return S_OK;
}

void NiflheimPillar::release()
{
	Enemy::release();
}

void NiflheimPillar::update()
{
	Enemy::update();
	this->move();
	Enemy::updateRect();
	this->animation();

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		OBJECTMANAGER->addObject(
			ObjectEnum::TYPE::ENEMY_OBJ,
			new Bullet(
				ImageName::Enemy::Niflheim::bullet,
				_x,
				_y,
				_shootAngle,
				4.0f,
				1.0f,
				ImageName::Enemy::Belial::bulletEffect
			)
		);
		_shootAngle += PI / 32;
	}
}

void NiflheimPillar::render(HDC hdc)
{
	Enemy::render(hdc);

}

void NiflheimPillar::move()
{
	_x = cosf(_bossAngle) * _bossDistance + *_niflheimX;
	_y = sinf(_bossAngle) * _bossDistance + *_niflheimY;
}

void NiflheimPillar::animation()
{
	if (_frameInfo.x >= 12)
	{
		_frameInfo.startFrameX = 12;
		_frameInfo.tick = 15;
		_imgAngle = GetAngleDeg(_x, _y, *_niflheimX, *_niflheimY) + 90;
		_bossAngle -= 0.01f;
		_rotateCenter = PointMake(_x, _y);
	}
}
void NiflheimPillar::initAnimation()
{
	_vImages.push_back(GPIMAGEMANAGER->findImage(ImageName::Enemy::Niflheim::pillar));
	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
	_frameInfo.maxFrameX = _vImages[0]->getMaxFrameX();
}

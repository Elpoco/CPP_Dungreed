#include "Stdafx.h"
#include "Skel.h"

Skel::Skel(float x, float y)
{
	_x = x;
	_y = y;
}

Skel::~Skel()
{
}

HRESULT Skel::init()
{
	this->initAnimation();
	Enemy::init();

	_info = DBMANAGER->getInfo(Code::UNIT::SKEL);
	_scanScale = { 25, 15 };

	settingHp(_info.hp);

	_attackTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void Skel::release()
{
	Enemy::release();
}

void Skel::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
}

void Skel::render(HDC hdc)
{
	Enemy::render(hdc);

	CAMERAMANAGER->frameRender(hdc, _sword, _x, _y + 10, 0,0, _angleWeapon);
}

void Skel::move()
{
	if (_isPlayerScan)
	{
		_state = IDLE;
		_rcAttack = { 0,0,0,0 };
		_anglePlayer = GetAngle(PointMake(_x, _y), _ptPlayer);

		if (GetDistance(PointMake(_x, _y), _ptPlayer) > 110)
		{
			_x += _moveSpeed * _isLeft ? -1 : 1;
			_state = MOVE;
		}
		else
		{
			if (_attackTime + _info.atkTime < TIMEMANAGER->getWorldTime()) this->attack();
		}
	}

	if (_isLeft)
	{
		if (_atkCnt == 0) _angleWeapon = DegToRad(60);
		else _angleWeapon = DegToRad(210);
	}
	else
	{
		if (_atkCnt == 0) _angleWeapon = DegToRad(120);
		else _angleWeapon = DegToRad(330);
	}
}

void Skel::initAnimation()
{
	_vImages.push_back(FindImage(ImageName::Enemy::SkelIdle));
	_vImages.push_back(FindImage(ImageName::Enemy::SkelWalk));

	_sword = FindImage(ImageName::Enemy::SkelSword);
	_atkCnt = 0;

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	_frameInfo.maxFrameX = _vImages[1]->getMaxFrameX();
}

void Skel::attack()
{
	_attackTime = TIMEMANAGER->getWorldTime();
	_atkCnt = !_atkCnt;

	_rcAttack = OBJECTMANAGER->addEffect(
		ImageName::Effect::Weapon::basicSwing,
		_x + cos(_anglePlayer) * 40,
		_y - sin(_anglePlayer) * 40,
		RadToDeg(_anglePlayer),
		PointMake(_x, _y)
	);
}

void Skel::frameUpdateEvent()
{
}

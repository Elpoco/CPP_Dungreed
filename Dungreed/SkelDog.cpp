#include "Stdafx.h"
#include "SkelDog.h"

SkelDog::SkelDog(float x, float y) :
	_overMove(70),
	_atkCnt(0)
{
	_x = x;
	_y = y;
}

SkelDog::~SkelDog()
{
}

HRESULT SkelDog::init()
{
	Enemy::init();
	this->initAnimation();

	_name = "½ºÄÌ¸®µ¶";
	_scanScale = { 15,6 };
	_isAutoLeft = false;
	_jumpSpeed /= 2;
	settingHp(UnitSet::Enemy::SkelDog::HP);

	return S_OK;
}

void SkelDog::release()
{
	Enemy::release();
}

void SkelDog::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
	this->animation();
}

void SkelDog::render(HDC hdc)
{
	Enemy::render(hdc);
}

void SkelDog::move()
{
	if (_isPlayerScan)
	{
		if (!_isAttack)
		{
			if (_x + (!_isLeft ? -_overMove : _overMove) <= _ptPlayer.x)
			{
				if (_isLeft) _atkCnt++;
				_isLeft = false;
				_state = SKELDOG_MOTION::RUN;
			}
			else if (_x + (_isLeft ? _overMove : -_overMove) > _ptPlayer.x)
			{
				if (!_isLeft) _atkCnt++;
				_isLeft = true;
				_state = SKELDOG_MOTION::RUN;
			}
		}

		if (_isLeft) _x -= _moveSpeed;
		else _x += _moveSpeed;

		if (_atkCnt > 4)
		{
			this->attack();
		}
	}
	
	if (!_isJump)
	{
		_isAttack = false;
	}
}

void SkelDog::animation()
{
}

void SkelDog::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::dogIdle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::dogRun));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::dogDie));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}

void SkelDog::attack()
{
	_atkCnt = 0;
	_isAttack = true;
	Unit::jump();
}

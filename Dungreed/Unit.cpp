#include "Stdafx.h"
#include "Unit.h"

Unit::Unit() :
	_name(""),
	_imgCurrent(0),
	_imgWidth(0.0f),
	_imgHeight(0.0f),
	_isLeft(false),
	_isJump(false),
	_isFall(true),
	_isFlying(false),
	_moveSpeed(UnitSet::MOVE_SPEED),
	_jumpSpeed(UnitSet::JUMP_SPEED),
	_gravity(0.0f),
	_reSize(0)
{
}

Unit::~Unit()
{
}

HRESULT Unit::init()
{
	Object::init();
	
	return S_OK;
}

void Unit::release()
{
	Object::release();
}

void Unit::update()
{
	Object::update();
	this->animation();
	this->move();
	this->updateRect();
	this->checkCollision();
}

void Unit::render(HDC hdc)
{
	Object::render(hdc);
	if (_isDebug)
	{
		CAMERAMANAGER->printRectangle(hdc, _rc, Color::Green);
		CAMERAMANAGER->printPoint(hdc, _rc.GetLeft(), _rc.GetTop(), _x, _y, "x: %d, y: %d");
	}

	if (_vImages[_imgCurrent]->getMaxFrameX() == 0 &&
		_vImages[_imgCurrent]->getMaxFrameY() == 0)
	{
		CAMERAMANAGER->render(hdc, _vImages[_imgCurrent], _rc.GetLeft(), _rc.GetTop());
	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _vImages[_imgCurrent], _rc.GetLeft() - _reSize/2, _rc.GetTop(), _frameInfo.x, _frameInfo.y);
	}
}

void Unit::move()
{
	if (_isFall && !_isFlying)
	{
		_y += _gravity;
		_gravity += UnitSet::GRAVITY;
	}
	
	if (_isJump)
	{
		_y -= _jumpSpeed;
	}
}

void Unit::animation()
{
	_frameInfo.cnt++;

	if (_frameInfo.cnt > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;

		bool checkFrame = _vImages[_imgCurrent]->getMaxFrameX() < _frameInfo.x;
		if (checkFrame) _frameInfo.x = 0;
	}

	if (_isLeft) _frameInfo.y = 1;
	else _frameInfo.y = 0;
}

void Unit::checkCollision()
{
	if (_isCollision[ColliderEnum::DIRECTION::BOTTOM])
	{
		_isFall = false;
		_isJump = false;
		_gravity = 0.0f;
	}
	else
	{
		_isFall = true;
	}

	if (_isCollision[ColliderEnum::DIRECTION::TOP])
	{
		if (_isJump) _isJump = false;
	}
}

void Unit::updateRect()
{
	_rc = RectFMakeCenter(
		_x,
		_y,
		_imgWidth,
		_imgHeight
	);

	this->updateProve();
}

void Unit::updateProve()
{
	_prove[ColliderEnum::LEFT] = PointMake(_rc.GetLeft(), _y);
	_prove[ColliderEnum::RIGHT] = PointMake(_rc.GetRight(), _y);
	_prove[ColliderEnum::TOP] = PointMake(_x, _rc.GetTop());
	_prove[ColliderEnum::BOTTOM] = PointMake(_x, _rc.GetBottom());
	_prove[ColliderEnum::LBOTTOM] = PointMake(_rc.GetLeft(), _rc.GetBottom());
	_prove[ColliderEnum::RBOTTOM] = PointMake(_rc.GetRight(), _rc.GetBottom());
}

void Unit::jump()
{
	_isJump = true;
	_isFall = true;
	_gravity = 0.0f;
	_y -= _jumpSpeed;
}

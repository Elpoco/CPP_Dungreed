#include "Stdafx.h"
#include "Unit.h"

Unit::Unit() :
	_isLeft(false),
	_isJump(false),
	_isFall(false),
	_moveSpeed(UNIT_MOVE_SPEED),
	_jumpSpeed(UNIT_JUMP_SPEED),
	_fallSpeed(UNIT_FALL_SPEED),
	_gravity(UNIT_GRAVITY)
{
}

HRESULT Unit::init(void)
{
	Object::init();
	PixelCollider::init(&_rc, &_x, &_y, &_isJump);
	
	return S_OK;
}

void Unit::release(void)
{
	Object::release();
	PixelCollider::release();
}

void Unit::update(void)
{
	Object::update();
	PixelCollider::update();
	this->move();
	this->animation();
}

void Unit::render(HDC hdc)
{
	Object::render(hdc);
	PixelCollider::render(hdc);
}

void Unit::move(void)
{
	if (_isJump)
	{
		_y -= _jumpSpeed + _fallSpeed;
		_fallSpeed -= _gravity;
	}
}

void Unit::animation(void)
{
	if (_isLeft)
	{
		Object::setFrameY(1);
	}
	else
	{
		Object::setFrameY(0);
	}
}

void Unit::jump(void)
{
}

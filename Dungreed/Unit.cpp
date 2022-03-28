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

HRESULT Unit::init()
{
	Object::init();
	PixelCollider::init(this);
	
	return S_OK;
}

void Unit::release()
{
	Object::release();
	PixelCollider::release();
}

void Unit::update()
{
	Object::update();
	//PixelCollider::update();
	this->move();
	this->animation();
}

void Unit::render(HDC hdc)
{
	Object::render(hdc);
	//PixelCollider::render(hdc);
}

void Unit::move()
{
	if (_isJump)
	{
		if (_isCollision)
		{
			_isJump = false;
			
		}
		else
		{
			_y -= _jumpSpeed + _fallSpeed;
			if (_fallSpeed < 3)
			{
				_fallSpeed -= _gravity;
			}
		}
	}

	//if (_isCollision && _isJump)
	//{
	//	_isJump = false;
	//}
	//
	//if (!_isCollision && !_isJump)
	//{
	//	_y -= _fallSpeed;
	//	_fallSpeed -= _gravity;
	//}
}

void Unit::animation()
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

void Unit::jump()
{
	_isJump = true;
	_fallSpeed = UNIT_FALL_SPEED;
	_isCollision = false;
}

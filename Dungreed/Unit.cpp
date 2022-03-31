#include "Stdafx.h"
#include "Unit.h"

Unit::Unit() :
	_isJump(false),
	_isFall(true),
	_isFlying(false),
	_moveSpeed(UnitSet::MOVE_SPEED),
	_jumpSpeed(UnitSet::JUMP_SPEED),
	_gravity(0.0f)
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
	this->move();
}

void Unit::render(HDC hdc)
{
	Object::render(hdc);
}

void Unit::move()
{
	if (_isJump)
	{
		_y -= _jumpSpeed;
	}

	if (_isFall)
	{
		_y += _gravity;
		_gravity += UnitSet::GRAVITY;
	}

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

void Unit::jump()
{
	_isJump = true;
	_isFall = true;
	_gravity = 0.0f;
}

#include "Stdafx.h"
#include "Unit.h"

Unit::Unit() :
	_isJump(false),
	_isFall(true),
	_isFlying(false),
	_moveSpeed(UnitSet::MOVE_SPEED),
	_jumpSpeed(UnitSet::JUMP_SPEED),
	_fallSpeed(UnitSet::FALL_SPEED),
	_gravity(UnitSet::GRAVITY)
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
	//if (!_isCollision[ColliderEnum::DIRECTION::BOTTOM] && !_isFlying)
	//{
	//	_y -= _fallSpeed;
	//	if (_fallSpeed < 3)
	//	{
	//		_fallSpeed -= _gravity;
	//	}
	//}
}

void Unit::jump()
{
	_isJump = true;
	_fallSpeed = UnitSet::FALL_SPEED;
}

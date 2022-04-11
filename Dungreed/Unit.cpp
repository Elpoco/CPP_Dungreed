#include "Stdafx.h"
#include "Unit.h"

Unit::Unit()
	: _name("")
	, _rcAttack({ 0,0,0,0 })
	, _state(0)
	, _imgCurrent(0)
	, _imgWidth(0.0f)
	, _imgHeight(0.0f)
	, _isStopAnimation(false)
	, _isLeft(false)
	, _isJump(false)
	, _isFall(true)
	, _isFlying(false)
	, _moveSpeed(UnitSet::MOVE_SPEED)
	, _jumpSpeed(UnitSet::JUMP_SPEED)
	, _gravity(0.0f)
	, _rcResize(0)
	, _imgAngle(0)
	, _rotateCenter({ 0,0 })
{
	for (int i = 0; i < ColliderEnum::DIRECTION::DIR_CNT; i++)
		_isCollision[i] = false;
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
		CAMERAMANAGER->printPoint(hdc, _rc.left, _rc.top, _x, _y, "x: %d, y: %d");
	}

	if (_vImages[_imgCurrent]->getMaxFrameX() == 0 &&
		_vImages[_imgCurrent]->getMaxFrameY() == 0)
	{
		CAMERAMANAGER->render(hdc, _vImages[_imgCurrent], _rc.left - _rcResize / 2, _rc.top);
	}
	else
	{
		if (_imgAngle)
		{
			CAMERAMANAGER->frameRender(hdc, _vImages[_imgCurrent], _rc.left - _rcResize / 2, _rc.top, _frameInfo.x, _frameInfo.y, _imgAngle, _rotateCenter);
		}
		else
		{
			CAMERAMANAGER->frameRender(hdc, _vImages[_imgCurrent], _rc.left - _rcResize / 2, _rc.top, _frameInfo.x, _frameInfo.y);
		}
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
	if (_isStopAnimation) return;

	_imgCurrent = _state;

	_frameInfo.cnt++;

	if (_frameInfo.cnt > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;

		bool checkFrame = _vImages[_imgCurrent]->getMaxFrameX() < _frameInfo.x;
		if (checkFrame) _frameInfo.x = _frameInfo.startFrameX;
	}

	if (_isLeft && _vImages[_imgCurrent]->getMaxFrameY() > 1)
	{
		_frameInfo.y = L;
	}
	else 
		_frameInfo.y = R;
}

void Unit::checkCollision()
{
	if (_isCollision[ColliderEnum::DIRECTION::BOTTOM])
	{
		_isFall = false;
		_isJump = false;
		_gravity = 0.0f;
	}
	else if (_isCollision[ColliderEnum::DIRECTION::RB])
	{
		_isFall = false;
		_isJump = false;
		_gravity = 0.0f;
	}
	else if (_isCollision[ColliderEnum::DIRECTION::TOP])
	{
		_isJump = false;
		_isFall = true;
		_gravity = 0.0f;
	}
	else
	{
		_isFall = true;
	}

	//if (_isCollision[ColliderEnum::DIRECTION::LTOP])
	//{
	//	if (_isJump) _isJump = false;
	//}
}

void Unit::pushObject(ColliderEnum::DIRECTION dir, float x, float y)
{
	switch (dir)
	{
	case ColliderEnum::LEFT:
		_x = x + _imgWidth / 2;
		break;
	case ColliderEnum::RIGHT:
		_x = x - _imgWidth / 2;
		break;
	case ColliderEnum::TOP:
		_y = y + _imgHeight / 2;
		break;
	case ColliderEnum::BOTTOM:
		_y = y - _imgHeight / 2;
		break;
	case ColliderEnum::LT:
		break;
	case ColliderEnum::RT:
		break;
	case ColliderEnum::LB:
		break;
	case ColliderEnum::RB:
		break;
	case ColliderEnum::DIR_CNT:
		break;
	default:
		if (x > 0) _x = x - _imgWidth / 2;
		if (y > 0) _y = y - _imgHeight / 2;
		break;
	}
}

void Unit::updateRect()
{
	_rc = RectMakeCenter(
		_x,
		_y,
		_imgWidth,
		_imgHeight
	);
}

void Unit::jump()
{
	_isJump = true;
	_isFall = true;
	_gravity = 0.0f;
	_y -= _jumpSpeed;
}

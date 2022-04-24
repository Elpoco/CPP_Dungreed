#include "Stdafx.h"
#include "Unit.h"

Unit::Unit()
	: _rcAttack({ 0,0,0,0 })
	, _state(0)
	, _imgCurrent(0)
	, _imgWidth(0.0f)
	, _imgHeight(0.0f)
	, _isStopAnimation(false)
	, _isLeft(FALSE)
	, _isJump(FALSE)
	, _isDownJump(FALSE)
	, _isFall(TRUE)
	, _isFlying(FALSE)
	, _isHit(FALSE)
	, _isDash(FALSE)
	, _hitTime(0.0f)
	, _imgAlpha(255)
	, _moveSpeed(UnitSet::MOVE_SPEED)
	, _jumpSpeed(UnitSet::JUMP_SPEED)
	, _gravity(0.0f)
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

	if (_imgAngle)
	{
		CAMERAMANAGER->frameRender(
			hdc, 
			_vImages[_imgCurrent],
			_rcRender.left,
			_rcRender.top,
			_frameInfo.x,
			_frameInfo.y, 
			_imgAngle,
			_rotateCenter
		);
	}
	else
	{
		if (_imgAlpha < 255)
		{
			CAMERAMANAGER->frameRender(
				hdc, 
				_vImages[_imgCurrent],
				_rcRender.left,
				_rcRender.top,
				_frameInfo.x,
				_frameInfo.y,
				_imgAlpha
			);
		}
		else
		{
			CAMERAMANAGER->frameRender(
				hdc, 
				_vImages[_imgCurrent],
				_rcRender.left,
				_rcRender.top,
				_frameInfo.x, 
				_frameInfo.y
			);
		}
	}
	
}

void Unit::move()
{
	if (_isFall && !_isFlying)
	{
		_y += _gravity;
		_gravity += UnitSet::GRAVITY;
		if (_gravity > 4.5f) _isDownJump = FALSE;
	}
	
	if (_isJump) _y -= _jumpSpeed;
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

		if (_frameInfo.x > _vImages[_imgCurrent]->getMaxFrameX())_frameInfo.x = _frameInfo.startFrameX;
	}

	if (_isLeft && _vImages[_imgCurrent]->getMaxFrameY() > 0) _frameInfo.y = L;	
	else _frameInfo.y = R;
}

void Unit::checkCollision()
{
	if (_isCollision[ColliderEnum::DIRECTION::BOTTOM])
	{
		_isFall = FALSE;
		_isJump = FALSE;
		_isDownJump = FALSE;
		_gravity = 0.0f;
	}
	else if (_isCollision[ColliderEnum::DIRECTION::TOP])
	{
		_isJump = FALSE;
		_isFall = TRUE;
		_gravity = 0.0f;
	}
	else
	{
		_isFall = TRUE;
	}
}

void Unit::pushObject(ColliderEnum::DIRECTION dir, float x, float y)
{
	switch (dir)
	{
	case ColliderEnum::LEFT:
		_x = x + _imgWidth * 0.5f - _rcResizeW;
		break;
	case ColliderEnum::RIGHT:
		_x = x - _imgWidth * 0.5f + _rcResizeW;
		break;
	case ColliderEnum::TOP:
		_y = y + _imgHeight * 0.5f;
		break;
	case ColliderEnum::BOTTOM:
		_y = y - _imgHeight * 0.5f;
		break;
	default:
		if (x > 0) _x = x - _imgWidth * 0.5f;
		if (y > 0) _y = y - _imgHeight * 0.5f + 1;
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

	_rc.left += _rcResizeW;
	_rc.right -= _rcResizeW;
	_rc.top += _rcResizeH;
	_rc.bottom -= _rcResizeH;

	_rc.left += _rcMoveX;
	_rc.right += _rcMoveX;
	_rc.top += _rcMoveY;
	_rc.bottom += _rcMoveY;

	_rcRender = RectMakeCenter(
		_x,
		_y,
		_imgWidth,
		_imgHeight
	);
}

void Unit::jump()
{
	_isJump = TRUE;
	_isDownJump = FALSE;
	_isFall = TRUE;
	_gravity = 0.0f;
	_y -= _jumpSpeed;
}

void Unit::downJump()
{
	if (_isDownJump) return;
	_isDownJump = TRUE;
	_isFall = TRUE;
	_gravity = 0.0f;
}

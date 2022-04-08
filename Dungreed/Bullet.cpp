#include "Stdafx.h"
#include "Bullet.h"

Bullet::Bullet(string imgName, float x, float y, float moveX, float moveY, float speed, float distance) :
	_imgName(imgName),
	_startX(x),
	_startY(y),
	_moveX(moveX),
	_moveY(moveY),
	_speed(speed),
	_distance(distance)
{
	this->init();
	_x = x;
	_y = y;
}

Bullet::~Bullet()
{
}

HRESULT Bullet::init()
{
	Object::init();

	_img = IMAGEMANAGER->findImage(_imgName);
	_frameInfo.maxFrameX = _img->getMaxFrameX();

	return S_OK;
}

void Bullet::release()
{
	Object::release();
}

void Bullet::update()
{
	Object::update();
	this->move();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	this->animation();
}

void Bullet::render(HDC hdc)
{
	Object::render(hdc);
	CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
}

void Bullet::move()
{
	_x += _moveX * _speed;
	_y += _moveY * _speed;

	if (GetDistance(_startX, _startY, _x, _y) > _distance)
	{
		_isLive = FALSE;
	}
}

void Bullet::animation()
{
	_frameInfo.cnt++;
	if (_frameInfo.cnt > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;
		if (_frameInfo.x > _frameInfo.maxFrameX)
		{
			_frameInfo.x = 0;
		}
	}
}

#include "Stdafx.h"
#include "Bullet.h"

#include "Effect.h"

Bullet::Bullet(string imgName, float x, float y, float moveX, float moveY, float speed
	, float damage, string destroyImgName, float distance)
	: _imgName(imgName)
	, _startX(x)
	, _startY(y)
	, _moveX(moveX)
	, _moveY(moveY)
	, _speed(speed)
	, _damage(damage)
	, _distance(distance)
	, _destroyImgName(destroyImgName)
{
	_x = x;
	_y = y;

	this->init();
}

Bullet::~Bullet()
{
}

HRESULT Bullet::init()
{
	Object::init();

	_gpImg = GPIMAGEMANAGER->findImage(_imgName);

	if (_gpImg)
	{
		_frameInfo.maxFrameX = _gpImg->getMaxFrameX();
		_frameInfo.maxFrameY = _gpImg->getMaxFrameY();
	}
	else
	{
		_img = IMAGEMANAGER->findImage(_imgName);
		_frameInfo.maxFrameX = _img->getMaxFrameX();
		_frameInfo.maxFrameY = _img->getMaxFrameY();
	}

	// 프레임 이미지인지 확인
	if (_frameInfo.maxFrameX > 0 && _frameInfo.maxFrameY > 0)
	{
		_frameInfo.isFrame = true;
		if (_gpImg)
		{
			_frameInfo.width = _gpImg->getFrameWidth();
			_frameInfo.height = _gpImg->getFrameHeight();
		}
		else
		{
			_frameInfo.width = _img->getFrameWidth();
			_frameInfo.height = _img->getFrameHeight();
		}
	}
	else
	{
		if (_gpImg)
		{
			_frameInfo.width = _gpImg->getWidth();
			_frameInfo.height = _gpImg->getHeight();
		}
		else
		{
			_frameInfo.width = _img->getWidth();
			_frameInfo.height = _img->getHeight();
		}
	}

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

	_rc = RectMakeCenter(_x, _y, _frameInfo.width, _frameInfo.height);

	this->animation();

	
}

void Bullet::render(HDC hdc)
{
	Object::render(hdc);

	if (_img)
	{
		if (_frameInfo.isFrame)
		{
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
		}
		else
		{
			CAMERAMANAGER->render(hdc, _img, _rc.left, _rc.top);
		}
	}
	else
	{
		if (_frameInfo.isFrame)
		{
			CAMERAMANAGER->frameRender(hdc, _gpImg, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
		}
		else
		{
			CAMERAMANAGER->render(hdc, _gpImg, _rc.left, _rc.top);
		}
	}
}

void Bullet::deleteEffect()
{
	if (_destroyImgName != "")
	{
		OBJECTMANAGER->addObject(
			ObjectEnum::TYPE::EFFECT,
			new Effect(
				_destroyImgName,
				_x,
				_y
			)
		);
	}
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

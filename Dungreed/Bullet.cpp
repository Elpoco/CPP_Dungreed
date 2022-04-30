#include "Stdafx.h"
#include "Bullet.h"

Bullet::Bullet(string imgName, float x, float y, float angle, float speed
	, int damage, string destroyImgName, float distance, BOOL super, BOOL imgRotate)
	: _imgName(imgName)
	, _startX(x)
	, _startY(y)
	, _angle(angle)
	, _speed(speed)
	, _damage(damage)
	, _distance(distance)
	, _destroyImgName(destroyImgName)
	, _isGP(FALSE)
	, _isSuper(super)
	, _isImgRotate(imgRotate)
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

	_img = FindImage(_imgName);
	
	if (GPIMAGEMANAGER->findImage(_imgName)) _isGP = TRUE;

	_frameInfo.maxFrameX = _img->getMaxFrameX();
	_frameInfo.maxFrameY = _img->getMaxFrameY();

	if (_frameInfo.maxFrameX > 0 || _frameInfo.maxFrameY > 0)
	{
		_frameInfo.isFrame = true;
		_frameInfo.width = _img->getFrameWidth();
		_frameInfo.height = _img->getFrameHeight();
	}
	else
	{
		_frameInfo.width = _img->getWidth();
		_frameInfo.height = _img->getHeight();
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
	if (_frameInfo.isFrame) this->animation();

	this->move();

	_rc = RectMakeCenter(_x, _y, _frameInfo.width, _frameInfo.height);

}

void Bullet::render(HDC hdc)
{
	Object::render(hdc);

	if (_isGP)
	{
		CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y, RadToDeg(_angle) + 90, PointMake(_x, _y));
	}
	else
	{
		if (_isImgRotate)
		{
			CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _frameInfo.x, _frameInfo.y, _angle);
		}
		else
		{
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
		}
	}
}

void Bullet::deleteEffect()
{
	if (_destroyImgName != "")
	{
		if (GPIMAGEMANAGER->findImage(_destroyImgName))
		{
			OBJECTMANAGER->addEffect(
				_destroyImgName,
				_x,
				_y,
				RadToDeg(_angle),
				PointMake(_x, _y)
			);
		}
		else
		{
			if (_isImgRotate)
			{
				OBJECTMANAGER->addEffect(
					_destroyImgName,
					_x,
					_y,
					_angle
				);
			}
			else
			{
				OBJECTMANAGER->addEffect(
					_destroyImgName,
					_x,
					_y
				);
			}
		}
	}
}

void Bullet::stopObject()
{
	if (_isSuper) return;
	Object::deleteObject();
}

void Bullet::collisionObject()
{
	Object::deleteObject();
}

void Bullet::move()
{
	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

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

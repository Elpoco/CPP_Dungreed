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
	, _isSuper(super)
	, _isImgRotate(imgRotate)
	, _isAuto(FALSE)
	, _scale(1.0f)
	, _isPenetrate(FALSE)
	, _isFind(FALSE)
{
	_x = x;
	_y = y;

	if (damage < 1) damage = 1;

	this->init();
}

Bullet::~Bullet()
{
}

HRESULT Bullet::init()
{
	Object::init();

	_img = FindImage(_imgName);

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

	_initTime = TIMEMANAGER->getWorldTime();

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

	_rc = RectMakeCenter(_x, _y, _frameInfo.width * _scale, _frameInfo.height * _scale);
}

void Bullet::render(HDC hdc)
{
	Object::render(hdc);

	if (_isImgRotate)
	{
		CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _frameInfo.x, _frameInfo.y, _angle, _scale);
	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
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
	if (_isPenetrate) return;
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

	if (_isAuto && _isFind)
	{
		float angle = GetAngle(_x, _y, _ptEnemy.x, _ptEnemy.y);
		float moveAngle = 0.08f;
		_speed += 0.01f;

		angle -= _angle;
		angle = angle < -PI ? angle + 2 * PI : angle > PI ? angle - 2 * PI : angle;
		angle = angle < -moveAngle ? -moveAngle : angle > moveAngle ? moveAngle : angle;
		_angle += angle;
	}
}

void Bullet::animation()
{
	_frameInfo.cnt++;
	if (_frameInfo.cnt % 2)
	{
		if (_imgName == ImageName::Item::Weapon::StarBullet)
		{
			OBJECTMANAGER->addEffect(
				ImageName::Effect::Weapon::StarParticle,
				_x,
				_y,
				100, ObjectEnum::OBJ_TYPE::EFFECT_BACK
			);
		}
	}
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

void Bullet::findEnemy(POINT pt)
{
	if (_initTime + 0.2f > TIMEMANAGER->getWorldTime()) return;
	_isFind = TRUE;
	_ptEnemy = pt;
}

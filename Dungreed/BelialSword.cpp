#include "Stdafx.h"
#include "BelialSword.h"

#include "Effect.h"

BelialSword::BelialSword(float x, float y, POINT* ptPlayer)
	: _startX(x)
	, _startY(y)
	, _ptPlayer(ptPlayer)
	, _angle(0.0f)
	, _degree(0)
	, _isShoot(false)
	, _isMoving(true)
{
	_x = x;
	_y = y;

	this->init();
}

BelialSword::~BelialSword()
{
}

HRESULT BelialSword::init()
{
	Object::init();

	_img = GPIMAGEMANAGER->findImage(ImageName::Enemy::Belial::belialSword);
	_initTime = TIMEMANAGER->getWorldTime();

	OBJECTMANAGER->addObject(
		ObjectEnum::TYPE::EFFECT,
		new Effect(
			ImageName::Enemy::Belial::belialSwordEffect,
			_x,
			_y
		)
	);

	return S_OK;
}

void BelialSword::release()
{
	Object::release();
}

void BelialSword::update()
{
	Object::update();
	this->move();
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());

	if (_initTime + SWORD_LIFE_TIME < TIMEMANAGER->getWorldTime())
		Object::deleteObject();
}

void BelialSword::render(HDC hdc)
{
	Object::render(hdc);
	CAMERAMANAGER->render(hdc, _img, _rc.left, _rc.top, _degree);
	if (_isDebug)
	{
		CAMERAMANAGER->printRectangle(hdc, _rc, Color::Red);
	}
}

void BelialSword::deleteEffect()
{
	OBJECTMANAGER->addObject(
		ObjectEnum::TYPE::EFFECT,
		new Effect(
			ImageName::Enemy::Belial::belialSwordEffect,
			_x,
			_y
		)
	);
}

void BelialSword::collisionObject()
{
	//Object::deleteObject();
	
}

void BelialSword::move()
{
	if (GetDistance(_startX, _startY, _x, _y) > 800) return;

	if (_isShoot || _initTime + 3 < TIMEMANAGER->getWorldTime())
	{
		_isShoot = true;
		if (_isMoving)
		{
			_x += cosf(_angle) * SWORD_SPEED;
			_y -= sinf(_angle) * SWORD_SPEED;
		}
	}
	else
	{
		_angle = GetAngle(_x, _y, _ptPlayer->x, _ptPlayer->y);
		_degree = _angle / PI * 180 + 90; 
	}
}

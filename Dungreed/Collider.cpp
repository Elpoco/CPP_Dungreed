#include "Stdafx.h"
#include "Collider.h"

#include "Object.h"

Collider::Collider(Object* object)
{
	_object = object;
}

Collider::~Collider()
{
}

HRESULT Collider::init()
{
	return S_OK;
}

void Collider::release()
{
}

void Collider::update()
{
}

void Collider::render(HDC hdc)
{
	this->settingProve();

	if (_isDebug)
	{
		for (int i = 0; i < ColliderEnum::DIRECTION::DIR_CNT; i++)
			CAMERAMANAGER->printRectangleCenter(hdc, _prove[i].x, _prove[i].y, 10, 10);

		POINT pt = TILEMANAGER->getTilePt(_prove[ColliderEnum::DIRECTION::BOTTOM]);
		CAMERAMANAGER->printPoint(hdc, _prove[ColliderEnum::DIRECTION::BOTTOM].x, _prove[ColliderEnum::DIRECTION::BOTTOM].y, pt.y, pt.x);
	}
}

void Collider::settingProve()
{
	RECT rc = _object->getRect();

	_prove[ColliderEnum::DIRECTION::TOP]	= PointMake(_object->getX(), rc.top);
	_prove[ColliderEnum::DIRECTION::LEFT]	= PointMake(rc.left, _object->getY());
	_prove[ColliderEnum::DIRECTION::RIGHT]	= PointMake(rc.right, _object->getY());
	_prove[ColliderEnum::DIRECTION::BOTTOM]	= PointMake(_object->getX(), rc.bottom);
	//_prove[ColliderEnum::DIRECTION::BOTTOM].x = _object->getX();
	//_prove[ColliderEnum::DIRECTION::BOTTOM].y = _object->getHeight() / 2;
}

void Collider::tileCollision()
{
	if (TILEMANAGER->getTileType(_prove[ColliderEnum::DIRECTION::BOTTOM]) == MapToolEnum::TILE_TYPE::BLOCK)
		_object->setCollision(ColliderEnum::DIRECTION::BOTTOM, true);
	else
		_object->setCollision(ColliderEnum::DIRECTION::BOTTOM, false);
}

#include "Stdafx.h"
#include "Collider.h"

Collider::Collider()
{
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
		for (int i = 0; i < DIRECTION::DIR_CNT; i++)
			CAMERAMANAGER->printRectangleCenter(hdc, _prove[i].X, _prove[i].Y, 10, 10);

		PointF pt = TILEMANAGER->getTilePt(_prove[DIRECTION::BOTTOM]);
		CAMERAMANAGER->printPoint(hdc, 
			_prove[DIRECTION::BOTTOM].X, _prove[DIRECTION::BOTTOM].Y, 
			pt.Y, pt.X);
	}
}

void Collider::settingProve()
{
	//RectF rc = _object->getRect();
	//
	//_prove[DIRECTION::TOP]	= PointMake(_object->getX(), rc.GetTop());
	//_prove[DIRECTION::LEFT]	= PointMake(rc.GetLeft(), _object->getY());
	//_prove[DIRECTION::RIGHT]	= PointMake(rc.GetRight(), _object->getY());
	//_prove[DIRECTION::BOTTOM]	= PointMake(_object->getX(), rc.GetBottom());
	//_prove[ColliderEnum::DIRECTION::BOTTOM].x = _object->getX();
	//_prove[ColliderEnum::DIRECTION::BOTTOM].y = _object->getHeight() / 2;
}

void Collider::tileCollision()
{
	//if (TILEMANAGER->getTileType(_prove[DIRECTION::BOTTOM]) == MapToolEnum::TILE_TYPE::BLOCK)
	//	_object->setCollision(DIRECTION::BOTTOM, true);
	//else
	//	_object->setCollision(DIRECTION::BOTTOM, false);
}

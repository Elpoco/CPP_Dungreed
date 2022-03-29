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
	this->settingProve();
	if (TILEMANAGER->getTileType(_prove[ColliderInfo::DIRECTION::BOTTOM]) == MapTool::TILE_TYPE::BLOCK)
		_object->setCollision(true);
	else
		_object->setCollision(false);
}

void Collider::render()
{
	if(_isDebug)
		for (int i = 0; i < ColliderInfo::DIRECTION::DIR_CNT; i++)
			RectangleMakeCenter(getMemDC(), _prove[i].x, _prove[i].y, 10, 10);
}

void Collider::settingProve()
{
	RECT rc = _object->getRect();
	//_prove[ColliderInfo::DIRECTION::TOP]	= PointMake(CAMERAMANAGER->getRelX(_object->getX()), CAMERAMANAGER->getRelY(rc.top));
	//_prove[ColliderInfo::DIRECTION::LEFT]	= PointMake(CAMERAMANAGER->getRelX(rc.left), CAMERAMANAGER->getRelY(_object->getY()));
	//_prove[ColliderInfo::DIRECTION::RIGHT]	= PointMake(CAMERAMANAGER->getRelX(rc.right), CAMERAMANAGER->getRelY(_object->getY()));
	//_prove[ColliderInfo::DIRECTION::BOTTOM]	= PointMake(CAMERAMANAGER->getRelX(_object->getX()), CAMERAMANAGER->getRelY(rc.bottom));
}

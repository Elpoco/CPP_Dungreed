#include "Stdafx.h"
#include "CollisionManager.h"

#include "Collider.h"
#include "Object.h"

CollisionManager::CollisionManager() :
	_onTileCollision(false)
{
}

CollisionManager::~CollisionManager()
{
}

HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}

void CollisionManager::update()
{
	viColliders iter = _vColliders.begin();
	for (; iter != _vColliders.end(); ++iter)
	{
		(*iter)->update();
	}
	if (_onTileCollision) this->tileCollision();
}

void CollisionManager::render(HDC hdc)
{
	viColliders iter = _vColliders.begin();
	for (; iter != _vColliders.end(); ++iter)
	{
		(*iter)->render(hdc);
	}
}

void CollisionManager::addObject(Object* object)
{
	_vColliders.push_back(new Collider(object));
}

void CollisionManager::tileCollision()
{
	viColliders iter = _vColliders.begin();
	for (; iter != _vColliders.end(); ++iter)
	{
		(*iter)->tileCollision();
	}
}

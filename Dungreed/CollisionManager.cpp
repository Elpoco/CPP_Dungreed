#include "Stdafx.h"
#include "CollisionManager.h"

#include "Collider.h"
#include "Object.h"

CollisionManager::CollisionManager()
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
}

void CollisionManager::render()
{
	viColliders iter = _vColliders.begin();
	for (; iter != _vColliders.end(); ++iter)
	{
		(*iter)->render();
	}
}

void CollisionManager::addObject(Object* object)
{
	_vColliders.push_back(new Collider(object));
}

void CollisionManager::tileCollision()
{
}

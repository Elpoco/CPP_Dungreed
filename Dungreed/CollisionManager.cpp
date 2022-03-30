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
	_collider = new Collider;

	return S_OK;
}

void CollisionManager::release()
{
}

void CollisionManager::update()
{
	if (_onTileCollision) this->tileCollision();
}

void CollisionManager::render(HDC hdc)
{
	for (Object* obj : *_vObjects)
	{
		//_collider
	}
}

void CollisionManager::tileCollision()
{
	for (Object* obj : *_vObjects)
	{
		//_collider
	}
}

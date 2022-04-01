#include "Stdafx.h"
#include "CollisionManager.h"

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
	if (_onTileCollision) this->tileCollision();
}

void CollisionManager::render(HDC hdc)
{
	if (_isDebug)
	{
		for (Object* obj : *_vObjects)
		{
			PointF* prove = obj->getProve();
			for (int i = 0; i < DIRECTION::DIR_CNT; i++)
			{
				Tile tile = TILEMANAGER->getTile(prove[i]);
				CAMERAMANAGER->printRectangle(hdc, tile.rc, Color::Red);
				if (obj->getCollision((DIRECTION)i))
				{
					CAMERAMANAGER->printRectanglePoint(hdc, prove[i], 10, 10, Color::Red);
				}
				else
				{
					CAMERAMANAGER->printRectanglePoint(hdc, prove[i], 10, 10, Color::Blue);

				}
			}
		}
	}
}

void CollisionManager::tileCollision()
{
	for (Object* obj : *_vObjects)
	{
		PointF* prove = obj->getProve();
		for (int i = 0; i < DIRECTION::DIR_CNT; i++)
		{
			Tile tile = TILEMANAGER->getTile(prove[i]);
			if (tile.type == MapToolEnum::TILE_TYPE::BLOCK)
			{
				obj->setCollision((DIRECTION)i, true);
				collisionBlock(obj, tile, (DIRECTION)i);
			}
			else if (tile.type == MapToolEnum::TILE_TYPE::DIG_L)
			{
				obj->setCollision((DIRECTION)i, true);
			}
			else
				obj->setCollision((DIRECTION)i, false);
		}
	}
}

void CollisionManager::collisionBlock(Object* obj, Tile tile, DIRECTION dir)
{
	switch (dir)
	{
	case DIRECTION::LEFT:
		obj->setX(tile.rc.GetRight() + obj->getWidth() / 2);
		break;
	case DIRECTION::RIGHT:
		obj->setX(tile.rc.GetLeft() - obj->getWidth() / 2);
		break;
	case DIRECTION::TOP:
		obj->setY(tile.rc.GetBottom() + obj->getHeight() / 2);
		break;
	case DIRECTION::BOTTOM:
		obj->setY(tile.rc.GetTop() - obj->getHeight() / 2);
		break;
	default:
		break;
	}
}

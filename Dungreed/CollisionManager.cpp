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
		for(auto pairObject : *_mObjects)
		{
			for (Object* obj : pairObject.second)
			{
				PointF* prove = obj->getProve();
				for (int i = 0; i < DIRECTION::DIR_CNT; i++)
				{
					TILE tile = TILEMANAGER->getTile(prove[i]);
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
}

void CollisionManager::tileCollision()
{
	for (auto pairObject : *_mObjects)
	{
		for (Object* obj : pairObject.second)
		{
			PointF* prove = obj->getProve();
			for (int i = 0; i < DIRECTION::DIR_CNT; i++)
			{
				TILE tile = TILEMANAGER->getTile(prove[i]);

				switch (tile.type)
				{
				case MapToolEnum::TILE_TYPE::BLOCK:
					obj->setCollision((DIRECTION)i, true);
					collisionBlock(obj, tile, (DIRECTION)i);
					break;
				case MapToolEnum::TILE_TYPE::DIG_L:
					if (i == DIRECTION::LBOTTOM)
					{
						obj->setCollision((DIRECTION)i, true);
						collisionBlock(obj, tile, (DIRECTION)i);
					}
					break;
				default:
					obj->setCollision((DIRECTION)i, false);
					break;
				}
			}
		}
	}
}

void CollisionManager::collisionBlock(Object* obj, TILE tile, DIRECTION dir)
{
	switch (dir)
	{
	case DIRECTION::LEFT:
		obj->setX(tile.rc.GetRight() + obj->getRect().Width / 2);
		break;
	case DIRECTION::RIGHT:
		obj->setX(tile.rc.GetLeft() - obj->getRect().Width / 2);
		break;
	case DIRECTION::TOP:
		obj->setY(tile.rc.GetBottom() + obj->getRect().Height / 2);
		break;
	case DIRECTION::BOTTOM:
		obj->setY(tile.rc.GetTop() - obj->getRect().Height / 2);
		break;
	case DIRECTION::LBOTTOM:
		//obj->setX(tile.rc.GetLeft() - obj->getRect().Width / 2);
		//obj->setY(tile.rc.GetTop() - obj->getRect().Height / 2);
		break;
	default:
		break;
	}
}

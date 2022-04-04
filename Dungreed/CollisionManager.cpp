#include "Stdafx.h"
#include "CollisionManager.h"

#include "Object.h"
#include "Enemy.h"

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
	this->enemyScanCollision();
}

void CollisionManager::render(HDC hdc)
{
	if (_isDebug)
	{
		for(auto pairObject : *_mObjects)
		{
			for (Object* obj : pairObject.second)
			{
				// 타일충돌
				PointF* prove = obj->getProve();
				for (int i = 0; i < DIRECTION::DIR_CNT; i++)
				{
					TILE tile = TILEMANAGER->getTile(prove[i]);
					CAMERAMANAGER->printRectangle(hdc, tile.rc, Color::Red);
					if (obj->getCollision((DIRECTION)i))
					{
						CAMERAMANAGER->printRectanglePoint(hdc, prove[i], 5, 5, Color::Red);
					}
					else
					{
						CAMERAMANAGER->printRectanglePoint(hdc, prove[i], 5, 5, Color::Blue);

					}
				}
			}
			if (pairObject.first == ObjectEnum::TYPE::ENEMY)
			{
				for (Object* obj : pairObject.second)
				{
					Enemy* enemy = dynamic_cast<Enemy*>(obj);
					// 스캔박스
					CAMERAMANAGER->printRectangle(hdc, enemy->getScanRect(), 
						(enemy->getPlayerScan() ? Color::Gold : Color::Aqua));
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

void CollisionManager::enemyScanCollision()
{
	auto pairPlayer = _mObjects->find(ObjectEnum::TYPE::PLAYER);
	auto pairEnemy = _mObjects->find(ObjectEnum::TYPE::ENEMY);
	for (Object* player : pairPlayer->second)
	{
		for (Object* obj : pairEnemy->second)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			RectF rcScan = enemy->getScanRect();
			bool isScan = rcScan.Intersect(player->getRect());
			
			if (enemy->getPlayerScan() || isScan)
			{
				enemy->scanPlayer(player->getPt(), player->getRect());
			}
		}
	}
}

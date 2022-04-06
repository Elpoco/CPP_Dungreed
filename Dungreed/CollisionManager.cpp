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
				// 타일충돌 랜더
				RECT rcObj = obj->getRect();
					
				int start = TILEMANAGER->getTileIndex(rcObj.left, rcObj.top);
				int startX = start % MapToolSet::TILE_CNT_X;
				int startY = start - startX;
				int end = TILEMANAGER->getTileIndex(rcObj.right, rcObj.bottom);
				int endX = end % MapToolSet::TILE_CNT_X;
				int endY = end - endX;
					
				for (int y = startY; y <= endY; y+= MapToolSet::TILE_CNT_X)
				{
					for (int x = startX; x <= endX; x++)
					{
						CAMERAMANAGER->printRectangle(hdc, TILEMANAGER->getTile(y + x).rc, Color::AntiqueWhite);
					}
				}
				// 충돌되는 타일 랜더 끝!
				
				// 적 관련 랜더
				if (pairObject.first == ObjectEnum::TYPE::ENEMY)
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
		if (pairObject.first != ObjectEnum::TYPE::PLAYER &&
			pairObject.first != ObjectEnum::TYPE::ENEMY) continue;

		for (Object* obj : pairObject.second)
		{
			RECT rcObj = obj->getRect();

			int start = TILEMANAGER->getTileIndex(rcObj.left, rcObj.top);
			int startX = start % MapToolSet::TILE_CNT_X;
			int startY = start - startX;
			int end = TILEMANAGER->getTileIndex(rcObj.right, rcObj.bottom);
			int endX = end % MapToolSet::TILE_CNT_X;
			int endY = end - endX;

			for (int y = startY; y <= endY; y += MapToolSet::TILE_CNT_X)
			{
				for (int x = startX; x <= endX; x++)
				{
					TILE tile = TILEMANAGER->getTile(y + x);
					obj->setCollision(DIRECTION::BOTTOM, false);
					switch (tile.type)
					{
					case MapToolEnum::TYPE::BLOCK:
						//if (rcObj.bottom >= tile.rc.top)
						//{
							obj->setCollision(DIRECTION::BOTTOM, true);
							obj->pushObject(DIRECTION::BOTTOM, 0, tile.rc.top);
						//}
						break;
					case MapToolEnum::TYPE::DIG_R:
					{
						obj->setCollision(DIRECTION::BOTTOM, true);
						int moveY = rcObj.right - tile.rc.left;
						obj->pushObject(0, tile.rc.bottom - moveY);
						break;
					}
					default:
						break;
					}
				}
			}
		}
	}
}

void CollisionManager::collisionBlock(Object* obj, TILE tile, DIRECTION dir)
{
	switch (dir)
	{
	//case DIRECTION::LEFT:
	//	obj->setX(tile.rc.GetRight() + obj->getRect().Width / 2);
	//	break;
	//case DIRECTION::RIGHT:
	//	obj->setX(tile.rc.GetLeft() - obj->getRect().Width / 2 );
	//	break;
	//case DIRECTION::TOP:
	//	obj->setY(tile.rc.GetBottom() + obj->getRect().Height / 2);
	//	break;
	//case DIRECTION::LTOP:
	//	obj->setX(tile.rc.GetRight() + obj->getRect().Width / 2);
	//	break;
	//case DIRECTION::RTOP:
	//	obj->setX(tile.rc.GetLeft() - obj->getRect().Width / 2 - 1);
	//	break;
	//case DIRECTION::LBOTTOM:
	//case DIRECTION::RBOTTOM:
		//if(obj->is)
		//obj->setY(tile.rc.top - (obj->getRect().bottom - obj->getRect().top) / 2);
		//break;
	//case DIRECTION::LBOTTOM:
		//obj->setX(tile.rc.GetLeft() - obj->getRect().Width / 2);
		//obj->setY(tile.rc.GetTop() - obj->getRect().Height / 2);
		//break;
	default:
		break;
	}
}

void CollisionManager::collisionDiagonal(Object* obj, TILE tile, DIRECTION dir)
{
	switch (dir)
	{
	//case DIRECTION::LBOTTOM:
		//obj->setY(tile.rc.GetTop() - obj->getRect().Height / 2);
	//	break;
	//case DIRECTION::RIGHT:
	//case DIRECTION::RBOTTOM:
		//obj->setY(tile.rc.GetTop() - obj->getRect().Height);
	//	break;
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
			//RectF rcScan = enemy->getScanRect();
			//bool isScan = rcScan.Intersect(rectToRectF(player->getRect()));
			//
			//if (enemy->getPlayerScan() || isScan)
			//{
			//	enemy->scanPlayer(player->getPt(), player->getRect());
			//}
		}
	}
}

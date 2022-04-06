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
				// Ÿ���浹 ����
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
				// �浹�Ǵ� Ÿ�� ���� ��!
				
				// �� ���� ����
				if (pairObject.first == ObjectEnum::TYPE::ENEMY)
				{
					Enemy* enemy = dynamic_cast<Enemy*>(obj);
					// ��ĵ�ڽ�
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
			for (int i = 0; i < DIRECTION::DIR_CNT; i++)
			{
				obj->setCollision((DIRECTION)i, false);
			}

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
					switch (tile.type)
					{
					case MapToolEnum::TYPE::BLOCK:
						if (tile.rc.left < rcObj.right)
						{
							//obj->setCollision(DIRECTION::RIGHT, true);
							//obj->pushObject(DIRECTION::RIGHT, tile.rc.left, 0);
						}

						if (tile.rc.top < rcObj.bottom)// && tile.y > rcObj.bottom)
						{
							obj->setCollision(DIRECTION::BOTTOM, true);
							obj->pushObject(DIRECTION::BOTTOM, 0, tile.rc.top);
						}
						break;
					default:
						break;
					}
					//CAMERAMANAGER->printRectangle(hdc, TILEMANAGER->getTile(y + x).rc, Color::AntiqueWhite);
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

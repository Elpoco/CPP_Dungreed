#include "Stdafx.h"
#include "CollisionManager.h"

#include "Object.h"
#include "Enemy.h"

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
	this->tileCollision();
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
				if (pairObject.first == ObjectEnum::TYPE::PLAYER)
				{
					// 타일충돌 랜더
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
							CAMERAMANAGER->printRectangle(hdc, TILEMANAGER->getTile(y + x).rc, Color::AntiqueWhite);
						}
					}
					// 충돌되는 타일 랜더 끝!
				}
				
				// 적 랜더
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

			float moveX = 0.0f;
			float moveY = 0.0f;

			for (int y = startY; y <= endY; y += MapToolSet::TILE_CNT_X)
			{
				for (int x = startX; x <= endX; x++)
				{
					TILE tile = TILEMANAGER->getTile(y + x);
					switch (tile.type)
					{
					case MapToolEnum::TYPE::DIG_R:
						moveY = obj->getRect().right - tile.rc.left;

						obj->setCollision(DIRECTION::BOTTOM, true);
						obj->pushObject(DIRECTION::NONE, 0, tile.rc.bottom - moveY);
						break;
					case MapToolEnum::TYPE::DIG_L:
						moveY = tile.rc.right - obj->getRect().left;

						obj->setCollision(DIRECTION::BOTTOM, true);
						obj->pushObject(DIRECTION::NONE, 0, tile.rc.bottom - moveY);
						break;
					case MapToolEnum::TYPE::BLOCK:
						obj->setCollision(DIRECTION::BOTTOM, true);
						obj->pushObject(DIRECTION::BOTTOM, 0, tile.rc.top);
						break;
					default:
						break;
					}
				}
			}
		}
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

			// 이전에 플레이어 감지한적 있는지
			if (enemy->getPlayerScan())
			{
				// 감지한적 있으면 정보 제공
				enemy->scanPlayer(player->getPt(), player->getRect());
			}
			else // 감지한적 없으면 체크하기
			{
				RECT tmp;
				if (IntersectRect(&tmp, &player->getRect(), &enemy->getScanRect()))
				{
					// 감지했으면 정보 제공
					enemy->scanPlayer(player->getPt(), player->getRect());
				}
			}
		}
	}
}

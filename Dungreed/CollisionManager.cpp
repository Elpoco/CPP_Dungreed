#include "Stdafx.h"
#include "CollisionManager.h"

#include "Object.h"
#include "Unit.h"
#include "Enemy.h"
#include "Player.h"

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
	this->playerEnemyCollision();
	this->shootingCollision();
}

void CollisionManager::render(HDC hdc)
{
	if (_isDebug)
	{
		for(auto pairObject : *_mObjects)
		{
			for (Object* obj : pairObject.second)
			{
				switch (pairObject.first)
				{
				case ObjectEnum::TYPE::PLAYER:
					renderPlayer(hdc, obj);
					break;
				case ObjectEnum::TYPE::ENEMY:
					renderEnemy(hdc, obj);
					break;
				case ObjectEnum::TYPE::ENEMY_OBJ:
					renderBullet(hdc, obj);
					break;
				default:
					break;
				}
			}
		}
	}
}

void CollisionManager::renderPlayer(HDC hdc, Object* obj)
{
	Player* player = dynamic_cast<Player*>(obj);

	// 타일충돌 랜더
	RECT rcObj = player->getRect();

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
			//CAMERAMANAGER->printRectangle(hdc, TILEMANAGER->getTile(y + x).rc, Color::AntiqueWhite);
		}
	}
	// 타일충돌 랜더

	CAMERAMANAGER->printRectangle(hdc, player->getAtkRect(), Color::Red);
}

void CollisionManager::renderEnemy(HDC hdc, Object* obj)
{
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	//if (!enemy->isSpawn()) continue;
	// 스캔박스
	CAMERAMANAGER->printRectangle(hdc, enemy->getScanRect(),
		(enemy->getPlayerScan() ? Color::Gold : Color::Aqua));
}

void CollisionManager::renderBullet(HDC hdc, Object* obj)
{
	CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Red);
}

void CollisionManager::tileCollision()
{
	for (auto pairObject : *_mObjects)
	{
		switch (pairObject.first)
		{
		// =============
		// # 유닛 충돌 #
		// =============
		case ObjectEnum::TYPE::PLAYER:
		case ObjectEnum::TYPE::ENEMY:
			for (Object* obj : pairObject.second)
			{
				Unit* unit = dynamic_cast<Unit*>(obj);

				for (int i = 0; i < DIRECTION::DIR_CNT; i++)
				{
					unit->setCollision((DIRECTION)i, false);
				}

				RECT rcObj = unit->getRect();

				int start = TILEMANAGER->getTileIndex(rcObj.left, rcObj.top);
				int end	  =	TILEMANAGER->getTileIndex(rcObj.right, rcObj.bottom);
				if (start < 0) return;
				int startX = start % MapToolSet::TILE_CNT_X;
				int startY = start - startX;
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
							moveY = unit->getRect().right - tile.rc.left;

							unit->setCollision(DIRECTION::BOTTOM, true);
							unit->pushObject(DIRECTION::NONE, 0, tile.rc.bottom - moveY);
							break;
						case MapToolEnum::TYPE::DIG_L:
							moveY = tile.rc.right - unit->getRect().left;

							unit->setCollision(DIRECTION::BOTTOM, true);
							unit->pushObject(DIRECTION::NONE, 0, tile.rc.bottom - moveY);
							break;
						case MapToolEnum::TYPE::BLOCK:
							if (tile.x < unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top) 
							{ // 왼쪽
								unit->setCollision(DIRECTION::LEFT, true);
								unit->pushObject(DIRECTION::LEFT, tile.rc.right, 0);
							}
							else if (tile.x > unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top)
							{ // 오른쪽
								unit->setCollision(DIRECTION::RIGHT, true);
								unit->pushObject(DIRECTION::RIGHT, tile.rc.left, 0);
							}
							else if (tile.y > rcObj.bottom)
							{ // 바닥
								unit->setCollision(DIRECTION::BOTTOM, true);
								unit->pushObject(DIRECTION::BOTTOM, 0, tile.rc.top);
							}
							else
							{ // 천장
								unit->setCollision(DIRECTION::TOP, true);
								unit->pushObject(DIRECTION::TOP, 0, tile.rc.bottom);
							}
							break;
						default:
							break;
						}
					}
				}
			}
			break;
		// ==============
		// # 투사체 충돌 #
		// ==============
		case ObjectEnum::TYPE::ENEMY_OBJ:
			for (Object* obj : pairObject.second)
			{
				TILE tile = TILEMANAGER->getTile(obj->getX(), obj->getY());
				if (tile.type == MapToolEnum::TYPE::BLOCK)
				{
					obj->stopObject();
				}
			}
			break;
		default:
			break;
		}
	}
}

void CollisionManager::playerEnemyCollision()
{
	auto pairPlayer = _mObjects->find(ObjectEnum::TYPE::PLAYER);
	auto pairEnemy = _mObjects->find(ObjectEnum::TYPE::ENEMY);
	for (Object* objPlayer : pairPlayer->second)
	{
		Player* player = dynamic_cast<Player*>(objPlayer);
		for (Object* obj : pairEnemy->second)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			//if (!enemy->isSpawn()) continue;

			RECT tmp;
			RECT playerHitBox = player->getRect();
			RECT enemyScanBox = enemy->getScanRect();

			RECT enemyHitBox = enemy->getRect();
			RECT playerAtkBox = player->getAtkRect();

			// 이전에 플레이어 감지한적 있는지
			if (enemy->getPlayerScan())
			{
				// 감지한적 있으면 정보 제공
				enemy->scanPlayer(player->getPt(), playerHitBox);
			}
			else // 감지한적 없으면 체크하기
			{
				if (IntersectRect(&tmp, &playerHitBox, &enemyScanBox))
				{
					// 감지했으면 정보 제공
					enemy->scanPlayer(player->getPt(), playerHitBox);
				}
			}
			// 스캔 끝

			if (IntersectRect(&tmp, &playerAtkBox, &enemyHitBox))
			{
				enemy->hitAttack(2);
			}
		}
	}
}

void CollisionManager::shootingCollision()
{
	auto pairPlayer = _mObjects->find(ObjectEnum::TYPE::PLAYER);
	auto pairEnemyObj = _mObjects->find(ObjectEnum::TYPE::ENEMY_OBJ);

	for (Object* objPlayer : pairPlayer->second)
	{
		Player* player = dynamic_cast<Player*>(objPlayer);

		for (Object* obj : pairEnemyObj->second)
		{
			RECT tmp;
			RECT rcPlayer = player->getRect();
			RECT rcObj = obj->getRect();

			if (IntersectRect(&tmp, &rcPlayer, &rcObj))
			{
				obj->collisionObject();
			}
		}
	}
}

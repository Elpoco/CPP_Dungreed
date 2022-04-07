#include "Stdafx.h"
#include "CollisionManager.h"

#include "Object.h"
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
					// Ÿ���浹 ����
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
					// �浹�Ǵ� Ÿ�� ���� ��!
				}
				
				// �� ����
				else if (pairObject.first == ObjectEnum::TYPE::ENEMY)
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
			RECT tmp;
			RECT playerHitBox = player->getRect();
			RECT enemyScanBox = enemy->getScanRect();

			RECT enemyHitBox = enemy->getRect();
			RECT playerAtkBox = player->getAtkRect();

			// ������ �÷��̾� �������� �ִ���
			if (enemy->getPlayerScan())
			{
				// �������� ������ ���� ����
				enemy->scanPlayer(player->getPt(), playerHitBox);
			}
			else // �������� ������ üũ�ϱ�
			{
				if (IntersectRect(&tmp, &playerHitBox, &enemyScanBox))
				{
					// ���������� ���� ����
					enemy->scanPlayer(player->getPt(), playerHitBox);
				}
			}
			// ��ĵ ��

			if (IntersectRect(&tmp, &playerAtkBox, &enemyHitBox))
			{
				enemy->hitAttack(1);
			}
		}
	}
}

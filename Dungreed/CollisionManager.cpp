#include "Stdafx.h"
#include "CollisionManager.h"

#include "Object.h"
#include "Unit.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "DropItem.h"

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
	collisionTile();
	collisionPlayerEnemy();
	collisionShooting();
	collisionButton();
	collisionItem();
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
				case ObjectEnum::TYPE::PLAYER_OBJ:
					renderBullet(hdc, obj);
					break;
				case ObjectEnum::TYPE::UI_FRONT:
				case ObjectEnum::TYPE::UI:
				case ObjectEnum::TYPE::BUTTON:
					renderUI(hdc, obj);
					break;
				case ObjectEnum::TYPE::ITEM_DROP:
					renderItem(hdc, obj);
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

	// Ÿ���浹 ����
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
			CAMERAMANAGER->printRectangle(hdc, TILEMANAGER->getTile(y + x).rc, Color::AntiqueWhite);
		}
	}

	// ���� �ڽ�
	CAMERAMANAGER->printRectangle(hdc, player->getAtkRect(), Color::Red);
}

void CollisionManager::renderEnemy(HDC hdc, Object* obj)
{
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	// ��ĵ�ڽ�
	CAMERAMANAGER->printRectangle(
		hdc, 
		enemy->getScanRect(),
		(enemy->getPlayerScan() ? Color::Gold : Color::Aqua)
	);

	// ���� �ڽ�
	CAMERAMANAGER->printRectangle(hdc, enemy->getAtkRect(), Color::Red);
}

void CollisionManager::renderBullet(HDC hdc, Object* obj)
{
	CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Red);
}

void CollisionManager::renderUI(HDC hdc, Object* obj)
{
	UI* ui = dynamic_cast<UI*>(obj);
	if (!ui->isShow()) return;

	if (ui->isFixed())
	{
		PrintRectangleColor(hdc, obj->getRect(), Color::Blue);
	}
	else
	{
		CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Blue);
	}
}

void CollisionManager::renderItem(HDC hdc, Object* obj)
{
	CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::YellowGreen);
}

void CollisionManager::collisionTile()
{
	for (auto pairObject : *_mObjects)
	{
		switch (pairObject.first)
		{
		// =============
		// # ���� �浹 #
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
						case MapToolEnum::OBJECT::BLOCK_R:
						case MapToolEnum::OBJECT::DOWN_R:
							moveY = unit->getRect().right - tile.rc.left;
							unit->setCollision(DIRECTION::BOTTOM, true);
							if (moveY > TILE_SIZE) continue;
							unit->pushObject(DIRECTION::NONE, 0, tile.rc.bottom - moveY);
							return;
						case MapToolEnum::OBJECT::BLOCK_L:
						case MapToolEnum::OBJECT::DOWN_L:
							moveY = unit->getRect().left - tile.rc.right;
							unit->setCollision(DIRECTION::BOTTOM, true);
							if (abs(moveY) > TILE_SIZE) continue;
							unit->pushObject(DIRECTION::NONE, 0, tile.rc.bottom + moveY);
							return;
						case MapToolEnum::OBJECT::BLOCK:
							if (tile.x < unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top) 
							{ // ����
								unit->setCollision(DIRECTION::LEFT, true);
								unit->pushObject(DIRECTION::LEFT, tile.rc.right, 0);
							}
							else if (tile.x > unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top)
							{ // ������
								unit->setCollision(DIRECTION::RIGHT, true);
								unit->pushObject(DIRECTION::RIGHT, tile.rc.left, 0);
							}
							else if (tile.y > rcObj.bottom)
							{ // �ٴ�
								unit->setCollision(DIRECTION::BOTTOM, true);
								unit->pushObject(DIRECTION::BOTTOM, 0, tile.rc.top);
							}
							else
							{ // õ��
								unit->setCollision(DIRECTION::TOP, true);
								unit->pushObject(DIRECTION::TOP, 0, tile.rc.bottom);
							}
							break;
						case MapToolEnum::OBJECT::DOWN:
							if (tile.y > rcObj.bottom)
							{ // �ٴ�
								unit->setCollision(DIRECTION::BOTTOM, true);
								unit->pushObject(DIRECTION::BOTTOM, 0, tile.rc.top);
							}
						default:
							break;
						}
					}
				}
			}
			break;
		// ==============
		// # ����ü �浹 #
		// ==============
		case ObjectEnum::TYPE::ENEMY_OBJ:
		case ObjectEnum::TYPE::PLAYER_OBJ:
			for (Object* obj : pairObject.second)
			{
				TILE tile = TILEMANAGER->getTile(obj->getX(), obj->getY());
				if (tile.type == MapToolEnum::OBJECT::BLOCK)
				{
					obj->stopObject();
					obj->collisionObject();
				}
			}
			break;
		// ==============
		// # ������ �浹 #
		// ==============
		case ObjectEnum::TYPE::ITEM_DROP:
			for (Object* obj : pairObject.second)
			{
				TILE tile = TILEMANAGER->getTile(obj->getX(), obj->getRect().bottom);
				if (tile.type == MapToolEnum::OBJECT::BLOCK)
				{
					obj->stopObject();
					obj->pushObject(DIRECTION::BOTTOM, tile.rc.top);
				}
			}
			break;
		default:
			break;
		}
	}
}

void CollisionManager::collisionPlayerEnemy()
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
			RECT enemyScanBox = enemy->getScanRect();
			RECT playerHitBox = player->getRect();
			RECT enemyAtkBox = enemy->getAtkRect();

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

			// �÷��̾� ����
			if (IntersectRect(&tmp, &playerAtkBox, &enemyHitBox))
			{
				enemy->hitAttack(player->getDmg(), enemy->getX() > player->getX());
			}
			// �� ����
			if (IntersectRect(&tmp, &playerHitBox, &enemyAtkBox))
			{
				player->hitAttack(enemy->getDmg(), player->getX() > enemy->getX());
			}
		}
	}
}

void CollisionManager::collisionShooting()
{
	auto pairPlayer = _mObjects->find(ObjectEnum::TYPE::PLAYER);
	auto pairEnemyObj = _mObjects->find(ObjectEnum::TYPE::ENEMY_OBJ);
	auto pairEnemy = _mObjects->find(ObjectEnum::TYPE::ENEMY);
	auto pairPlayerObj = _mObjects->find(ObjectEnum::TYPE::PLAYER_OBJ);

	// �÷��̾ ���� �Ѿ˿� �±�
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
				player->hitAttack(obj->getDmg(), player->getX() > obj->getX());
			}
		}
	}

	// ���Ͱ� �÷��̾� �Ѿ˿� �±�
	for (Object* objEnemy : pairEnemy->second)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(objEnemy);

		for (Object* obj : pairPlayerObj->second)
		{
			RECT tmp;
			RECT rcEnemy = enemy->getRect();
			RECT rcObj = obj->getRect();
			
			if (IntersectRect(&tmp, &rcEnemy, &rcObj))
			{
				obj->collisionObject();
				enemy->hitAttack(obj->getDmg(), enemy->getX() > obj->getX());
			}
		}
	}
}

void CollisionManager::collisionButton()
{
	auto pairButton = _mObjects->find(ObjectEnum::TYPE::BUTTON);

	for (Object* objButton : pairButton->second)
	{
		Button* btn = dynamic_cast<Button*>(objButton);

		if (!btn->isShow()) continue;
		
		RECT rcBtn = btn->getRect();

		btn->setOff();

		if (PtInRect(&rcBtn, _ptMouse))
		{
			btn->setOn();
			if (IsOnceKeyUp(KEY::CLICK_L))
			{
				btn->onClick();
				return;
			}
		}
	}
}

void CollisionManager::collisionItem()
{
	auto pairPlayer = _mObjects->find(ObjectEnum::TYPE::PLAYER);
	auto pairItemObj = _mObjects->find(ObjectEnum::TYPE::ITEM_DROP);

	for (Object* objPlayer : pairPlayer->second)
	{
		Player* player = dynamic_cast<Player*>(objPlayer);

		for (Object* obj : pairItemObj->second)
		{
			DropItem* item = dynamic_cast<DropItem*>(obj);
			Code::ITEM code = item->getCode();

			RECT tmp;
			RECT rcPlayer = player->getRect();
			RECT rcObj = obj->getRect();

			if (IntersectRect(&tmp, &rcPlayer, &rcObj))
			{
				player->getItem(code);
				obj->collisionObject();
				ITEMMANAGER->getItemEffect(code, obj->getX(), rcObj.top, player->getX() > obj->getX());
			}
		}
	}
}

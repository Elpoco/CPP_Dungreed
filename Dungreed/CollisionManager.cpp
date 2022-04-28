#include "Stdafx.h"
#include "CollisionManager.h"

#include "Object.h"
#include "Unit.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "DropItem.h"
#include "NPC.h"

using namespace ObjectEnum;
using namespace MapToolEnum;
using namespace TileSet;

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
	collisionNpc();
	collisionDungeonObj();
}

void CollisionManager::render(HDC hdc)
{
	if (_isDebug)
	{
		for (auto pairObject : *_mObjects)
		{
			for (Object* obj : pairObject.second)
			{
				switch (pairObject.first)
				{
				case OBJ_TYPE::PLAYER:
					renderPlayer(hdc, obj);
					break;
				case OBJ_TYPE::ENEMY:
					renderEnemy(hdc, obj);
					break;
				case OBJ_TYPE::ENEMY_OBJ:
				case OBJ_TYPE::PLAYER_OBJ:
					renderBullet(hdc, obj);
					break;
				case OBJ_TYPE::UI_FRONT:
				case OBJ_TYPE::UI:
				case OBJ_TYPE::BUTTON:
					renderUI(hdc, obj);
					break;
				case OBJ_TYPE::ITEM_DROP:
					renderItem(hdc, obj);
					break;
				case OBJ_TYPE::NPC:
					renderNpc(hdc, obj);
					break;
				case OBJ_TYPE::DUNGEON:
				case OBJ_TYPE::DUNGEON_OBJ:
					renderDungeonObj(hdc, obj);
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

	// Ÿ���浹 ����
	RECT rcObj = player->getRect();

	int start = TILEMANAGER->getTileIndex(rcObj.left, rcObj.top);
	int startX = start % TILE_CNT_X;
	int startY = start - startX;
	int end = TILEMANAGER->getTileIndex(rcObj.right, rcObj.bottom);
	int endX = end % TILE_CNT_X;
	int endY = end - endX;

	if (endX == 0) endX = startX;

	for (int y = startY; y <= endY; y += TILE_CNT_X)
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

void CollisionManager::renderNpc(HDC hdc, Object* obj)
{
	CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Snow);
}

void CollisionManager::renderDungeonObj(HDC hdc, Object* obj)
{
	CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Snow);
}

void CollisionManager::collisionTile()
{
	// Ÿ�ϰ� ������Ʈ �浹 ����
	for (auto pairObject : *_mObjects)
	{
		switch (pairObject.first)
		{
		case OBJ_TYPE::PLAYER:
		case OBJ_TYPE::ENEMY:
			// =============
			// # ���� �浹 #
			// =============
			unitTileCollision(pairObject.second);
			break;
		case OBJ_TYPE::ENEMY_OBJ:
		case OBJ_TYPE::PLAYER_OBJ:
			// ==============
			// # ����ü �浹 #
			// ==============
			for (Object* obj : pairObject.second)
			{
				TILE tile = TILEMANAGER->getTile(obj->getX(), obj->getY());
				if (tile.type == MAP_OBJ::BLOCK   ||
					tile.type == MAP_OBJ::BLOCK_L ||
					tile.type == MAP_OBJ::BLOCK_R)
				{
					obj->stopObject();
					obj->collisionObject();
				}
			}
			break;
		case OBJ_TYPE::ITEM_DROP:
			// ==============
			// # ������ �浹 #
			// ==============
			for (Object* obj : pairObject.second)
			{
				TILE tile = TILEMANAGER->getTile(obj->getX(), obj->getRect().bottom);
				if (tile.type == MAP_OBJ::BLOCK ||
					tile.type == MAP_OBJ::DOWN)
				{
					obj->stopObject();
					obj->pushObject(DIR::BOTTOM, tile.rc.top);
				}
			}
			break;
		default:
			break;
		}
	}
}

void CollisionManager::unitTileCollision(ObjectManager::vObjects vObjects)
{
	for (Object* obj : vObjects)
	{
		Unit* unit = dynamic_cast<Unit*>(obj);
		RECT rcObj = unit->getRect();

		if(rcObj.left <= 0) unit->pushObject(DIR::LEFT, 0, 0);
		if (rcObj.right >= TileSet::TOTAL_TILE_X) unit->pushObject(DIR::RIGHT, TileSet::TOTAL_TILE_X, 0);

		for (int i = 0; i < DIR::DIR_CNT; i++)
		{
			unit->setCollision((DIR)i, false);
		}

		int start = TILEMANAGER->getTileIndex(rcObj.left, rcObj.top);
		int end = TILEMANAGER->getTileIndex(rcObj.right, rcObj.bottom);
		if (start < 0) return;
		int startX = start % TILE_CNT_X;
		int startY = start - startX;
		int endX = end % TILE_CNT_X;
		int endY = end - endX;

		if (endX == 0) endX = startX;

		float moveX = 0.0f;
		float moveY = 0.0f;

		for (int y = startY; y <= endY; y += TILE_CNT_X)
		{
			for (int x = startX; x <= endX; x++)
			{
				TILE tile = TILEMANAGER->getTile(y + x);

				switch (tile.type)
				{
				case MAP_OBJ::DOWN_R:	case MAP_OBJ::DOWN_L:
					if (unit->isDash()) break;
					if (unit->isDownJumping()) break;
					if (unit->isFlying()) break;

				case MAP_OBJ::BLOCK_R:	case MAP_OBJ::BLOCK_L:
					if (unit->isJumping()) break;

					if (tile.type == DOWN_R ||
						tile.type == BLOCK_R)
						moveY = rcObj.right - tile.rc.left;
					else 
						moveY = tile.rc.right - rcObj.left;

					if (moveY >= TILE_SIZE || moveY <= 0) continue;

					unit->pushObject(DIR::NONE, 0, tile.rc.bottom - moveY + 2);

					return;

				case MAP_OBJ::BLOCK:
					if (tile.x < unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top)
					{ // ����
						unit->pushObject(DIR::LEFT, tile.rc.right, 0);
					}
					else if (tile.x > unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top)
					{ // ������
						unit->pushObject(DIR::RIGHT, tile.rc.left, 0);
					}
					else if (tile.y > rcObj.bottom)
					{ // �ٴ�
						unit->pushObject(DIR::BOTTOM, 0, tile.rc.top);
					}
					else
					{ // õ��
						unit->pushObject(DIR::TOP, 0, tile.rc.bottom);
					}
					break;

				case MAP_OBJ::DOWN:
					if (unit->isJumping()) break;
					if (unit->isDownJumping()) break;
					if (unit->isDash()) break;
					if (unit->isFlying()) break;

					if (tile.y > rcObj.bottom)
					{ // �ٴ�
						unit->pushObject(DIR::BOTTOM, 0, tile.rc.top);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void CollisionManager::collisionPlayerEnemy()
{
	auto pairPlayer = _mObjects->find(OBJ_TYPE::PLAYER);
	auto pairEnemy = _mObjects->find(OBJ_TYPE::ENEMY);
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
	auto pairPlayer = _mObjects->find(OBJ_TYPE::PLAYER);
	auto pairEnemyObj = _mObjects->find(OBJ_TYPE::ENEMY_OBJ);
	auto pairEnemy = _mObjects->find(OBJ_TYPE::ENEMY);
	auto pairPlayerObj = _mObjects->find(OBJ_TYPE::PLAYER_OBJ);

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
	auto pairButton = _mObjects->find(OBJ_TYPE::BUTTON);

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
	auto pairPlayer = _mObjects->find(OBJ_TYPE::PLAYER);
	auto pairItemObj = _mObjects->find(OBJ_TYPE::ITEM_DROP);

	for (Object* objPlayer : pairPlayer->second)
	{
		Player* player = dynamic_cast<Player*>(objPlayer);

		for (Object* obj : pairItemObj->second)
		{
			DropItem* item = dynamic_cast<DropItem*>(obj);
			Code::ITEM code = item->getCode();

			RECT tmp;
			RECT rcPlayer = player->getRect();
			RECT rcObj = item->getRect();

			if (IntersectRect(&tmp, &rcPlayer, &rcObj) && item->isStop())
			{
				player->getItem(code);
				item->collisionObject();
				item->pickUpPlayer(player->getX() > item->getX());
			}
		}
	}
}

void CollisionManager::collisionNpc()
{
	auto pairPlayer = _mObjects->find(OBJ_TYPE::PLAYER);
	auto pairNpc = _mObjects->find(OBJ_TYPE::NPC);

	for (Object* objPlayer : pairPlayer->second)
	{
		Player* player = dynamic_cast<Player*>(objPlayer);

		for (Object* obj : pairNpc->second)
		{
			NPC* npc = dynamic_cast<NPC*>(obj);

			RECT tmp;
			RECT rcPlayer = player->getRect();
			RECT rcObj = npc->getRect();

			if (IntersectRect(&tmp, &rcPlayer, &rcObj))
			{
				npc->collisionObject();
			}
		}
	}
}

void CollisionManager::collisionDungeonObj()
{
	auto pairPlayer = _mObjects->find(OBJ_TYPE::PLAYER);
	auto pairDungeon = _mObjects->find(OBJ_TYPE::DUNGEON);
	auto pairDungeonObj = _mObjects->find(OBJ_TYPE::DUNGEON_OBJ);

	for (Object* objPlayer : pairPlayer->second)
	{
		Player* player = dynamic_cast<Player*>(objPlayer);

		for (Object* obj : pairDungeon->second)
		{
			RECT tmp;
			RECT rcPlayer = player->getRect();
			RECT rcObj = obj->getRect();

			if (IntersectRect(&tmp, &rcPlayer, &rcObj))
			{
				obj->collisionObject();
			}
		}

		for (Object* obj : pairDungeonObj->second)
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

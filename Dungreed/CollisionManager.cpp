#include "Stdafx.h"
#include "CollisionManager.h"

#include "Object.h"
#include "Unit.h"
#include "Enemy.h"
#include "Player.h"
#include "Button.h"
#include "DropItem.h"
#include "NPC.h"
#include "Bullet.h"

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

	// 타일충돌 랜더
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

	// 공격 박스
	CAMERAMANAGER->printRectangle(hdc, player->getAtkRect(), Color::Red);
}

void CollisionManager::renderEnemy(HDC hdc, Object* obj)
{
	Enemy* enemy = dynamic_cast<Enemy*>(obj);

	// 스캔박스
	CAMERAMANAGER->printRectangle(
		hdc,
		enemy->getScanRect(),
		(enemy->getPlayerScan() ? Color::Gold : Color::Aqua)
	);

	// 공격 박스
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
	if(obj->isRender())
		CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Snow);
}

void CollisionManager::renderDungeonObj(HDC hdc, Object* obj)
{
	CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Snow);
}

void CollisionManager::collisionTile()
{
	// 타일과 오브젝트 충돌 관리
	for (auto pairObject : *_mObjects)
	{
		switch (pairObject.first)
		{
		case OBJ_TYPE::PLAYER:
		case OBJ_TYPE::ENEMY:
			// =============
			// # 유닛 충돌 #
			// =============
			unitTileCollision(pairObject.second);
			break;
		case OBJ_TYPE::ENEMY_OBJ:
		case OBJ_TYPE::PLAYER_OBJ:
			// ==============
			// # 투사체 충돌 #
			// ==============
			for (Object* obj : pairObject.second)
			{
				TILE tile = TILEMANAGER->getTile(obj->getX(), obj->getY());

				if (tile.type == MAP_OBJ::BLOCK   ||
					tile.type == MAP_OBJ::BLOCK_L ||
					tile.type == MAP_OBJ::BLOCK_R)
				{
					obj->stopObject();
					//obj->collisionObject();
				}
			}
			break;
		case OBJ_TYPE::ITEM_DROP:
		case OBJ_TYPE::DUNGEON_OBJ:
			// ============================
			// # 아이템, 던전 오브젝트 충돌 #
			// ============================
			for (Object* obj : pairObject.second)
			{
				TILE tile = TILEMANAGER->getTile(obj->getX(), obj->getRect().bottom);
				TILE leftTile = TILEMANAGER->getTile(obj->getRect().left, obj->getY());
				TILE rightTile = TILEMANAGER->getTile(obj->getRect().right, obj->getY());
				RECT rcObj = obj->getRect();

				float moveX = 0.0f;
				float moveY = 0.0f;

				if (leftTile.type == MAP_OBJ::BLOCK)
				{
					obj->pushObject(DIR::LEFT, leftTile.rc.right);
				}

				if (rightTile.type == MAP_OBJ::BLOCK)
				{
					obj->pushObject(DIR::RIGHT, leftTile.rc.left);
				}

				switch (tile.type)
				{
				case MAP_OBJ::BLOCK:
				case MAP_OBJ::DOWN:
					if (tile.y > rcObj.bottom)
					{
						obj->pushObject(DIR::BOTTOM, tile.rc.top);
						obj->stopObject();
					}

					break;
				case MAP_OBJ::BLOCK_L:
				case MAP_OBJ::DOWN_L:
				case MAP_OBJ::BLOCK_R:
				case MAP_OBJ::DOWN_R:
					if (tile.type == DOWN_R || tile.type == BLOCK_R)
					{
						moveY = rcObj.right - tile.rc.left;
					}
					else
					{
						moveY = tile.rc.right - rcObj.left;
					}

					obj->pushObject(DIR::BOTTOM, tile.rc.bottom - moveY + 2);
					obj->stopObject();
					break;
				default:
					break;
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

					if (tile.type == DOWN_R || tile.type == BLOCK_R)
					{
						moveY = rcObj.right - tile.rc.left;
					}
					else
					{
						moveY = tile.rc.right - rcObj.left;
					}

					if (moveY >= TILE_SIZE) { unit->setCollision(DIR::BOTTOM, true); continue; }
					if( moveY <= 0) continue;
					

					unit->pushObject(DIR::NONE, 0, tile.rc.bottom - moveY + 2);

					return;

				case MAP_OBJ::DOWN:
					if (unit->isJumping()) break;
					if (unit->isDownJumping()) break;
					if (unit->isDash()) break;
					if (unit->isFlying()) break;

					if (tile.y > rcObj.bottom)
					{ // 바닥
						unit->pushObject(DIR::BOTTOM, 0, tile.rc.top);
					}
					break;

				case MAP_OBJ::BLOCK:
					if (tile.x < unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top)
					{ // 왼쪽
						unit->pushObject(DIR::LEFT, tile.rc.right, 0);
					}
					else if (tile.x > unit->getX() && tile.y < rcObj.bottom && tile.y > rcObj.top)
					{ // 오른쪽
						unit->pushObject(DIR::RIGHT, tile.rc.left, 0);
					}
					else if (tile.y < rcObj.top && tile.rc.left < unit->getX() && tile.rc.right > unit->getX())
					{ // 천장
						unit->pushObject(DIR::TOP, 0, tile.rc.bottom);
					}
					else if (tile.y > rcObj.bottom && tile.rc.left <= unit->getX() && tile.rc.right >= unit->getX())
					{ // 바닥
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

			// 플레이어 공격
			if (IntersectRect(&tmp, &playerAtkBox, &enemyHitBox))
			{
				enemy->hitAttack(player->getDmg(), enemy->getX() > player->getX());
			}
			// 적 공격
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

	// 플레이어가 몬스터 총알에 맞기
	for (Object* objPlayer : pairPlayer->second)
	{
		Player* player = dynamic_cast<Player*>(objPlayer);
		for (Object* obj : pairEnemyObj->second)
		{
			RECT tmp;
			RECT rcPlayer = player->getRect();
			RECT rcAttack = player->getAtkRect();
			RECT rcObj = obj->getRect();

			BOOL check = CAMERAMANAGER->checkObjectInCamera(
				obj->getX(), 
				obj->getY(),
				rcObj.right - rcObj.left,
				rcObj.bottom - rcObj.top
			);

			if (check) continue;
			
			// 적 총알 부수기
			//if (IntersectRect(&tmp, &rcAttack, &rcObj))
			//{
			//	obj->collisionObject();
			//	continue;
			//}
		
			if (IntersectRect(&tmp, &rcPlayer, &rcObj))
			{
				obj->collisionObject();
				player->hitAttack(obj->getDmg(), player->getX() > obj->getX());
			}
		}
	}

	// 몬스터가 플레이어 총알에 맞기
	for (Object* obj : pairPlayerObj->second)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(obj);
		bullet->eraseEnemy();
		for (Object* objEnemy : pairEnemy->second)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(objEnemy);
			RECT tmp;
			RECT rcEnemy = enemy->getRect();
			RECT rcObj = bullet->getRect();

			if (bullet->isAuto()) bullet->findEnemy(enemy->getPt());

			if (enemy->findAtkBulletTime(bullet->getInitTime()) && IntersectRect(&tmp, &rcEnemy, &rcObj))
			{
				bullet->collisionObject();
				enemy->hitAttack(bullet->getDmg(), enemy->getX() > bullet->getX());
				if (bullet->getPenetrate()) enemy->setAtkBulletTime(bullet->getInitTime());
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
				if (player->getItem(code))
				{
					item->collisionObject();
					item->pickUpPlayer(player->getX() > item->getX());
				}
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

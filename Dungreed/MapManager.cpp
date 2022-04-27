#include "Stdafx.h"
#include "MapManager.h"

#include "Door.h"

MapManager::MapManager()
	: _unitCnt(0)
	, _isClear(FALSE)
{
}

MapManager::~MapManager()
{
}

HRESULT MapManager::init()
{
	for (int i = 0; i < DIR::DIR_CNT; i++)
	{
		_door[i] = new Door((DIR)i, 0, 0);
		OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::DUNGEON, _door[i]);
	}

	return S_OK;
}

void MapManager::release()
{
}

void MapManager::update()
{
	checkMonster();

}

void MapManager::render(HDC hdc)
{
}

void MapManager::settingDungeon()
{
	_mapCode = TILEMANAGER->getCurrentMapCode();
	_mapInfo = DBMANAGER->getInfo(_mapCode);
	
	settingDoor();
	settingMonster();
}

void MapManager::settingDoor()
{
	for (int i = 0; i < DIR::DIR_CNT; i++)
	{
		_ptDoor[i] = { TileSet::TILE_CNT_X ,TileSet::TILE_CNT_Y };
	}

	TILEMANAGER->getDoorPos(_ptDoor);

	for (int i = 0; i < DIR::DIR_CNT; i++)
	{
		_door[i]->setTileX(_ptDoor[i].x);
		_door[i]->setTileY(_ptDoor[i].y);
	}
}

void MapManager::settingMonster()
{
	_unitCnt = 0;

	for (int i = 0; i < UnitSet::MAX_SPAWN; i++)
	{
		if (_mapInfo.arrSpawnInfo[i].unit == Code::UNIT::NONE) break;
		_unitCnt++;
		OBJECTMANAGER->addEnemy(
			_mapInfo.arrSpawnInfo[i].unit,
			_mapInfo.arrSpawnInfo[i].ptSpawn.x,
			_mapInfo.arrSpawnInfo[i].ptSpawn.y
		);
	}

	if (_unitCnt != 0)
	{
		_isClear = FALSE;
		closeDoor();
	}
}

void MapManager::chageRoom(DIR dir)
{
	switch (dir)
	{
	case Direction::LEFT:
		TILEMANAGER->loadMap(FileName::DungeonStart);
		settingDungeon();
		OBJECTMANAGER->getPlayer()->setX(_door[DIR::RIGHT]->getX() - TILE_SIZE * 2);
		OBJECTMANAGER->getPlayer()->setY(_door[DIR::RIGHT]->getY() + TILE_SIZE * 2);
		break;
	case Direction::TOP:
		TILEMANAGER->loadMap(FileName::Dungeon01);
		settingDungeon();
		OBJECTMANAGER->getPlayer()->setX(_door[DIR::BOTTOM]->getX() + TILE_SIZE * 2);
		OBJECTMANAGER->getPlayer()->setY(_door[DIR::BOTTOM]->getY() - TILE_SIZE * 2);
		break;
	case Direction::RIGHT:
		TILEMANAGER->loadMap(FileName::Niflheim);
		settingDungeon();
		OBJECTMANAGER->getPlayer()->setX(_door[DIR::LEFT]->getX() + TILE_SIZE * 2);
		OBJECTMANAGER->getPlayer()->setY(_door[DIR::LEFT]->getY() + TILE_SIZE * 2);
		break;
	case Direction::BOTTOM:
		TILEMANAGER->loadMap(FileName::Belial);
		settingDungeon();
		OBJECTMANAGER->getPlayer()->setX(CENTER_X);
		OBJECTMANAGER->getPlayer()->setY(CENTER_Y);
		break;
	default:
		break;
	}

	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::ITEM_DROP);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::PLAYER_OBJ);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::ENEMY_OBJ);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::DUNGEON_OBJ);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::EFFECT);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::EFFECT_BACK);

	UIMANAGER->updateMiniMap();
}

void MapManager::openDoor()
{
	for (int i = 0; i < DIR::DIR_CNT; i++)
	{
		_door[i]->openDoor();
	}
}

void MapManager::closeDoor()
{
	for (int i = 0; i < DIR::DIR_CNT; i++)
	{
		_door[i]->closeDoor();
	}
}

void MapManager::checkMonster()
{
	if (!_isClear && _unitCnt == 0)
	{
		_isClear = TRUE;
		openDoor();
		if (_mapInfo.ptTresure.x != 0)
		{
			OBJECTMANAGER->addTresure(_mapInfo.ptTresure.x, _mapInfo.ptTresure.y);
		}
	}
}

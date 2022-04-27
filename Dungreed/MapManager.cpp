#include "Stdafx.h"
#include "MapManager.h"

#include "Door.h"

using namespace MapManagerSet;

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

	_imgParticle[0] = FindImage(ImageName::Dungeon::sqaure4);
	_imgParticle[1] = FindImage(ImageName::Dungeon::sqaure5);

	return S_OK;
}

void MapManager::release()
{
}

void MapManager::update()
{
	checkMonster();
	makeParticle();
}

void MapManager::render(HDC hdc)
{
	renderParticle(hdc);
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

void MapManager::makeParticle()
{
	for (int i = 0; i < PARTICLE_CNT; i++)
	{
		if (_particle[i].isOn) continue;
		_particle[i].isOn = true;
		_particle[i].imgIdx = RND->getInt(PARTICLE_IMG);
		_particle[i].dir = (DIR)0;
		_particle[i].startX = RND->getFromIntTo(0, WINSIZE_X);
		_particle[i].startY = RND->getFromIntTo(0, WINSIZE_Y);
		_particle[i].startX = _particle[i].startX - _imgParticle[_particle[i].imgIdx]->getWidth() * 0.5f;
		_particle[i].startY = _particle[i].startY - _imgParticle[_particle[i].imgIdx]->getHeight() * 0.5f;
		_particle[i].x = _particle[i].startX;
		_particle[i].y = _particle[i].startY;
		_particle[i].speed = RND->getFromFloatTo(0.5f, 1.0f);
		_particle[i].alpha = RND->getFromIntTo(100, 200);
		break;
	}

	for (int i = 0; i < PARTICLE_CNT; i++)
	{
		if (!_particle[i].isOn) continue;

		_particle[i].alpha--;
		if (_particle[i].dir == DIR::LEFT)		_particle[i].x += _particle[i].speed;
		else if (_particle[i].dir == DIR::RIGHT) _particle[i].x -= _particle[i].speed;
		else if (_particle[i].dir == DIR::TOP)	_particle[i].y += _particle[i].speed;
		else									_particle[i].y -= _particle[i].speed;

		int distance = GetDistance(
			_particle[i].startX,
			_particle[i].startY,
			_particle[i].x,
			_particle[i].y
		);
		if (distance > 50) _particle[i].isOn = false;
	}
}

void MapManager::renderParticle(HDC hdc)
{
	for (int i = 0; i < PARTICLE_CNT; i++)
	{
		if (!_particle[i].isOn) continue;
		CAMERAMANAGER->render(
			hdc,
			_imgParticle[_particle[i].imgIdx],
			_particle[i].x,
			_particle[i].y,
			_particle[i].alpha
		);
	}
}

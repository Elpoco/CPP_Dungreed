#include "Stdafx.h"
#include "MapManager.h"

#include "GameScene.h"
#include "Door.h"

using namespace MapManagerSet;

MapManager::MapManager()
	: _unitCnt(0)
	, _isClear(FALSE)
	, _isSnowMap(FALSE)
{
}

MapManager::~MapManager()
{
}

HRESULT MapManager::init()
{
	initMap();

	for (int i = 0; i < DIR::DIR_CNT; i++)
	{
		_door[i] = new Door((DIR)i, 0, 0);
		OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::DUNGEON, _door[i]);
	}

	_imgParticle[0] = FindImage(ImageName::Dungeon::sqaure4);
	_imgParticle[1] = FindImage(ImageName::Dungeon::sqaure5);

	_imgSnow = IMAGEMANAGER->findImage(ImageName::Dungeon::Snow);
	_snowX = 0.0f;
	_snowY = 0.0f;
	_rcSnow = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);

	_layer = IMAGEMANAGER->findImage(ImageName::Dungeon::subBg);
	_background = IMAGEMANAGER->findImage(ImageName::Dungeon::bgLayer0);

	_imgStartDoor = FindImage(ImageName::Dungeon::StartDoor);
	_doorFrame.maxFrameX = _imgStartDoor->getMaxFrameX();
	_isFirst = TRUE;
	_enterTime = TIMEMANAGER->getWorldTime();

	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::ITEM_DROP);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::PLAYER_OBJ);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::ENEMY_OBJ);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::DUNGEON_OBJ);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::EFFECT);
	OBJECTMANAGER->clearObjects(ObjectEnum::OBJ_TYPE::EFFECT_BACK);

	OBJECTMANAGER->addNPC(Code::NPC::DUNGEON_SHOP, 838, 619, Code::MAP::DUNGEON_SHOP);

	return S_OK;
}

void MapManager::release()
{
}

void MapManager::update()
{
	checkMonster();
	if (_isSnowMap)
	{
		updateSnow();
	}
	else
	{
		makeParticle();
		updateParticle();
	}

	if (_isFirst && _enterTime + 1.0f < TIMEMANAGER->getWorldTime())
	{
		if (_doorFrame.cnt++ > _doorFrame.maxFrameX)
		{
			_doorFrame.cnt = 0;
			_doorFrame.x++;
			if (_doorFrame.x == 5) SOUNDMANAGER->play(SoundName::Dungeon::CloseSteelDoor, _sound);
			if (_doorFrame.x > _doorFrame.maxFrameX)
			{
				_isFirst = FALSE;
			}
		}
	}
}

void MapManager::render(HDC hdc)
{
	switch (_arrMapCode[_curLocation])
	{
	case Code::MAP::DUNGEON_START:
		CAMERAMANAGER->frameRender(hdc, _imgStartDoor, 214, 430, _doorFrame.x, 0);
		break;
	case Code::MAP::DUNGEON_SHOP:
	case Code::MAP::DUNGEON_FOOD:
		CAMERAMANAGER->render(hdc, ImageName::Dungeon::DungeonInn, 335, 348); 
		if (_curLocation == 14) break;
		CAMERAMANAGER->render(hdc, ImageName::Dungeon::InDungeonShop, 400, 544);
		break;
	default:
		break;
	}

	if (_isSnowMap)
	{
		renderSnow(hdc);
	}
	else
	{
		renderParticle(hdc);
	}
}

void MapManager::backgoundRender(HDC hdc)
{
	_rcBackground = CAMERAMANAGER->calRelRc(RectMake(0, 0, _mapWidth, _mapHeight));
	_background->loopRender(hdc, &_rcBackground, CAMERAMANAGER->getAbsX() * 0.3f, CAMERAMANAGER->getAbsY() * 0.3f);
	_rcLayer = CAMERAMANAGER->calRelRc(RectMake(0, 0, _mapWidth, _mapHeight));
	_layer->loopRender(hdc, &_rcLayer, CAMERAMANAGER->getAbsX() * 0.1f, CAMERAMANAGER->getAbsY() * 0.3f);
}

void MapManager::initMap()
{
	for (int i = 0; i < (int)Code::MAP::MAP_CNT; i++)
	{
		_arrMapCode[i] = (Code::MAP)i;
		_arrClearMap[i] = FALSE;
	}

	_curLocation = 4;
	TILEMANAGER->loadMap(_arrMapCode[_curLocation]);
}

void MapManager::settingDungeon()
{
	_mapInfo = DBMANAGER->getInfo(_arrMapCode[_curLocation]);
	_mapWidth = TILEMANAGER->getCurrentMapTileWidth() + TILE_SIZE;
	_mapHeight = TILEMANAGER->getCurrentMapTileHeight() + TILE_SIZE;

	if (!_isSnowMap && _arrMapCode[_curLocation] == Code::MAP::DUNGEON_11)
	{
		_isSnowMap = TRUE;
		_layer = IMAGEMANAGER->findImage(ImageName::Dungeon::bgLayer1);
		SOUNDMANAGER->stop(SoundName::dungeon);
		SOUNDMANAGER->play(SoundName::IceDungeon, _sound);
	}

	if (_isSnowMap &&  _arrMapCode[_curLocation] == Code::MAP::DUNGEON_08)
	{
		_isSnowMap = FALSE;
		_layer = IMAGEMANAGER->findImage(ImageName::Dungeon::subBg);
		SOUNDMANAGER->stop(SoundName::IceDungeon);
		SOUNDMANAGER->play(SoundName::dungeon, _sound);
	}

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

	if (!_arrClearMap[_curLocation])
	{
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
		_curLocation--;
		break;
	case Direction::TOP:
		_curLocation -= MAP_Y;
		break;
	case Direction::RIGHT:
		_curLocation++;
		break;
	case Direction::BOTTOM:
		_curLocation += MAP_Y;
		break;
	default:
		break;
	}

	TILEMANAGER->loadMap(_arrMapCode[_curLocation]);
	settingDungeon();

	int idx = dir;

	if (idx < 2) idx += 2;
	else idx -= 2;

	int dirX = 1;
	int dirY = 1;
	if (dir == 0) dirX = -1;
	if (dir == 1) dirY = -1;
	
	OBJECTMANAGER->getPlayer()->setX(_door[idx]->getX() + TILE_SIZE * 2 * dirX);
	OBJECTMANAGER->getPlayer()->setY(_door[idx]->getY() + TILE_SIZE * 2 * dirY);

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
		_arrClearMap[_curLocation] = TRUE;
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
		_particle[i].dir = (DIR)RND->getInt(DIR::DIR_CNT);
		_particle[i].startX = RND->getFromIntTo(0, _mapWidth);
		_particle[i].startY = RND->getFromIntTo(0, _mapHeight);
		_particle[i].startX = _particle[i].startX - _imgParticle[_particle[i].imgIdx]->getWidth() * 0.5f;
		_particle[i].startY = _particle[i].startY - _imgParticle[_particle[i].imgIdx]->getHeight() * 0.5f;
		_particle[i].x = _particle[i].startX;
		_particle[i].y = _particle[i].startY;
		_particle[i].speedX = RND->getFromFloatTo(0.3f, 0.7f) - 0.5f;
		_particle[i].speedY = RND->getFromFloatTo(0.3f, 0.7f) - 0.5f;
		_particle[i].alpha = RND->getFromIntTo(100, 200);
		break;
	}
}

void MapManager::updateParticle()
{
	for (int i = 0; i < PARTICLE_CNT; i++)
	{
		if (!_particle[i].isOn) continue;

		_particle[i].alpha--;
		_particle[i].x += _particle[i].speedX;
		_particle[i].y += _particle[i].speedY;

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

void MapManager::updateSnow()
{
	_snowX += 2.0f;
	_snowY -= 5.0f;
	_rcSnow = CAMERAMANAGER->calRelRc(
		RectMake(
			0, 0,
			_mapWidth,
			_mapHeight
		)
	);
}

void MapManager::renderSnow(HDC hdc)
{
	_imgSnow->loopAlphaRender(hdc, &_rcSnow, _snowX, _snowY, 170);
}

Code::MAP MapManager::getCurMapCode()
{
	if (TILEMANAGER->getCurrentMapName() == FileName::Town ||
		TILEMANAGER->getCurrentMapName() == FileName::testSave)
	{
		return Code::MAP::TOWN;
	}

	return _arrMapCode[_curLocation]; 
}

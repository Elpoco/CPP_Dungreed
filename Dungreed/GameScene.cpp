#include "Stdafx.h"
#include "GameScene.h"

#include "Object.h"

using namespace LocationEnum;

GameScene::GameScene()
	: _location(LOCATION::TOWN)
	, _isEnter(FALSE)
{
}

GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::TARGET);
	OBJECTMANAGER->addUnit(Code::UNIT::PLAYER, TileSet::TOTAL_TILE_X * 0.5f, TileSet::TOTAL_TILE_Y * 0.5f);

	// Town
	TILEMANAGER->loadMap(FileName::Town);
	_layer = IMAGEMANAGER->findImage(ImageName::Town::townLayerDay);
	_background = IMAGEMANAGER->findImage(ImageName::Town::townBgDay);
	SOUNDMANAGER->play(SoundName::town, _sound);
	// 던전 입구
	_rcEntrance = RectMakeCenter(2940, 1296, 750, 1);
	_imgEnter = FindImage(ImageName::Town::dungeonEat);
	_enterFrame.maxFrameX = _imgEnter->getMaxFrameX();
	_enterFrame.width = _imgEnter->getFrameWidth();
	_enterFrame.height = _imgEnter->getFrameHeight();

	return S_OK;
}

void GameScene::release()
{
}

void GameScene::update()
{
	switch (_location)
	{
	case LocationEnum::LOCATION::TOWN:
		updateTown();
		break;
	case LocationEnum::LOCATION::DUNGEON:

		break;
	default:
		break;
	}
}

void GameScene::render()
{
	switch (_location)
	{
	case LocationEnum::LOCATION::TOWN:
		renderTown(getMemDC());
		break;
	default:
		break;
	}
	TILEMANAGER->render(getMemDC());

	if (_isEnter) CAMERAMANAGER->frameRender(getMemDC(), _imgEnter, _rcEnter.left, _rcEnter.top, _enterFrame.x, 0);
}

void GameScene::updateTown()
{
	RECT temp;
	RECT rcPlayer = OBJECTMANAGER->getPlayer()->getRect();

	if (!_isEnter && IntersectRect(&temp, &rcPlayer, &_rcEntrance))
	{
		OBJECTMANAGER->getPlayer()->stopObject();
		SOUNDMANAGER->play(SoundName::dungeonEat2, _sound);
		_rcEnter = RectMakeCenter(
			OBJECTMANAGER->getPlayer()->getX(),
			rcPlayer.bottom - _enterFrame.height * 0.5f,
			_enterFrame.width,
			_enterFrame.height
		);
		_isEnter = TRUE;
	}

	if (_isEnter)
	{
		if (++_enterFrame.cnt > _enterFrame.tick)
		{
			_enterFrame.cnt = 0;
			_enterFrame.x++;
			if (_enterFrame.x == 9)
			{
				SOUNDMANAGER->play(SoundName::dungeonEat, _sound);
				OBJECTMANAGER->getPlayer()->setRender(FALSE);
			}
			if (_enterFrame.x > _enterFrame.maxFrameX)
			{
				SOUNDMANAGER->stop(SoundName::dungeonEat2);
				SOUNDMANAGER->stop(SoundName::town);
				_enterFrame.x = 0;
				_isEnter = FALSE;
				_location = LOCATION::DUNGEON;
				SCENEMANAGER->setChangeScene(TRUE);
				loadDungeon();
			}
		}
	}
}

void GameScene::renderTown(HDC hdc)
{
	IMAGEMANAGER->render(ImageName::Town::cloud, hdc);
	RECT rc = { 0,WINSIZE_Y - _background->getHeight() - (100 - (TileSet::TOTAL_TILE_Y - (CAMERAMANAGER->getAbsY() + WINSIZE_Y))*0.7), WINSIZE_X, WINSIZE_Y };
	_background->loopRender(hdc, &rc, CAMERAMANAGER->getAbsX() / 3, 0);
	rc = RectMake(0, WINSIZE_Y - _layer->getHeight() - (100 - (TileSet::TOTAL_TILE_Y - (CAMERAMANAGER->getAbsY() + WINSIZE_Y))*1.2), WINSIZE_X, _layer->getHeight());
	_layer->loopRender(hdc, &rc, CAMERAMANAGER->getAbsX()*0.8, 0);
}

void GameScene::loadDungeon()
{
	// 맵 로드
	TILEMANAGER->loadMap(FileName::DungeonStart);
	_curDungeon = TILEMANAGER->getCurrentMapCode();
	_mapInfo = DBMANAGER->getInfo(_curDungeon);
	// 플레이어 셋팅
	OBJECTMANAGER->getPlayer()->setX(300);
	OBJECTMANAGER->getPlayer()->setY(470);
	OBJECTMANAGER->getPlayer()->setRender(TRUE);
	CAMERAMANAGER->cameraInitPos();
	// 음악 재생
	SOUNDMANAGER->play(SoundName::dungeon, _sound);
	// 던전 셋팅
	settingDungeon();

	// 로딩완료
	SCENEMANAGER->setChangeScene(FALSE);
	// 플레이어 다시 움직이게
	OBJECTMANAGER->getPlayer()->resumeObject();
}

void GameScene::settingDungeon()
{
	OBJECTMANAGER->addUnit(
		_mapInfo.arrSpawnInfo[0].unit,
		_mapInfo.arrSpawnInfo[0].ptSpawn.x,
		_mapInfo.arrSpawnInfo[0].ptSpawn.y
	);

	for (int i = 0; i < DIR::DIR_CNT; i++)
	{
		if (_mapInfo.door[i].isOn)
		{
			OBJECTMANAGER->addDoor((DIR)i, _mapInfo.door[i].tileX, _mapInfo.door[i].tileY);
		}
	}
}

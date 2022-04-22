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
	OBJECTMANAGER->addUnit(Code::UNIT::PLAYER, MapToolSet::TOTAL_TILE_X * 0.5f, MapToolSet::TOTAL_TILE_Y * 0.5f);

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
		updateDungeon();
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
	RECT rc = { 0,WINSIZE_Y - _background->getHeight() - (100 - (MapToolSet::TOTAL_TILE_Y - (CAMERAMANAGER->getAbsY() + WINSIZE_Y))*0.7), WINSIZE_X, WINSIZE_Y };
	_background->loopRender(hdc, &rc, CAMERAMANAGER->getAbsX() / 3, 0);
	rc = RectMake(0, WINSIZE_Y - _layer->getHeight() - (100 - (MapToolSet::TOTAL_TILE_Y - (CAMERAMANAGER->getAbsY() + WINSIZE_Y))*1.2), WINSIZE_X, _layer->getHeight());
	_layer->loopRender(hdc, &rc, CAMERAMANAGER->getAbsX()*0.8, 0);
}

void GameScene::loadDungeon()
{
	// 맵 로드
	TILEMANAGER->loadMap(FileName::Dungeon);
	// 플레이어 셋팅
	OBJECTMANAGER->getPlayer()->setX(CENTER_X);
	OBJECTMANAGER->getPlayer()->setRender(TRUE);
	// 음악 재생
	SOUNDMANAGER->play(SoundName::dungeon, _sound);

	OBJECTMANAGER->addUnit(Code::UNIT::SKEL_DOG, 135, 1270);

	_spawnInfo[0].rcScan = RectMakeCenter(1100, 1266, 300, 300);
	_spawnInfo[0].ptSpawn = PointMake(1380, 900);
	_spawnInfo[0].unit = Code::UNIT::LITTLE_GHOST;

	_spawnInfo[1].rcScan = RectMakeCenter(1100, 1266, 300, 300);
	_spawnInfo[1].ptSpawn = PointMake(1200, 900);
	_spawnInfo[1].unit = Code::UNIT::LITTLE_GHOST;

	_spawnInfo[2].rcScan = RectMakeCenter(1100, 1266, 300, 300);
	_spawnInfo[2].ptSpawn = PointMake(900, 1150);
	_spawnInfo[2].unit = Code::UNIT::LITTLE_GHOST;

	_spawnInfo[3].rcScan = RectMakeCenter(2100, 1266, 300, 300);
	_spawnInfo[3].ptSpawn = PointMake(2425, 1270);
	_spawnInfo[3].unit = Code::UNIT::SKEL_DOG;

	_spawnInfo[4].rcScan = RectMakeCenter(2100, 1266, 300, 300);
	_spawnInfo[4].ptSpawn = PointMake(2625, 1270);
	_spawnInfo[4].unit = Code::UNIT::SKEL_DOG;

	_spawnInfo[5].rcScan = RectMakeCenter(2100, 1266, 300, 300);
	_spawnInfo[5].ptSpawn = PointMake(2825, 1270);
	_spawnInfo[5].unit = Code::UNIT::SKEL_DOG;

	_spawnInfo[6].rcScan = RectMakeCenter(3850, 1266, 300, 300);
	_spawnInfo[6].ptSpawn = PointMake(4200, 1000);
	_spawnInfo[6].unit = Code::UNIT::BELIAL;

	_spawnInfo[7].rcScan = RectMakeCenter(4800, 1266, 300, 300);
	_spawnInfo[7].ptSpawn = PointMake(5100, 1000);
	_spawnInfo[7].unit = Code::UNIT::NIFLEHEIM;


	//3350 930 콜트
	ITEMMANAGER->dropItem(Code::ITEM::COLT, 3350, 930);

	_spawnCnt = 0;

	// 로딩완료
	SCENEMANAGER->setChangeScene(FALSE);
	// 플레이어 다시 움직이게
	OBJECTMANAGER->getPlayer()->resumeObject();
}

void GameScene::updateDungeon()
{
	RECT rcPlayer = OBJECTMANAGER->getPlayer()->getRect();
	for (int i = 0; i < 30; i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &rcPlayer, &_spawnInfo[i].rcScan))
		{
			if (++_spawnCnt < 50) return;
			_spawnCnt = 0;
			_spawnInfo[i].rcScan = { 0,0,0,0 };
			OBJECTMANAGER->addUnit(_spawnInfo[i].unit, _spawnInfo[i].ptSpawn.x, _spawnInfo[i].ptSpawn.y);
			return;
		}
	}
}

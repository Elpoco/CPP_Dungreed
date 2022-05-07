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

	// Town
	TILEMANAGER->loadMap(FileName::Town);
	_imgSky = IMAGEMANAGER->findImage(ImageName::Town::cloud);
	_imgLayer = IMAGEMANAGER->findImage(ImageName::Town::townLayerDay);
	_imgBackground = IMAGEMANAGER->findImage(ImageName::Town::townBgDay);
	_skyX = 0.0f;
	SOUNDMANAGER->play(SoundName::town, _sound);
	UIMANAGER->showMapInfo("Town");

	_vTownDeco.push_back({ FindImage(ImageName::Town::BrokenTemple), 2590, 557 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::Tree0), 3944, 1112 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::Tree1), 1790, 1066 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::DogHouse), 1768, 1217 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::DungeonSignL), 2459, 1229 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::DungeonSignR), 3350, 1232 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::Grass0), 1619, 1265 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::Grass1), 871, 700 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::Grass2), 5474, 1219 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::Shop), 5050, 364 });
	//_vTownDeco.push_back({ FindImage(ImageName::Town::BrokenHouse0), 5089, 601 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::BrokenHouse1), 193, 608 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::TrainingSchool), 11, 1064 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::BlackSmith), 5204, 905 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::StreetLight_0), 1302, 1124 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::StreetLight_0), 4109, 1124 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::StreetLight_1), 777, 578 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::StreetLight_1), 4920, 578 });
	_vTownDeco.push_back({ FindImage(ImageName::Town::StreetLight_2),  5054, 1154 });

	// 던전 입구
	_rcEntrance = RectMakeCenter(2940, 1296, 750, 10);
	_imgEnter = FindImage(ImageName::Town::dungeonEat);
	_enterFrame.maxFrameX = _imgEnter->getMaxFrameX();
	_enterFrame.width = _imgEnter->getFrameWidth();
	_enterFrame.height = _imgEnter->getFrameHeight();

	UIMANAGER->initMiniMap();
	OBJECTMANAGER->addPlayer(TileSet::TOTAL_TILE_X * 0.5f, TileSet::TOTAL_TILE_Y * 0.5f);
	OBJECTMANAGER->addNPC(Code::NPC::SHOP, 5241, 719);
	OBJECTMANAGER->addNPC(Code::NPC::BLACKSMITH, 5345, 1293);
	OBJECTMANAGER->addNPC(Code::NPC::COMMANDER, 418, 1294);

	//OBJECTMANAGER->addNPC(Code::NPC::INN, 2943, 814);

	OBJECTMANAGER->addTresure(5360, 696, Code::TRESURE_TYPE::GOLD);
	OBJECTMANAGER->addTresure(5440, 696, Code::TRESURE_TYPE::GOLD);
	OBJECTMANAGER->addTresure(5520, 696, Code::TRESURE_TYPE::GOLD);
	OBJECTMANAGER->addTresure(5600, 696, Code::TRESURE_TYPE::GOLD);

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
		MAPMANAGER->update();
		break;
	default:
		break;
	}
}

void GameScene::render()
{
	if (_location == LocationEnum::LOCATION::TOWN)
	{
		renderBackTown(getMemDC());
	}
	else
	{
		MAPMANAGER->backgoundRender(getMemDC());
	}

	TILEMANAGER->render(getMemDC());
	
	if (_location == LocationEnum::LOCATION::TOWN)
	{
		renderTown(getMemDC());
	}
	else
	{
		MAPMANAGER->render(getMemDC());
	}

	if (_isEnter) CAMERAMANAGER->frameRender(getMemDC(), _imgEnter, _rcEnter.left, _rcEnter.top, _enterFrame.x, 0);

}

void GameScene::updateTown()
{
	_skyX += 0.1f;

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
	for (auto deco : _vTownDeco)
	{
		CAMERAMANAGER->render(hdc, deco.img, deco.x, deco.y);
	}
}

void GameScene::renderBackTown(HDC hdc)
{
	RECT rc = { 0,0, WINSIZE_X, WINSIZE_Y };
	_imgSky->loopRender(hdc, &rc, _skyX, 0);
	_rcBackground = RectMake(0, WINSIZE_Y - _imgBackground->getHeight() - (100 - (TileSet::TOTAL_TILE_Y - (CAMERAMANAGER->getAbsY() + WINSIZE_Y))*0.7), WINSIZE_X, WINSIZE_Y);
	_imgBackground->loopRender(hdc, &_rcBackground, CAMERAMANAGER->getAbsX() * 0.3f, 0);
	_rcLayer = RectMake(0, WINSIZE_Y - _imgLayer->getHeight() - (100 - (TileSet::TOTAL_TILE_Y - (CAMERAMANAGER->getAbsY() + WINSIZE_Y))*1.2), WINSIZE_X, _imgLayer->getHeight());
	_imgLayer->loopRender(hdc, &_rcLayer, CAMERAMANAGER->getAbsX() * 0.8, 0);
}

void GameScene::loadDungeon()
{
	// 맵 로드
	MAPMANAGER->init();
	UIMANAGER->updateMiniMap();
	UIMANAGER->enterDungeon();
	UIMANAGER->initWorldMap();

	// 플레이어 셋팅
	OBJECTMANAGER->getPlayer()->setX(300);
	OBJECTMANAGER->getPlayer()->setY(593);
	OBJECTMANAGER->getPlayer()->setRender(TRUE);
	CAMERAMANAGER->cameraInitPos();
	// 음악 재생
	SOUNDMANAGER->play(SoundName::dungeon, _sound);
	// 던전 셋팅
	MAPMANAGER->settingDungeon();

	// 로딩완료
	SCENEMANAGER->setChangeScene(FALSE);
	// 플레이어 다시 움직이게
	OBJECTMANAGER->getPlayer()->resumeObject();
}

#include "Stdafx.h"
#include "TileManager.h"

using namespace TileSet;
using namespace MapToolEnum;

TileManager::TileManager()
	: _renderWidth(WINSIZE_X + TILE_SIZE)
	, _renderHeight(WINSIZE_Y + TILE_SIZE)
	, _isShowObj(FALSE)
{
}

TileManager::~TileManager()
{
}

HRESULT TileManager::init()
{
	_imgObject = FindImage(ImageName::MapTool::mapObject);

	initTile();

	_imgTile = IMAGEMANAGER->findImage(ImageName::MapTool::mapTile);

	return S_OK;
}

void TileManager::release()
{
}

void TileManager::update()
{
	if (IsOnceKeyDown(KEY::F2)) _isShowObj = !_isShowObj;
}

void TileManager::render(HDC hdc)
{
	int cX = CAMERAMANAGER->getAbsX() / TILE_SIZE;
	int cY = CAMERAMANAGER->getAbsY() / TILE_SIZE;

	for (int y = cY; y <= cY + (_renderHeight / TILE_SIZE); y++)
	{
		if (y >= TILE_CNT_Y || y < 0) continue;

		for (int x = cX; x <= cX + (_renderWidth / TILE_SIZE); x++)
		{
			if (x >= TILE_CNT_X || x < 0) continue;

			this->tileRender(hdc, _tiles[y * TILE_CNT_X + x]);
		}
	}
}

void TileManager::initTile()
{
	SAFE_DELETE_ARRAY(_tiles);

	_tiles = new TILE[TOTAL_TILE_CNT];

	for (float y = 0; y < TILE_CNT_Y; y++)
	{
		for (float x = 0; x < TILE_CNT_X; x++)
		{
			int idx = y * TILE_CNT_X + x;
			_tiles[idx].x = x * TILE_SIZE + TILE_SIZE * 0.5f;
			_tiles[idx].y = y * TILE_SIZE + TILE_SIZE * 0.5f;
			_tiles[idx].idx = PointMake(x, y);
			_tiles[idx].rc = RectMake(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
	}
}

void TileManager::tileRender(HDC hdc, TILE tile)
{
	if(SCENEMANAGER->getCurrentSceneName() == SceneName::mapToolScene)
		CAMERAMANAGER->printRectangle(hdc, tile.rc.left, tile.rc.top, TILE_SIZE, TILE_SIZE);
	CAMERAMANAGER->frameRender(hdc, _imgTile, tile.rc.left, tile.rc.top, tile.tileFrameX, tile.tileFrameY);
	if(_isShowObj) CAMERAMANAGER->frameRender(hdc, _imgObject, tile.rc.left, tile.rc.top, tile.type, 0);

	if (SCENEMANAGER->getCurrentSceneName() == SceneName::mapToolScene && _isDebug)
		CAMERAMANAGER->printPoint(hdc, tile.rc.left, tile.rc.top, tile.idx.y, tile.idx.x);
}

void TileManager::setRenderSize(int width, int height)
{
	_renderWidth = width;
	_renderHeight = height;
}

void TileManager::setTile(int idx, int frameX, int frameY, int type)
{
	if (idx > TILE_CNT_X * TILE_CNT_Y - 1 || idx < 0) return;

	_tiles[idx].tileFrameX = frameX;
	_tiles[idx].tileFrameY = frameY;
	_tiles[idx].type = type;
}

TILE TileManager::getTile(float x, float y)
{
	return this->getTile(PointMake(x, y));
}

TILE TileManager::getTile(POINT pt)
{
	int idx = getTileIndex(pt);

	return _tiles[idx];
}

POINT TileManager::getTilePt(POINT pt)
{
	int idx = getTileIndex(pt);

	return _tiles[idx].idx;
}

int TileManager::getTileIndex(float x, float y)
{
	return this->getTileIndex(PointMake(x, y));
}

int TileManager::getTileIndex(POINT pt)
{
	int x = (pt.x) / TILE_SIZE;
	int y = (pt.y) / TILE_SIZE;

	int idx = TILE_CNT_X * y + x;
	int maxTile = TILE_CNT_X * TILE_CNT_Y;

	if (idx >= maxTile || idx < 0) idx = -1;

	return idx;
}

int TileManager::saveMap(string str)
{
	return FILEMANAGER->saveFile(PATH_DATA, str + ".dat", _tiles, TOTAL_TILE_CNT * sizeof(TILE));
}

int TileManager::loadMap(string str)
{
	initTile();
	int res = FILEMANAGER->loadFile(PATH_DATA, str + ".dat", _tiles, TOTAL_TILE_CNT * sizeof(TILE));
	CAMERAMANAGER->updateMapSize();
	_curMapName = str;

	return res;
}

int TileManager::loadMap(Code::MAP code)
{
	string str = FileName::testSave;
	switch (code)
	{
	case Code::MAP::DUNGEON_START:
		str = FileName::DungeonStart;
		break;
	case Code::MAP::DUNGEON_SHOP:
		str = FileName::DungeonShop;
		break;
	case Code::MAP::DUNGEON_FOOD:
		str = FileName::DungeonFood;
		break;
	case Code::MAP::DUNGEON_01:
		str = FileName::Dungeon01;
		break;
	case Code::MAP::DUNGEON_02:
		str = FileName::Dungeon02;
		break;
	case Code::MAP::DUNGEON_03:
		str = FileName::Dungeon03;
		break;
	case Code::MAP::DUNGEON_04:
		str = FileName::Dungeon04;
		break;
	case Code::MAP::DUNGEON_05:
		str = FileName::Dungeon05;
		break;
	case Code::MAP::DUNGEON_06:
		str = FileName::Dungeon06;
		break;
	case Code::MAP::DUNGEON_07:
		str = FileName::Dungeon07;
		break;
	case Code::MAP::DUNGEON_08:
		str = FileName::Dungeon08;
		break;
	case Code::MAP::DUNGEON_09:
		str = FileName::Dungeon09;
		break;
	case Code::MAP::DUNGEON_10:
		str = FileName::Dungeon10;
		break;
	case Code::MAP::DUNGEON_11:
		str = FileName::Dungeon11;
		break;
	case Code::MAP::BELIAL:
		str = FileName::Belial;
		break;
	case Code::MAP::NIFLHEIM:
		str = FileName::Niflheim;
		break;
	default:
		break;
	}

	initTile();
	int res = FILEMANAGER->loadFile(PATH_DATA, str + ".dat", _tiles, TOTAL_TILE_CNT * sizeof(TILE));
	CAMERAMANAGER->updateMapSize();
	_curMapName = str;

	return res;
}

int TileManager::getCurrentMapTileCntX()
{
	int tileCnt = 0;
	for (int y = 0; y < TILE_CNT_Y; y++)
	{
		int tempCnt = 0;
		for (int x = 0; x < TILE_CNT_X; x++)
		{
			if (_tiles[TILE_CNT_X * y + x].tileFrameX != -1)
			{
				tempCnt = x;
			}
		}
		if (tempCnt > tileCnt) tileCnt = tempCnt;
		if (tileCnt == TILE_CNT_X - 1) break;
	}

	return tileCnt;
}

int TileManager::getCurrentMapTileCntY()
{
	int tileCnt = 0;
	for (int x = 0; x < TILE_CNT_X; x++)
	{
		int tempCnt = 0;
		for (int y = 0; y < TILE_CNT_Y; y++)
		{
			if (_tiles[TILE_CNT_X * y + x].tileFrameX != -1)
			{
				tempCnt = y;
			}
		}
		if (tempCnt > tileCnt) tileCnt = tempCnt;
		if (tileCnt == TILE_CNT_Y - 1) break;
	}

	return tileCnt;
}

float TileManager::getCurrentMapTileWidth()
{
	return getCurrentMapTileCntX() * TILE_SIZE;
}

float TileManager::getCurrentMapTileHeight()
{
	return getCurrentMapTileCntY() * TILE_SIZE;
}

void TileManager::getDoorPos(POINT* ptDoor)
{
	int curTileX = getCurrentMapTileCntX();
	int curTileY = getCurrentMapTileCntY();

	for (int y = 0; y < curTileY; y++)
	{
		if (_tiles[TILE_CNT_X * y].type == MapToolEnum::MAP_OBJ::NONE)
		{
			ptDoor[DIR::LEFT] = { 0, y };
			break;
		}
	}

	for (int x = 0; x < curTileX; x++)
	{
		if (_tiles[x].type == MapToolEnum::MAP_OBJ::NONE)
		{
			ptDoor[DIR::TOP] = { x, 0 };
			break;
		}
	}

	for (int y = 0; y < curTileY; y++)
	{
		if (_tiles[TILE_CNT_X * y + curTileX].type == MapToolEnum::MAP_OBJ::NONE)
		{
			ptDoor[DIR::RIGHT] = { curTileX, y };
			break;
		}
	}

	for (int x = 0; x < curTileX; x++)
	{
		if (_tiles[TILE_CNT_X * curTileY + x].type == MapToolEnum::MAP_OBJ::NONE)
		{
			ptDoor[DIR::BOTTOM] = { x, curTileY };
			break;
		}
	}
}

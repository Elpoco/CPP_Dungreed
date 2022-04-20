#include "Stdafx.h"
#include "TileManager.h"

using namespace MapToolSet;
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

	_tileCntX = TILE_CNT_X;
	_tileCntY = TILE_CNT_Y;
	_tileTotalCnt = _tileCntX * _tileCntY;

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
		if (y >= _tileCntY || y < 0) continue;

		for (int x = cX; x <= cX + (_renderWidth / TILE_SIZE); x++)
		{
			if (x >= _tileCntX || x < 0) continue;

			this->tileRender(hdc, _tiles[y * _tileCntX + x]);
		}
	}
}

void TileManager::initTile()
{
	SAFE_DELETE_ARRAY(_tiles);

	_tiles = new TILE[_tileTotalCnt];

	for (float y = 0; y < _tileCntY; y++)
	{
		for (float x = 0; x < _tileCntX; x++)
		{
			int idx = y * _tileCntX + x;
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
	if (idx > _tileCntX * _tileCntY - 1 || idx < 0) return;

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
	int maxTile = _tileCntX * _tileCntY;

	if (idx >= maxTile || idx < 0) idx = -1;

	return idx;
}

int TileManager::saveMap(string str)
{
	return FILEMANAGER->saveFile(PATH_DATA, str + ".dat", _tiles, _tileTotalCnt * sizeof(TILE));
}

int TileManager::loadMap(string str)
{
	initTile();
	return FILEMANAGER->loadFile(PATH_DATA, str + ".dat", _tiles, _tileTotalCnt * sizeof(TILE));
}

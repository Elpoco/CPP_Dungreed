#include "Stdafx.h"
#include "TileManager.h"

using namespace MapToolSet;
using namespace MapToolEnum;

TileManager::TileManager() :
	_renderWidth(WINSIZE_X + TILE_SIZE),
	_renderHeight(WINSIZE_Y + TILE_SIZE)
{
}

TileManager::~TileManager()
{
}

HRESULT TileManager::init()
{
	_tileCntX = TILE_CNT_X;
	_tileCntY = TILE_CNT_Y;
	_tileTotalCnt = _tileCntX * _tileCntY;

	_tiles = new TILE[_tileTotalCnt];

	for (float y = 0; y < _tileCntY; y++)
	{
		for (float x = 0; x < _tileCntX; x++)
		{
			int idx = y * _tileCntX + x;
			_tiles[idx].x = x * TILE_SIZE + TILE_SIZE/2;
			_tiles[idx].y = y * TILE_SIZE + TILE_SIZE/2;
			_tiles[idx].pos = PointMake(x, y);
			_tiles[idx].rc = RectMake(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
	}

	_imgTile = IMAGEMANAGER->findImage(ImageName::mapTile);

	return S_OK;
}

void TileManager::release()
{
}

void TileManager::update()
{
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

void TileManager::tileRender(HDC hdc, TILE tile)
{
	//if (tile.terrain == TERRAIN::TR_NONE &&
	//	tile.object == MAP_OBJECT::MO_NONE)
	if (tile.type == TYPE::NONE)
	{
		if (SCENEMANAGER->getCurrentSceneName() == SceneName::mapToolScene)
			CAMERAMANAGER->printRectangle(hdc, tile.rc.left, tile.rc.top, TILE_SIZE, TILE_SIZE);
	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _imgTile, tile.rc.left, tile.rc.top, tile.tileFrameX, tile.tileFrameY);
	}

	if (SCENEMANAGER->getCurrentSceneName() == SceneName::mapToolScene && _isDebug)
		CAMERAMANAGER->printPoint(hdc, tile.rc.left, tile.rc.top, tile.pos.y, tile.pos.x);
}

void TileManager::setRenderSize(int width, int height)
{
	_renderWidth = width;
	_renderHeight = height;
}

//void TileManager::setTileFrame(int idx, int frameX, int frameY, TERRAIN terrain, MAP_OBJECT object)
void TileManager::setTileFrame(int idx, int frameX, int frameY, TYPE type)
{
	if (idx > _tileCntX * _tileCntY - 1 || idx < 0) return;

	_tiles[idx].tileFrameX = frameX;
	_tiles[idx].tileFrameY = frameY;
	_tiles[idx].type = type;
	//_tiles[idx].terrain = terrain;
	//_tiles[idx].object = object;
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

	return _tiles[idx].pos;
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

//TILE_TYPE TileManager::getTileType(PointF pt)
//{
//	int idx = this->getTileIndex(pt);
//
//	return _tiles[idx].type;
//}

int TileManager::saveMap(string str)
{
	return FILEMANAGER->saveFile(PATH_DATA, str, _tiles, _tileTotalCnt * sizeof(TILE));
}

int TileManager::loadMap(string str)
{
	return FILEMANAGER->loadFile(PATH_DATA, str, _tiles, _tileTotalCnt * sizeof(TILE));
}

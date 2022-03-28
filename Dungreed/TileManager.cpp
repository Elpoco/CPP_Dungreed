#include "Stdafx.h"
#include "TileManager.h"

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

	_tiles = new Tile[_tileTotalCnt];

	for (int y = 0; y < _tileCntY; y++)
	{
		for (int x = 0; x < _tileCntX; x++)
		{
			int idx = y * _tileCntX + x;
			_tiles[idx].idx = { x,y };
			_tiles[idx].rc = RectMake(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
	}

	return S_OK;
}

HRESULT TileManager::init(int tileCntX, int tileCntY)
{
	

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
	int cX = CAMERAMANAGER->getAbsX();
	int cY = CAMERAMANAGER->getAbsY();
	for (int y = cY / TILE_SIZE; y <= (_renderHeight / TILE_SIZE) + (cY / TILE_SIZE); y++)
	{
		if (y >= _tileCntY || y < 0) continue;
		for (int x = cX / TILE_SIZE; x <= (_renderWidth / TILE_SIZE) + (cX / TILE_SIZE); x++)
		{
			if (x >= _tileCntX || x < 0) continue;
			this->tileRender(hdc, _tiles[y * _tileCntX + x]);
		}
	}
}

void TileManager::tileRender(HDC hdc, Tile tile)
{
	switch (tile.type)
	{
	case TILE_TYPE::NONE:
		if (_isDebug)
			RectangleMake(hdc, 
				CAMERAMANAGER->getRelX(tile.rc.left), 
				CAMERAMANAGER->getRelY(tile.rc.top), 
				TILE_SIZE, TILE_SIZE);
		break;
	case TILE_TYPE::BLOCK:
		IMAGEMANAGER->frameRender("MapTile", hdc, 
			CAMERAMANAGER->getRelX(tile.rc.left), 
			CAMERAMANAGER->getRelY(tile.rc.top), 
			tile.tileFrame.x, tile.tileFrame.y);
		break;
	default:
		break;
	}

	if (_isDebug)
	{
		printPt(hdc, CAMERAMANAGER->getRelX(tile.rc.left), CAMERAMANAGER->getRelY(tile.rc.top), tile.idx.y, tile.idx.x);
	}
}

void TileManager::setRenderSize(int width, int height)
{
	_renderWidth = width;
	_renderHeight = height;
}

void TileManager::setTileFrame(int idx, int frameX, int frameY, TILE_TYPE type)
{
	if (idx > _tileCntX * _tileCntY - 1 || idx < 0) return;

	_tiles[idx].tileFrame = { frameX, frameY };
	_tiles[idx].type = type;
}

int TileManager::getTileIndex(POINT pt)
{
	int x = (pt.x + CAMERAMANAGER->getAbsX()) / TILE_SIZE;
	int y = (pt.y + CAMERAMANAGER->getAbsY()) / TILE_SIZE;

	int idx = y * TILE_CNT_X + x;

	if (idx > _tileCntX * _tileCntY - 1 || idx < 0) idx = 0;

	return idx;
}

TILE_TYPE TileManager::getTileType(POINT pt)
{
	int idx = this->getTileIndex(pt);

	return _tiles[idx].type;
}

int TileManager::saveMap(string str)
{
	return FILEMANAGER->saveFile(PATH_DATA, str, _tiles, _tileTotalCnt * sizeof(Tile));
}

int TileManager::loadMap(string str)
{
	return FILEMANAGER->loadFile(PATH_DATA, str, _tiles, _tileTotalCnt * sizeof(Tile));
}

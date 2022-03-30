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
	_tileCntX = MapToolSet::TILE_CNT_X;
	_tileCntY = MapToolSet::TILE_CNT_Y;
	_tileTotalCnt = _tileCntX * _tileCntY;

	_tiles = new Tile[_tileTotalCnt];

	for (float y = 0; y < _tileCntY; y++)
	{
		for (float x = 0; x < _tileCntX; x++)
		{
			int idx = y * _tileCntX + x;
			_tiles[idx].pos = { x,y };
			_tiles[idx].rc = RectFMake(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
	}

	_imgTile = IMAGEMANAGER->findImage(ImageName::mapTile);

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
	case MapToolEnum::TILE_TYPE::NONE:
		if (SCENEMANAGER->getCurrentSceneName() == SceneName::mapToolScene)
			CAMERAMANAGER->printRectangle(hdc, tile.rc.GetLeft(), tile.rc.GetTop(), TILE_SIZE, TILE_SIZE);
		break;
	case MapToolEnum::TILE_TYPE::BLOCK:
		CAMERAMANAGER->frameRender(hdc, _imgTile, tile.rc.GetLeft(), tile.rc.GetTop(), tile.tileFrameX, tile.tileFrameY);
		break;
	default:
		break;
	}

	if (_isDebug)
	{
		CAMERAMANAGER->printPoint(hdc, tile.rc.GetLeft(), tile.rc.GetTop(), tile.pos.Y, tile.pos.X);
	}
}

void TileManager::setRenderSize(int width, int height)
{
	_renderWidth = width;
	_renderHeight = height;
}

void TileManager::setTileFrame(int idx, int frameX, int frameY, MapToolEnum::TILE_TYPE type)
{
	if (idx > _tileCntX * _tileCntY - 1 || idx < 0) return;

	_tiles[idx].tileFrameX = frameX;
	_tiles[idx].tileFrameY = frameY;
	_tiles[idx].type = type;
}

Tile TileManager::getTile(PointF pt)
{
	int idx = getTileIndex(pt);

	return _tiles[idx];
}

PointF TileManager::getTilePt(PointF pt)
{
	int idx = getTileIndex(pt);

	return _tiles[idx].pos;
}

int TileManager::getTileIndex(PointF pt)
{
	int x = (pt.X + CAMERAMANAGER->getAbsX()) / TILE_SIZE;
	int y = (pt.Y + CAMERAMANAGER->getAbsY()) / TILE_SIZE;

	int idx = MapToolSet::TILE_CNT_X * y + x;
	int maxTile = _tileCntX * _tileCntY;

	if (idx >= maxTile || idx < 0) idx = 0;

	return idx;
}

MapToolEnum::TILE_TYPE TileManager::getTileType(PointF pt)
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

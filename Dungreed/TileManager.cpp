#include "Stdafx.h"
#include "TileManager.h"

#include "Tile.h"

TileManager::TileManager() :
	_renderWidth(WINSIZE_X),
	_renderHeight(WINSIZE_Y)
{
}

TileManager::~TileManager()
{
}

HRESULT TileManager::init()
{
	_tileCntX = TILE_CNT_X;
	_tileCntY = TILE_CNT_Y;

	//_tiles = new Tile[_tileCntX*_tileCntY];

	for (int y = 0; y < _tileCntY; y++)
	{
		for (int x = 0; x < _tileCntX; x++)
		{
			_tiles[y*_tileCntX + x] = new Tile(x,y);  //.init(x, y);
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

void TileManager::render()
{
	int cX = CAMERAMANAGER->getAbsX();
	int cY = CAMERAMANAGER->getAbsY();
	for (int y = cY / TILE_SIZE; y <= _renderHeight / TILE_SIZE + cY / TILE_SIZE; y++)
	{
		if (y >= _tileCntY || y < 0) continue;
		for (int x = cX / TILE_SIZE; x <= _renderWidth / TILE_SIZE + cX / TILE_SIZE; x++)
		{
			if (x >= _tileCntX || x < 0) continue;
			_tiles[y * _tileCntX + x]->render();
		}
	}
}

void TileManager::setRenderSize(int width, int height)
{
	_renderWidth = width;
	_renderHeight = height;
}

void TileManager::setTileFrame(int idx, int frameX, int frameY, TILE_TYPE type)
{
	if (idx > _tileCntX * _tileCntY || idx < 0) return;
	_tiles[idx]->setFrame(frameX, frameY, type);
}

void TileManager::saveMap(string str)
{
	if (str == "") str = "testSave.map";
	cout << sizeof(Tile);
	FILEMANAGER->saveFile(PATH_DATA, str, &_tiles, _tileCntX * _tileCntY * sizeof(Tile));
}

void TileManager::loadMap(string str)
{
	if (str == "") str = "testSave.map";
	FILEMANAGER->loadFile(PATH_DATA, str, &_tiles, _tileCntX * _tileCntY * sizeof(Tile));
	for (Tile* tile : _tiles)
	{
		cout << tile->getRect().left << " ";
	}
}

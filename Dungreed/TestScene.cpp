#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"

HRESULT TestScene::init(void)
{
	_player = new Player;
	_player->init();

	for (int i = TILE_SIZE/2; i < WINSIZE_Y; i+= TILE_SIZE)
	{
		for (int j = TILE_SIZE/2; j < WINSIZE_X; j+= TILE_SIZE)
		{
			tagTile tile;
			tile.x = j;
			tile.y = i;
			if (i > CENTER_Y + 300) tile.type = BLOCK;
			else tile.type = NONE;
			tile.rc = RectMakeCenter(tile.x, tile.y, TILE_SIZE, TILE_SIZE);

			_vTiles.push_back(tile);
		}
	}

	return S_OK;
}

void TestScene::release(void)
{
}

void TestScene::update(void)
{
	_player->update();
	_proveBottom = _player->getRect().bottom;
	int idxY = _proveBottom / TILE_SIZE;
	int idxX = _player->getX() / TILE_SIZE;
	int row = WINSIZE_X / TILE_SIZE;
	if (_vTiles[idxY * row + idxX].type == BLOCK)
	{
		//_player->setY(_vTiles[idxY * row + idxX].rc.top);
	}
}

void TestScene::render(void)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	IMAGEMANAGER->render("PixelTest", getMemDC());
	for (_viTile = _vTiles.begin(); _viTile != _vTiles.end(); ++_viTile)
	{
		if ((*_viTile).type == NONE)
			RectangleMakeRect(getMemDC(), (*_viTile).rc);
		else
			FillRect(getMemDC(), &(*_viTile).rc, hBrush);
	}
	DeleteObject(hBrush);
	_player->render(getMemDC());
}

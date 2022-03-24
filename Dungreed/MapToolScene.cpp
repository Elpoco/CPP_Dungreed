#include "Stdafx.h"
#include "MapToolScene.h"

#include "Tile.h"

HRESULT MapToolScene::init(void)
{
	x = 0;
	y = 0;

	for (int i = 0; i < TILE_CNT; i++)
	{
		for (int j = 0; j < TILE_CNT; j++)
		{
			Tile* tile = new Tile;
			tile->init(j*TILE_SIZE, i*TILE_SIZE);
			_vTiles.push_back(tile);
		}
	}

	return S_OK;
}

void MapToolScene::release(void)
{
}

void MapToolScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown('A')&& CAMERAMANAGER->getAbsX()>0) { x -= 5; CAMERAMANAGER->updateX(-5); }
	if (KEYMANAGER->isStayKeyDown('W')&&CAMERAMANAGER->getAbsY()>0) { y -= 5; CAMERAMANAGER->updateY(-5); }
	if (KEYMANAGER->isStayKeyDown('D')) { x += 5; CAMERAMANAGER->updateX(5); }
	if (KEYMANAGER->isStayKeyDown('S')) { y += 5; CAMERAMANAGER->updateY(5); }

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mX = _ptMouse.x;
		mY = _ptMouse.y;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		x += mX - _ptMouse.x;
		y += mY - _ptMouse.y;
	}

	for (_viTiles = _vTiles.begin(); _viTiles != _vTiles.end(); ++_viTiles)
	{
		(*_viTiles)->update();
	}
}

void MapToolScene::render(void)
{
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			IMAGEMANAGER->render("MapTile", getMemDC(), (TILE_SIZE +1)*j - x, (TILE_SIZE + 1)*i - y, TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE, TILE_SIZE);
			//IMAGEMANAGER->findImage("MapTile")->stretchRender(getMemDC(), 0, 0, 2.0f, 2.0f);
		}
	}
	
	
	for (int i = (CAMERAMANAGER->getAbsY()) / TILE_SIZE; i < (CAMERAMANAGER->getAbsY() + WINSIZE_Y) / TILE_SIZE; i++)
	{
		for (int j = (CAMERAMANAGER->getAbsX()) / TILE_SIZE; j < (CAMERAMANAGER->getAbsX() + WINSIZE_X) / TILE_SIZE; j++)
		{
			_vTiles[i*TILE_CNT + j]->render(getMemDC());
		}
	}
}

#include "Stdafx.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

HRESULT MiniMap::init()
{
	_isFixed = TRUE;
	settingMiniMap();

	return S_OK;
}

void MiniMap::release()
{
}

void MiniMap::update()
{
}

void MiniMap::render(HDC hdc)
{
	PrintRectangle(hdc, _x, _y, 100, 100);
}

void MiniMap::settingMiniMap()
{
	_tileCntX = TILEMANAGER->getCurrentMapTileCntX();
	_tileCntY = TILEMANAGER->getCurrentMapTileCntY();
	_mapWidth = _tileCntX * TILE_SIZE;
	_mapHeight = _tileCntY * TILE_SIZE;

	_x = WINSIZE_X - 100;
	_y = WINSIZE_Y + 100;
}

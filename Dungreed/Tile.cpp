#include "Stdafx.h"
#include "Tile.h"

Tile::Tile() :
	_x(0.0f),
	_y(0.0f),
	_rc({0,0,0,0}),
	_isClick(false)
{
}

HRESULT Tile::init(void)
{
	return S_OK;
}

HRESULT Tile::init(float x, float y)
{
	_x = x;
	_y = y;

	_rc = RectMakeCenter(x, y, TILE_SIZE, TILE_SIZE);
	return S_OK;
}

void Tile::release(void)
{
}

void Tile::update(void)
{
	_rc = RectMakeCenter(CAMERAMANAGER->getRelX(_x), CAMERAMANAGER->getRelY(_y), TILE_SIZE, TILE_SIZE);
}

void Tile::render(HDC hdc)
{
	RectangleMakeRect(hdc, _rc);
}


#include "Stdafx.h"
#include "Tile.h"

Tile::Tile() :
	_rc({ 0,0,0,0 }),
	_idx({ 0,0 }),
	_frame({ 0,0 })
{
}

Tile::Tile(int x, int y) :
	_rc({ x * TILE_SIZE,y * TILE_SIZE,(x + 1) * TILE_SIZE,(y + 1) * TILE_SIZE }),
	_idx({ x,y }),
	_frame({ 0,0 }),
	_type(TILE_TYPE::NONE)
{
}

Tile::~Tile()
{
}

HRESULT Tile::init()
{
	return S_OK;
}

HRESULT Tile::init(int x, int y)
{
	_idx.x = x;
	_idx.y = y;
	_type = TILE_TYPE::NONE;

	_rc = RectMakeCenter(x*TILE_SIZE + TILE_SIZE / 2, y*TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
	return S_OK;
}

HRESULT Tile::init(int x, int y, TILE_TYPE type)
{
	_idx.x = x;
	_idx.y = y;
	_type = type;

	_rc = RectMakeCenter(x*TILE_SIZE + TILE_SIZE / 2, y*TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
	return S_OK;
}

void Tile::release()
{
}

void Tile::update()
{
}

void Tile::render()
{
	switch (_type)
	{
	case TILE_TYPE::NONE:
		RectangleMake(getMemDC(), CAMERAMANAGER->getRelX(_rc.left), CAMERAMANAGER->getRelY(_rc.top), TILE_SIZE, TILE_SIZE);
		break;
	case TILE_TYPE::BLOCK:
		IMAGEMANAGER->frameRender("MapTile", getMemDC(), CAMERAMANAGER->getRelX(_rc.left), CAMERAMANAGER->getRelY(_rc.top), _frame.x, _frame.y);
		break;
	default:
		break;
	}

	if (_isDebug)
	{
		char str[128];
		wsprintf(str, "%d, %d", _idx.y, _idx.x);
		TextOut(getMemDC(), CAMERAMANAGER->getRelX(_rc.left), CAMERAMANAGER->getRelY(_rc.top), str, strlen(str));
	}
}


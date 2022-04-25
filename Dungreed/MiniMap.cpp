#include "Stdafx.h"
#include "MiniMap.h"

using namespace MiniMapSet;

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

HRESULT MiniMap::init()
{
	_imgBlock = FindImage(ImageName::UI::MiniMap::MapPixel);
	_imgPlayer = FindImage(ImageName::UI::MiniMap::PlayerPixel);

	_isFixed = TRUE;
	settingMiniMap();

	return S_OK;
}

void MiniMap::release()
{
}

void MiniMap::update()
{
	updatePlayerPosition();
}

void MiniMap::render(HDC hdc)
{
	for (int y = 0; y < _tileCntY; y++)
	{
		for (int x = 0; x < _tileCntX; x++)
		{
			if (_arrType[y * _tileCntX + x] != MapToolEnum::MAP_OBJ::NONE)
			{
				_imgBlock->render(hdc, _miniMapX + x * 5, MAP_Y + y * 5);
			}
			if (y * _tileCntX + x == _playerIdx)
			{
				_imgPlayer->render(hdc, _miniMapX + x * 5, MAP_Y + y * 5);

			}
		}
	}
}

void MiniMap::settingMiniMap()
{
	_tileCntX = TILEMANAGER->getCurrentMapTileCntX();
	_tileCntY = TILEMANAGER->getCurrentMapTileCntY();
	_miniMapX = WINSIZE_X - (_tileCntX * 5) - 10;

	_arrType = new MapToolEnum::MAP_OBJ[_tileCntX * _tileCntY];

	const TILE* tiles = TILEMANAGER->getTiles();

	for (int y = 0; y < _tileCntY; y++)
	{
		for (int x = 0; x < _tileCntX; x++)
		{
			_arrType[y * _tileCntX + x] = (MapToolEnum::MAP_OBJ)tiles[y * TileSet::TILE_CNT_X + x].type;
		}
	}
}

void MiniMap::updatePlayerPosition()
{
	POINT pos = OBJECTMANAGER->getPlayer()->getPt();
	_playerIdx = TILEMANAGER->getTileIndex(pos);
}

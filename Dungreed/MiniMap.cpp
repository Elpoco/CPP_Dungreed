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
	_imgBorder = FindImage(ImageName::UI::MiniMap::BorderPixel);
	_imgBlock = FindImage(ImageName::UI::MiniMap::MapPixel);

	_imgPlayer = FindImage(ImageName::UI::MiniMap::PlayerPixel);
	_imgEnemy = FindImage(ImageName::UI::MiniMap::EnemyPixel);
	_imgDoor = FindImage(ImageName::UI::MiniMap::DoorPixel);

	_isFixed = TRUE;
	_isDungeon = FALSE;
	settingMiniMap();

	return S_OK;
}

void MiniMap::release()
{
}

void MiniMap::update()
{
	updateUnitPosition();
}

void MiniMap::render(HDC hdc)
{
	for (int y = 0; y < _tileCntY; y++)
	{
		for (int x = 0; x < _tileCntX; x++)
		{
			if (_arrType[y * _tileCntX + x] != MapToolEnum::MAP_OBJ::NONE)
			{
				_imgBlock->render(hdc, _miniMapX + x * 5, _miniMapY + y * 5);
			}

			if (x == 0 || y == 0 ||
				x == _tileCntX - 1 || y == _tileCntY - 1)
			{
				_imgBorder->render(hdc, _miniMapX + x * 5, _miniMapY + y * 5);
				if (_isDungeon && _arrType[y * _tileCntX + x] == MapToolEnum::MAP_OBJ::NONE)
				{
					_imgDoor->render(hdc, _miniMapX + x * 5, _miniMapY + y * 5);
				}
			}
		}
	}
	for (auto pt : _vEnemyPt)
	{
		_imgEnemy->render(
			hdc,
			_miniMapX + pt.x * 5,
			_miniMapY + pt.y * 5
		);
	}
	_imgPlayer->render(hdc, _miniMapX + _playerX * 5, _miniMapY + _playerY * 5);
}

void MiniMap::settingMiniMap()
{
	if (TILEMANAGER->getCurrentMapName() == FileName::Town)
	{
		_imgBorder = FindImage(ImageName::UI::MiniMap::BorderPixel);
		_imgBlock = FindImage(ImageName::UI::MiniMap::MapPixel);
	}
	else
	{
		_imgBlock = FindImage(ImageName::UI::MiniMap::BorderPixel);
	}

	_tileCntX = TILEMANAGER->getCurrentMapTileCntX();
	_tileCntY = TILEMANAGER->getCurrentMapTileCntY() + 1;
	_miniMapX = WINSIZE_X - (_tileCntX * 5) - 10;
	_miniMapY = 10;
	_miniMapW = _tileCntX * 5;
	_miniMapH = _tileCntY * 5;

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

void MiniMap::updateUnitPosition()
{
	POINT pos = OBJECTMANAGER->getPlayer()->getPt();
	_playerX = pos.x / TILE_SIZE;
	_playerY = pos.y / TILE_SIZE;

	_vObject = OBJECTMANAGER->getEnemy();
	_vEnemyPt.clear();

	for (auto obj : *_vObject)
	{
		_vEnemyPt.push_back(
			PointMake(
			obj->getX() / TILE_SIZE,
			obj->getY() / TILE_SIZE
			)
		);
	}

	_vObject = OBJECTMANAGER->getNPC();
	for (auto obj : *_vObject)
	{
		if (!obj->isRender()) continue;
		_vEnemyPt.push_back(
			PointMake(
				obj->getX() / TILE_SIZE,
				obj->getY() / TILE_SIZE
			)
		);
	}
}

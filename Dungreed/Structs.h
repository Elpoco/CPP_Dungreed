#pragma once

using Gdiplus::RectF;
using Gdiplus::PointF;

typedef struct tagTile
{
	RectF rc;
	PointF pos;
	int tileFrameX;
	int tileFrameY;
	MapToolEnum::TILE_TYPE type;

	tagTile()
	{
		rc = { 0,0,0,0 };
		pos = { 0,0 };
		tileFrameX = 0;
		tileFrameY = 0;
		type = MapToolEnum::TILE_TYPE::NONE;
	}
} Tile;
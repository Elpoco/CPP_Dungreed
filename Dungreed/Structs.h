#pragma once

using Gdiplus::RectF;
using Gdiplus::PointF;

typedef struct tagTile
{
	RectF rc;
	PointF pos;		// ≈∏¿œ ¿Œµ¶Ω∫
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
} TILE;

typedef struct tagFrameInfo
{
	int tick;
	int cnt;
	int x;
	int y;

	tagFrameInfo()
	{
		tick = 10;
		cnt = 0;
		x = 0;
		y = 0;
	}
} FRAME_INFO;
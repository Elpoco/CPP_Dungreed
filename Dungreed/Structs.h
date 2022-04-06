#pragma once

typedef struct tagTile
{
	float x;
	float y;
	RECT rc;
	POINT pos;		// ≈∏¿œ ¿Œµ¶Ω∫
	int tileFrameX;
	int tileFrameY;

	MapToolEnum::TYPE type;

	//MapToolEnum::TERRAIN	terrain;
	//MapToolEnum::MAP_OBJECT object;

	tagTile()
	{
		x = 0.0f;
		y = 0.0f;
		rc = { 0,0,0,0 };
		pos = { 0,0 };
		tileFrameX = 0;
		tileFrameY = 0;
		type = MapToolEnum::TYPE::NONE;

		//terrain = MapToolEnum::TERRAIN::TR_NONE;
		//object = MapToolEnum::MAP_OBJECT::MO_NONE;
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
#pragma once

typedef struct tagTile
{
	float x;
	float y;
	RECT rc;
	POINT pos;		// Å¸ÀÏ ÀÎµ¦½º
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
	bool isFrame;
	int tick;
	int cnt;
	int x;
	int y;
	int maxFrameX;
	int maxFrameY;
	int startFrameX;
	int width;
	int height;

	tagFrameInfo()
	{
		isFrame = false;
		tick = 8;
		cnt = 0;
		x = 0;
		y = 0;
		maxFrameX = 0;
		maxFrameY = 0;
		startFrameX = 0;
		width = 0;
		height = 0;
	}
} FRAME_INFO;

typedef struct tagEnemyInfo
{
	Code::UNIT code;
	string name;
	int hp;
	int dmg;

	tagEnemyInfo() {}
	tagEnemyInfo(Code::UNIT code, string name, int hp, int dmg = 1)
	{
		this->code = code;
		this->name = name;
		this->hp = hp;
		this->dmg = dmg;
	}
} ENEMY_INFO;

typedef struct tagItemInfo
{
	Code::ITEM_TYPE type;
	Code::ITEM code;
	string name;
	int point;
	int maxPoint;

	tagItemInfo() {}
	tagItemInfo(Code::ITEM_TYPE type, Code::ITEM code, string name, int point, int maxPoint = 0)
	{
		this->type = type;
		this->code = code;
		this->name = name;
		this->point = point;
		this->maxPoint = maxPoint;
	}
} ITEM_INFO;
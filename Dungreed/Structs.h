#pragma once

typedef struct tagTile
{
	float x;
	float y;
	RECT rc;
	POINT idx;		// Å¸ÀÏ ÀÎµ¦½º
	int tileFrameX;
	int tileFrameY;

	int type;

	tagTile()
	{
		x = 0.0f;
		y = 0.0f;
		rc = { 0,0,0,0 };
		idx = { 0,0 };
		tileFrameX = -1;
		tileFrameY = -1;
		type = MapToolEnum::MAP_OBJ::NONE;
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
	int endFrameX;
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
		endFrameX = 0;
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
	int minDmg;
	int maxDmg;
	float atkSpeed;
	int def;
	int etc;

	tagItemInfo() {}
	tagItemInfo(Code::ITEM_TYPE type, Code::ITEM code, string name, 
		int minDmg, int maxDmg = 0, float atkSpeed = 1.0f, int def = 0, int etc = 0)
	{
		this->type = type;
		this->code = code;
		this->name = name;
		this->minDmg = minDmg;
		this->maxDmg = maxDmg;
		this->atkSpeed = atkSpeed;
		this->def = def;
		this->etc = etc;
	}
} ITEM_INFO;

typedef struct tagSpawnInfo
{
	RECT rcScan;
	POINT ptSpawn;
	Code::UNIT unit;

	tagSpawnInfo()
	{
		unit = Code::UNIT::NONE;
	}
} SPAWN_INFO;

typedef struct tagDoorInfo
{
	Direction::DIR dir;
	int tileX;
	int tileY;
} DOOR_INFO;

typedef struct tagMapInfo
{
	DOOR_INFO door[Direction::DIR::DIR_CNT];
	SPAWN_INFO arrSpawnInfo[UnitSet::MAX_SPAWN];
	POINT ptTresure;

	tagMapInfo() 
	{
		ptTresure = { 0,0 };
	}
} MAP_INFO;
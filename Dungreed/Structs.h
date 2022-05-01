#pragma once

typedef struct tagTile
{
	float x;
	float y;
	RECT rc;
	POINT idx;		// 타일 인덱스
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
	int def;
	float atkTime;

	tagEnemyInfo() {}
	tagEnemyInfo(Code::UNIT code, string name, int hp, int dmg = 1, int def = 0, float atkTime = 1.0f)
	{
		this->code = code;
		this->name = name;
		this->hp = hp;
		this->dmg = dmg;
		this->def = def;
		this->atkTime = atkTime;
	}
} ENEMY_INFO;

typedef struct tagItemInfo
{
	Code::ITEM_KIND  type;
	Code::ITEM		 code;
	Code::ITEM_GRADE grade;

	string name;
	string description;

	int price;
	int minDmg;
	int maxDmg = 0;
	float atkSpeed = 0;
	int def = 0;
	int bulletCnt = 0;

	string accDsc = "";

	tagItemInfo() {}
	tagItemInfo(Code::ITEM_KIND type, Code::ITEM code, Code::ITEM_GRADE grade, string name, string description,
		int price, int minDmg, int maxDmg = 0, float atkSpeed = 1.0f, int def = 0, int bulletCnt = 0)
	{
		this->type = type;
		this->code = code;
		this->grade = grade;
		this->name = name;
		this->description = description;
		this->price = price;
		this->minDmg = minDmg;
		this->maxDmg = maxDmg;
		this->atkSpeed = atkSpeed;
		this->def = def;
		this->bulletCnt = bulletCnt;
	}

	tagItemInfo(Code::ITEM_KIND type, Code::ITEM code, Code::ITEM_GRADE grade, string name, string description,
		int price, string accDsc)
	{
		this->type = type;
		this->code = code;
		this->grade = grade;
		this->name = name;
		this->description = description;
		this->price = price;
		this->accDsc = accDsc;
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

typedef struct tagParticle
{
	Direction::DIR dir;
	bool isOn;
	int imgIdx;
	float startX;
	float startY;
	float x;
	float y;
	float speedX;
	float speedY;
	float angle;
	BYTE alpha;

	tagParticle()
	{
		isOn = false;
	}
} PARTICLE;

typedef struct tagStringInfo
{
	const char* str;
	float width;  // 문자열이 들어갈 가로크기
	float height; // 세로크기
	float startX;
	float startY;
} STRING_INFO;

typedef struct tagBulletInfo
{
	int curBulletCnt;
	int maxBulletCnt;
} BULLET_INFO;
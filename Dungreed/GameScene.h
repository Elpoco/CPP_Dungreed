#pragma once
#include "GameNode.h"

class Object;

class GameScene : public GameNode
{
private:
	struct tagSpawnInfo
	{
		RECT rcScan;
		POINT ptSpawn;
		Code::UNIT unit;
	};

private:
	LocationEnum::LOCATION _location;

	// Town
	Image* _layer;
	Image* _background;
	RECT _rcLayer;
	RECT _rcBackground;
	RECT _rcEntrance;
	FRAME_INFO _enterFrame;
	ImageBase* _imgEnter;
	RECT _rcEnter;
	BOOL _isEnter;

	// Dungeon
	Code::MAP _curDungeon;
	MAP_INFO _mapInfo;
	int _spawnCnt;

public:
	GameScene();
	~GameScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void updateTown();
	void renderTown(HDC hdc);

	void loadDungeon();
	void settingDungeon();

};


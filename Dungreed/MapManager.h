#pragma once
#include "SingletonBase.h"

class Door;

class MapManager : public SingletonBase<MapManager>
{
private:
	Code::MAP _mapCode;
	MAP_INFO _mapInfo;

	Door* _door[DIR::DIR_CNT];
	POINT _ptDoor[DIR::DIR_CNT];

	BOOL _isClear;
	int _unitCnt;

public:
	MapManager();
	~MapManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void settingDungeon();
	void settingDoor();
	void settingMonster();

	void chageRoom(DIR dir);
	void openDoor();
	void closeDoor();

	void dieMonster() { _unitCnt--; }

	Code::MAP getCurMapCode() { return _mapCode; }

};


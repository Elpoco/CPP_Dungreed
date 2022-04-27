#pragma once
#include "SingletonBase.h"

class Door;

namespace MapManagerSet
{
	constexpr int PARTICLE_IMG = 2;
	constexpr int PARTICLE_CNT = 100;
}

class MapManager : public SingletonBase<MapManager>
{
private:
	enum class PARTICLE_STATE
	{
		NONE,
		NORMAL,
		SNOW
	};

private:
	Code::MAP _mapCode;
	MAP_INFO _mapInfo;

	Door* _door[DIR::DIR_CNT];
	POINT _ptDoor[DIR::DIR_CNT];

	BOOL _isClear;
	int _unitCnt;

	ImageBase* _imgParticle[MapManagerSet::PARTICLE_IMG];
	PARTICLE _particle[MapManagerSet::PARTICLE_CNT];

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
	void checkMonster();

	void makeParticle();
	void renderParticle(HDC hdc);

	void dieMonster() { _unitCnt--; }

	Code::MAP getCurMapCode() { return _mapCode; }

};


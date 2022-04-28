#pragma once
#include "SingletonBase.h"

class Door;

namespace MapManagerSet
{
	constexpr int MAP_X = 4;
	constexpr int MAP_Y = 4;
	constexpr int MAP_CNT = MAP_X * MAP_Y;

	constexpr int PARTICLE_IMG = 2;
	constexpr int PARTICLE_CNT = 40;
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
	Code::MAP	_arrMapCode[MapManagerSet::MAP_CNT];
	BOOL		_arrClearMap[MapManagerSet::MAP_CNT];
	int			_curLocation;

	MAP_INFO _mapInfo;
	float	 _mapWidth;
	float	 _mapHeight;

	Image* _layer;
	Image* _background;
	RECT _rcLayer;
	RECT _rcBackground;
	BOOL _isSnowMap;

	Door* _door[DIR::DIR_CNT];
	POINT _ptDoor[DIR::DIR_CNT];

	BOOL _isClear;
	int _unitCnt;

	ImageBase* _imgParticle[MapManagerSet::PARTICLE_IMG];
	PARTICLE _particle[MapManagerSet::PARTICLE_CNT];

	Image* _imgSnow;
	RECT _rcSnow;
	float _snowX;
	float _snowY;

public:
	MapManager();
	~MapManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void backgoundRender(HDC hdc);

	void initMap();

	void settingDungeon();
	void settingDoor();
	void settingMonster();

	void chageRoom(DIR dir);
	void openDoor();
	void closeDoor();
	void checkMonster();

	void makeParticle();
	void updateParticle();
	void renderParticle(HDC hdc);

	void updateSnow();
	void renderSnow(HDC hdc);

	void dieMonster() { _unitCnt--; }

	Code::MAP getCurMapCode() { return _arrMapCode[_curLocation]; }

};


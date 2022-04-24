#pragma once
#include "SingletonBase.h"

class EnemyData;
class ItemData;
class MapData;

class DataBaseManager : public SingletonBase<DataBaseManager>
{
private:
	EnemyData* _enemyData;
	ItemData* _itemData;
	MapData* _mapData;

public:
	DataBaseManager();
	~DataBaseManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	ENEMY_INFO getInfo(Code::UNIT code);
	ITEM_INFO getInfo(Code::ITEM code);
	MAP_INFO getInfo(Code::MAP code);

};


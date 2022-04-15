#pragma once
#include "SingletonBase.h"

class EnemyData;
class ItemData;

class DataBaseManager : public SingletonBase<DataBaseManager>
{
private:
	EnemyData* _enemyData;
	ItemData* _itemData;

public:
	DataBaseManager();
	~DataBaseManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	ENEMY_INFO getInfo(Code::UNIT code);
	ITEM_INFO getInfo(Code::ITEM code);

};


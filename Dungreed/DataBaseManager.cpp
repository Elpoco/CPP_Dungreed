#include "Stdafx.h"
#include "DataBaseManager.h"

#include "EnemyData.h"
#include "ItemData.h"

DataBaseManager::DataBaseManager()
{
}

DataBaseManager::~DataBaseManager()
{
}

HRESULT DataBaseManager::init()
{
	_enemyData = new EnemyData;
	_itemData = new ItemData;

	return S_OK;
}

void DataBaseManager::release()
{
}

void DataBaseManager::update()
{
}

void DataBaseManager::render(HDC hdc)
{
}

ENEMY_INFO DataBaseManager::getInfo(Code::UNIT code)
{
	return _enemyData->getInfo(code);
}

ITEM_INFO DataBaseManager::getInfo(Code::ITEM code)
{
	return _itemData->getInfo(code);
}

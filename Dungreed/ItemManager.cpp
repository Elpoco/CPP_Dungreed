#include "Stdafx.h"
#include "ItemManager.h"

#include "Item.h"
#include "DropItem.h"
#include "Sword.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init()
{
	return S_OK;
}

void ItemManager::release()
{
}

void ItemManager::update()
{
}

void ItemManager::render(HDC hdc)
{
}

Item* ItemManager::getItem(Code::ITEM code)
{
	Item* item;
		item = new Sword(code);
	switch (code)
	{
	case Code::ITEM::SHOT_SWORD:
		break;
	case Code::ITEM::GREAT_SWORD:
		break;
	case Code::ITEM::ITEM_CNT:
		break;
	default:
		break;
	}
	return item;
}

ImageBase* ItemManager::findCodeImage(Code::ITEM code)
{
	string imgName;
	switch (code)
	{
	case Code::ITEM::COIN:
		imgName = ImageName::Item::Gold::coin;
		break;
	case Code::ITEM::BULLION:
		imgName = ImageName::Item::Gold::bullion;
		break;
	case Code::ITEM::SHOT_SWORD:
		imgName = ImageName::Item::Weapon::basicShotSword;
		break;
	default:
		imgName = "";
		break;
	}
	return FindImage(imgName);
}

void ItemManager::dropItem(Code::ITEM code, float x, float y)
{
	OBJECTMANAGER->addDropItem(new DropItem(code, x, y));
}

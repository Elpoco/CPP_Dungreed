#include "Stdafx.h"
#include "ItemManager.h"

#include "Inventory.h"
#include "DropItem.h"
#include "Item.h"

#include "Sword.h"
#include "Gun.h"

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

void ItemManager::getItem(Code::ITEM code)
{
	Item* item;
	switch (code)
	{
	case Code::ITEM::SHOT_SWORD:
	case Code::ITEM::GREAT_SWORD:
		item = new Sword(code);
		break;
	case Code::ITEM::COLT:
		item = new Gun(code);
		break;
	default:
		item = new Sword(code);
		break;
	}

	_inventory->addItem(item);
}

ImageBase* ItemManager::findImage(Code::ITEM code)
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
	case Code::ITEM::COLT:
		imgName = ImageName::Item::Weapon::colt;
		break;
	default:
		imgName = "";
		break;
	}

	return FindImage(imgName);
}

void ItemManager::dropItem(Code::ITEM code, float x, float y, BOOL scatter)
{
	OBJECTMANAGER->addDropItem(new DropItem(code, x, y, scatter));
}

Item* ItemManager::getEquipItem()
{
	 return _inventory->getEquipItem(); 
}

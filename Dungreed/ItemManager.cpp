#include "Stdafx.h"
#include "ItemManager.h"

#include "Inventory.h"
#include "DropItem.h"
#include "Item.h"

#include "Sword.h"
#include "Gun.h"

#include "Accessory.h"

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

Item* ItemManager::getItem(Code::ITEM code)
{
	Item* item;
	switch (code)
	{
	case Code::ITEM::SHOT_SWORD:
	case Code::ITEM::BAMBOO_SWORD:
	case Code::ITEM::LIGHTSABER:
		item = new Sword(code);
		break;
	case Code::ITEM::COLT:
		item = new Gun(code);
		break;
	case Code::ITEM::MULTI_BULLET:
	case Code::ITEM::MAGNIFYINGGLASS:
		item = new Accessory(code);
		break;
	default:
		item = new Sword(code);
		break;
	}
	OBJECTMANAGER->addItem(item);
	return item;
}

BOOL ItemManager::giveItem(Code::ITEM code)
{
	return _inventory->addItem(getItem(code));
}

BOOL ItemManager::giveItem(Item* item)
{
	return _inventory->addItem(item);
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
	case Code::ITEM::BAMBOO_SWORD:
		imgName = ImageName::Item::Weapon::BambooSword;
		break;
	case Code::ITEM::LIGHTSABER:
		imgName = ImageName::Item::Weapon::LightSaber;
		break;
	case Code::ITEM::COLT:
		imgName = ImageName::Item::Weapon::colt;
		break;
	case Code::ITEM::MULTI_BULLET:
		imgName = ImageName::Item::Accessory::MultiBullet;
		break;
	case Code::ITEM::MAGNIFYINGGLASS:
		imgName = ImageName::Item::Accessory::MagnifyingGlass;
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

Code::ITEM ItemManager::getEquipAccCode(int idx)
{
	return _inventory->getEquipAccCode(idx);
}

#include "Stdafx.h"
#include "ItemManager.h"

#include "Inventory.h"
#include "DropItem.h"
#include "Item.h"

#include "Sword.h"
#include "Gun.h"
#include "Spear.h"

#include "Accessory.h"
#include "Armor.h"

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
	case Code::ITEM::COSMOSSWORD:
	case Code::ITEM::THREETIEREDBATON:
		item = new Sword(code);
		break;
	case Code::ITEM::LALA:
	case Code::ITEM::COLT:
	case Code::ITEM::GATLINGGUN:
		item = new Gun(code);
		break;
	case Code::ITEM::SPEAR:
		item = new Spear(code);
		break;
	case Code::ITEM::MULTI_BULLET:
	case Code::ITEM::MAGNIFYINGGLASS:
	case Code::ITEM::WINGBOOTS:
	case Code::ITEM::LEATHERARMOR:
	case Code::ITEM::CHAINARMOR:
	case Code::ITEM::CharmOfAttack:
	case Code::ITEM::CharmOfMadness:
	case Code::ITEM::Jarngreipr:
	case Code::ITEM::Speedloader:
	case Code::ITEM::DaisyRing:
		item = new Accessory(code);
		break;
	case Code::ITEM::MagicShield:
		item = new Armor(code);
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
	case Code::ITEM::COSMOSSWORD:
		imgName = ImageName::Item::Weapon::CosmosSword;
		break;
	case Code::ITEM::THREETIEREDBATON:
		imgName = ImageName::Item::Weapon::ThreeTieredBaton;
		break;
	case Code::ITEM::SPEAR:
		imgName = ImageName::Item::Weapon::Spear;
		break;
	case Code::ITEM::LALA:
		imgName = ImageName::Item::Weapon::Lala;
		break;
	case Code::ITEM::COLT:
		imgName = ImageName::Item::Weapon::colt;
		break;
	case Code::ITEM::GATLINGGUN:
		imgName = ImageName::Item::Weapon::GatlingGun;
		break;
	case Code::ITEM::MULTI_BULLET:
		imgName = ImageName::Item::Accessory::MultiBullet;
		break;
	case Code::ITEM::MAGNIFYINGGLASS:
		imgName = ImageName::Item::Accessory::MagnifyingGlass;
		break;
	case Code::ITEM::WINGBOOTS:
		imgName = ImageName::Item::Accessory::Wingboots;
		break;
	case Code::ITEM::BULLION2:
		imgName = ImageName::Item::Accessory::Bullion;
		break;
	case Code::ITEM::LEATHERARMOR:
		imgName = ImageName::Item::Accessory::LeatherArmor;
		break;
	case Code::ITEM::CHAINARMOR:
		imgName = ImageName::Item::Accessory::ChainArmor;
		break;
	case Code::ITEM::CharmOfAttack:
		imgName = ImageName::Item::Accessory::CharmOfAttack;
		break;
	case Code::ITEM::CharmOfMadness:
		imgName = ImageName::Item::Accessory::CharmOfMadness;
		break;
	case Code::ITEM::Jarngreipr:
		imgName = ImageName::Item::Accessory::Jarngreipr;
		break;
	case Code::ITEM::Speedloader:
		imgName = ImageName::Item::Accessory::Speedloader;
		break;
	case Code::ITEM::DaisyRing:
		imgName = ImageName::Item::Accessory::DaisyRing;
		break;
	case Code::ITEM::MagicShield:
		imgName = ImageName::Item::Weapon::MagicShield;
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

void ItemManager::clearInventory()
{
	_inventory->clearInventory();
}

Item* ItemManager::getEquipItem()
{
	 return _inventory->getEquipItem(); 
}

Code::ITEM ItemManager::getEquipAccCode(int idx)
{
	return _inventory->getEquipAccCode(idx);
}

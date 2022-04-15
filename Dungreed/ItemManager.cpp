#include "Stdafx.h"
#include "ItemManager.h"

#include "Item.h"
#include "DropItem.h"
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

void ItemManager::update()
{
}

void ItemManager::render(HDC hdc)
{
}

Item* ItemManager::getItem(Code::ITEM code)
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
	return item;
}

ImageBase** ItemManager::findCodeImage(Code::ITEM code)
{
	string imgName;
	string imgNameInven;
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
		imgNameInven = ImageName::Item::Weapon::basicShotSwordInven;
		break;
	case Code::ITEM::COLT:
		imgName = ImageName::Item::Weapon::colt;
		imgNameInven = ImageName::Item::Weapon::coltInven;
		break;
	default:
		imgName = "";
		break;
	}

	ImageBase* arrImg[2];
	arrImg[0] = FindImage(imgName);
	arrImg[1] = FindImage(imgNameInven);
	return arrImg;
}

void ItemManager::dropItem(Code::ITEM code, float x, float y)
{
	OBJECTMANAGER->addDropItem(new DropItem(code, x, y));
}

void ItemManager::getItemEffect(Code::ITEM code, int x, int y, R_L dir)
{
	if (code <= Code::ITEM::BULLION)
	{
		if (code == Code::ITEM::BULLION)
			OBJECTMANAGER->addDynamicImageFont(x, y, 100, dir, ImageFontEnum::FONT_TYPE::GOLD);
		else
			OBJECTMANAGER->addDynamicImageFont(x, y, 10, dir, ImageFontEnum::FONT_TYPE::GOLD);
	
		SOUNDMANAGER->play(SoundName::Item::getCoin, _sound);
	}
	else
	{
		SOUNDMANAGER->play(SoundName::Item::getItem, _sound);
	}
}

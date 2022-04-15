#include "Stdafx.h"
#include "ItemManager.h"

#include "DropItem.h"

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

string ItemManager::findCodeImage(Code::ITEM code)
{
	string res;
	switch (code)
	{
	case Code::ITEM::COIN:
		res = ImageName::Item::Gold::coin;
		break;
	case Code::ITEM::BULLION:
		res = ImageName::Item::Gold::bullion;
		break;
	case Code::ITEM::SHOT_SWORD:
		res = ImageName::Item::Weapon::basicShotSwordDrop;
		break;
	default:
		res = "";
		break;
	}
	return res;
}

void ItemManager::dropItem(Code::ITEM code, float x, float y)
{
	OBJECTMANAGER->addDropItem(new DropItem(code, x, y));
}

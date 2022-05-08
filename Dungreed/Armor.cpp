#include "Stdafx.h"
#include "Armor.h"

Armor::Armor(Code::ITEM code)
	: Item(code)
{
}

Armor::~Armor()
{
}

HRESULT Armor::init()
{
	Item::init();

	return S_OK;
}

void Armor::release()
{
	Item::release();
}

void Armor::update()
{
	Item::update();
}

void Armor::render(HDC hdc)
{
	Item::render(hdc);
}

void Armor::equip()
{
	Item::equip();

	PLAYERMANAGER->setPower(_itemInfo.power);
	PLAYERMANAGER->setDef(_itemInfo.def);
	PLAYERMANAGER->setHp(_itemInfo.hp);
}

void Armor::unequip()
{
	Item::unequip();

	PLAYERMANAGER->setPower(-_itemInfo.power);
	PLAYERMANAGER->setDef(-_itemInfo.def);
	PLAYERMANAGER->setHp(-_itemInfo.hp);
}

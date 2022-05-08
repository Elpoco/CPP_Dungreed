#include "Stdafx.h"
#include "Accessory.h"

Accessory::Accessory(Code::ITEM code)
	: Item(code)
{
}

Accessory::~Accessory()
{
}

HRESULT Accessory::init()
{
	Item::init();

	return S_OK;
}

void Accessory::release()
{
	Item::release();
}

void Accessory::update()
{
	Item::update();
}

void Accessory::render(HDC hdc)
{
	Item::render(hdc);
}

void Accessory::equip()
{
	Item::equip();

	PLAYERMANAGER->setPower(_itemInfo.power);
	PLAYERMANAGER->setDef(_itemInfo.def);
	PLAYERMANAGER->setHp(_itemInfo.hp);

	switch (_itemInfo.code)
	{
	case Code::ITEM::WINGBOOTS:
		PLAYERMANAGER->addDashCnt(1);
		break;
	case Code::ITEM::MULTI_BULLET:
		PLAYERMANAGER->setMultiBullet(TRUE);
		PLAYERMANAGER->setBulletPower(-5);
		break;
	case Code::ITEM::MAGNIFYINGGLASS:
		PLAYERMANAGER->setSizeBullet(TRUE);
		PLAYERMANAGER->setShootSpeed(-0.7f);
		PLAYERMANAGER->setBulletPower(10);
		break;
	case Code::ITEM::Jarngreipr:
		PLAYERMANAGER->setAtkSpeed(0.5f);
		PLAYERMANAGER->setShootSpeed(0.5f);
		break;
	case Code::ITEM::Speedloader:
		PLAYERMANAGER->setReloadSpeed(0.9f);
		break;
	case Code::ITEM::DaisyRing:
		PLAYERMANAGER->addDashCnt(2);
		PLAYERMANAGER->setSkillCooltime(-0.9f);
		break;
	default:
		break;
	}
}

void Accessory::unequip()
{
	Item::unequip();

	PLAYERMANAGER->setPower(-_itemInfo.power);
	PLAYERMANAGER->setDef(-_itemInfo.def);
	PLAYERMANAGER->setHp(-_itemInfo.hp);

	switch (_itemInfo.code)
	{
	case Code::ITEM::WINGBOOTS:
		PLAYERMANAGER->addDashCnt(-1);
		break;
	case Code::ITEM::MULTI_BULLET:
		PLAYERMANAGER->setMultiBullet(FALSE);
		PLAYERMANAGER->setBulletPower(5);
		break;
	case Code::ITEM::MAGNIFYINGGLASS:
		PLAYERMANAGER->setSizeBullet(FALSE);
		PLAYERMANAGER->setShootSpeed(0.7f);
		PLAYERMANAGER->setBulletPower(-10);
		break;
	case Code::ITEM::Jarngreipr:
		PLAYERMANAGER->setAtkSpeed(-0.5f);
		PLAYERMANAGER->setShootSpeed(-0.5f);
		break;
	case Code::ITEM::Speedloader:
		PLAYERMANAGER->setReloadSpeed(-0.9f);
		break;
	case Code::ITEM::DaisyRing:
		PLAYERMANAGER->addDashCnt(-2);
		PLAYERMANAGER->setSkillCooltime(0.9f);
		break;
	default:
		break;
	}
}

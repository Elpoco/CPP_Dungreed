#include "Stdafx.h"
#include "Gun.h"

Gun::Gun(Code::ITEM code)
	: Item(code)
{
}

Gun::~Gun()
{
}

HRESULT Gun::init()
{
	Item::init();

	return S_OK;
}

void Gun::release()
{
	Item::release();
}

void Gun::update()
{
	Item::update();

	if (!_isEquip) return;
	_rc.left -= 10;
	_frameInfo.y = *_isLeft;

	if (UIMANAGER->onInventory()) return;
}

void Gun::render(HDC hdc)
{
	Item::render(hdc);
}

RECT Gun::attack()
{
	OBJECTMANAGER->addEffect(ImageName::Enemy::Niflheim::bulletFX, _ptHand->x, _ptHand->y);

	OBJECTMANAGER->addBullet(
		ObjectEnum::TYPE::PLAYER_OBJ,
		ImageName::Enemy::Niflheim::bullet,
		_ptHand->x,
		_ptHand->y,
		GetAngle(CAMERAMANAGER->calRelPt(*_ptHand), _ptMouse),
		4,
		2,
		ImageName::Enemy::Niflheim::bulletFX
	);
	return { 0,0,0,0 };
}

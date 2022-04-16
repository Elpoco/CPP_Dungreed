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

	_bulletCnt = _info.etc;

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

	SOUNDMANAGER->play(SoundName::Item::Weapon::Gun, _sound);

	OBJECTMANAGER->addBullet(
		ObjectEnum::TYPE::PLAYER_OBJ,
		ImageName::Item::Weapon::bullet02,
		_ptHand->x,
		_ptHand->y,
		GetAngle(CAMERAMANAGER->calRelPt(*_ptHand), _ptMouse),
		5.0f,
		RND->getFromIntTo(_info.minDmg, _info.maxDmg),
		ImageName::Enemy::Niflheim::bulletFX
	);
	return { 0,0,0,0 };
}

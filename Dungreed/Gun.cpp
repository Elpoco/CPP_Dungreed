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
	_frameInfo.y = ITEMMANAGER->getPlayerIsLeft();


	if (_bulletCnt <= 0)
	{
		_lastAttack += 1.5f;
		_bulletCnt = _info.etc;
	}

	if (UIMANAGER->onInventory()) return;
	this->settingShootingPoint();
}

void Gun::render(HDC hdc)
{
	Item::render(hdc);
}

RECT Gun::attack()
{
	if (_lastAttack + 0.9f - _info.atkSpeed > TIMEMANAGER->getWorldTime()) return { 0,0,0,0 };
	_lastAttack = TIMEMANAGER->getWorldTime();
	if (--_bulletCnt < 0) return { 0,0,0,0 };

	OBJECTMANAGER->addEffect(
		ImageName::Effect::Weapon::shooting,
		_shootingX,
		_shootingY,
		_degree,
		PointMake(_shootingX,_shootingY)
	);

	SOUNDMANAGER->play(SoundName::Item::Weapon::Gun, _sound);

	OBJECTMANAGER->addBullet(
		ObjectEnum::TYPE::PLAYER_OBJ,
		ImageName::Item::Weapon::bullet02,
		_shootingX,
		_shootingY,
		_angle,
		5.0f,
		RND->getFromIntTo(_info.minDmg, _info.maxDmg),
		ImageName::Effect::Weapon::shootingHit
	);
	return { 0,0,0,0 };
}

void Gun::settingShootingPoint()
{
	// 총구 위치 구하기
	_angle = GetAngle(ITEMMANAGER->getPlayerBody(), CAMERAMANAGER->calAbsPt(_ptMouse));
	_shootingX = ITEMMANAGER->getPlayerHand().x + cosf(_angle) * _frameInfo.width;
	_shootingX += ITEMMANAGER->getPlayerIsLeft() ? 12 : -12;
	_shootingY = ITEMMANAGER->getPlayerHand().y - sinf(_angle) * _frameInfo.height - 8;
	_degree = RadToDeg(_angle);
}

#include "Stdafx.h"
#include "Sword.h"

Sword::Sword(Code::ITEM code)
	: Item(code)
	, _isFirst(TRUE)
{
}

Sword::~Sword()
{
}

HRESULT Sword::init()
{
	Item::init();

	return S_OK;
}

void Sword::release()
{
	Item::release();
}

void Sword::update()
{
	Item::update();
	
	if (!_isEquip) return;

	if (UIMANAGER->onInventory()) return;

	if (_isFirst)
	{
		if (ITEMMANAGER->getPlayerIsLeft()) _degree -= 60;
		else _degree += 60;
	}
	else
	{
		if (ITEMMANAGER->getPlayerIsLeft()) _degree -= 230;
		else _degree += 230;
	}
}

void Sword::render(HDC hdc)
{
	Item::render(hdc);
}

RECT Sword::attack()
{
	if (_lastAttack + 0.9f - _info.atkSpeed > TIMEMANAGER->getWorldTime()) return { 0,0,0,0 };
	_lastAttack = TIMEMANAGER->getWorldTime();

	_isFirst = !_isFirst;

	float effectAngle = GetAngle(ITEMMANAGER->getPlayerHand(), CAMERAMANAGER->calAbsPt(_ptMouse));
	float effectX = cosf(effectAngle) * 30 + ITEMMANAGER->getPlayerHand().x;
	float effectY = -sinf(effectAngle) * 30 + ITEMMANAGER->getPlayerHand().y;

	SOUNDMANAGER->play(SoundName::Item::Weapon::swing2, _sound);

	return OBJECTMANAGER->addEffect(
		ImageName::Effect::Weapon::basicSwing,
		effectX,
		effectY,
		RadToDeg(effectAngle),
		PointMake(effectX, effectY)
	);
}

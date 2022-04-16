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
		if (*_isLeft) _degree -= 90;
		else _degree += 90;
	}
	else
	{
		if (*_isLeft) _degree -= 230;
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

	float effectAngle = GetAngle(CAMERAMANAGER->calRelPt(*_ptHand), _ptMouse);
	float effectX = cosf(effectAngle) * 30 + _ptHand->x;
	float effectY = -sinf(effectAngle) * 30 + _ptHand->y;

	SOUNDMANAGER->play(SoundName::Item::Weapon::swing2, _sound);

	return OBJECTMANAGER->addEffect(
		ImageName::Effect::Weapon::basicSwing,
		effectX,
		effectY,
		RadToDeg(effectAngle),
		PointMake(effectX, effectY)
	);
}

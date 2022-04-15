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
	
	if (_isFirst)
	{
		if (*_isLeft) _angle -= 90;
		else _angle += 90;
	}
	else
	{
		if (*_isLeft) _angle -= 210;
		else _angle += 210;
	}
}

void Sword::render(HDC hdc)
{
	Item::render(hdc);
}

RECT Sword::attack()
{
	_isFirst = !_isFirst;

	float effectAngle = GetAngle(CAMERAMANAGER->calRelPt(*_ptHand), _ptMouse);
	float effectX = cosf(effectAngle) * 30 + _ptHand->x;
	float effectY = -sinf(effectAngle) * 30 + _ptHand->y;

	return OBJECTMANAGER->addEffect(
		ImageName::Effect::Weapon::effectBasic,
		effectX,
		effectY,
		RadToDeg(effectAngle),
		PointMake(effectX, effectY)
	);
}

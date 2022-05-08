#include "Stdafx.h"
#include "Spear.h"

Spear::Spear(Code::ITEM code)
	: Item(code)
{
}

Spear::~Spear()
{
}

HRESULT Spear::init()
{
	Item::init();
	_handleX = _frameInfo.width * 0.5f;

	return S_OK;
}

void Spear::release()
{
	Item::release();
}

void Spear::update()
{
	Item::update();

	if (!_isEquip) return;

	if (UIMANAGER->isUI()) return;

	_rc.left += cosf(_angle) * 1;
	_rc.top -= sinf(_angle) * 1;
}

void Spear::render(HDC hdc)
{
	Item::render(hdc);
}

RECT Spear::attack()
{
	return { 0,0,0,0 };
}

void Spear::equip()
{
	Item::equip();
}

void Spear::unequip()
{
	Item::unequip();
}

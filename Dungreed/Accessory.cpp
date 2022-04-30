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

#include "Stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::Item(string name)
{
	this->init(name);
}

Item::~Item()
{
}

HRESULT Item::init()
{
	return S_OK;
}

HRESULT Item::init(string name)
{
	_img = GPIMAGEMANAGER->findImage(name);
	return S_OK;
}

void Item::release()
{
}

void Item::update()
{
}

void Item::render(HDC hdc)
{
}

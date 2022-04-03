#include "Stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

HRESULT Item::init()
{
	return E_NOTIMPL;
}

HRESULT Item::init(string name)
{
	//_vImages.push_back(GPIMAGEMANAGER->findImage(name));

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

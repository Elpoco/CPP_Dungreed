#include "Stdafx.h"
#include "Box.h"

Box::Box()
{
}

Box::~Box()
{
}

HRESULT Box::init()
{
	Object::init();

	return S_OK;
}

void Box::release()
{
	Object::release();
}

void Box::update()
{
	Object::update();
}

void Box::render(HDC hdc)
{
	Object::render(hdc);
}

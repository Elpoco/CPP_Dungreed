#include "Stdafx.h"
#include "Collider.h"

#include "Object.h"

HRESULT Collider::init()
{
	return S_OK;
}

HRESULT Collider::init(Object* object)
{
	_object = object;
	this->settingProve();

	return S_OK;
}

void Collider::release()
{
}

void Collider::update()
{
}

void Collider::render()
{
	for (int i = 0; i < DIR_CNT; i++)
	{
		RectangleMakeCenter(getMemDC(), _prove[i].x, _prove[i].y, 10, 10);
	}
}

void Collider::settingProve()
{
	RECT rc = _object->getRect();
	_prove[LEFT] = { rc.left, (long)_object->getY() };
	_prove[TOP] = { (long)_object->getX(), rc.top };
	_prove[RIGHT] = { rc.right, (long)_object->getY() };
	_prove[BOTTOM] = { (long)_object->getX(), rc.bottom };
}

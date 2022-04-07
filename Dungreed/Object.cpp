#include "Stdafx.h"
#include "Object.h"

Object::Object() : 
	_x(CENTER_X),
	_y(CENTER_Y),
	_rc({0,0,0,0}),
	_isLive(TRUE)
{
	for (int i = 0; i < ColliderEnum::DIRECTION::DIR_CNT; i++)
		_isCollision[i] = false;
}

Object::~Object()
{
}

HRESULT Object::init()
{
	return S_OK;
}

void Object::release()
{
}

void Object::update()
{
}

void Object::render(HDC hdc)
{
}

#include "Stdafx.h"
#include "Object.h"

Object::Object() : 
	_x(-1),
	_y(-1),
	_rc({0,0,0,0}),
	_isLive(TRUE)
{
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

#include "Stdafx.h"
#include "Object.h"

Object::Object()
	: _x(-1)
	, _y(-1)
	, _rc({0,0,0,0})
	, _rcRender({0,0,0,0})
	, _isLive(TRUE)
	, _isRender(TRUE)
	, _rcResizeW(0)
	, _rcResizeH(0)
	, _rcMoveX(0)
	, _rcMoveY(0)
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

#include "Stdafx.h"
#include "Object.h"

Object::Object() : 
	_imgCurrent(0),
	_x(CENTER_X),
	_y(CENTER_Y),
	_rc({0,0,0,0})
{
}

HRESULT Object::init(void)
{
	return S_OK;
}

void Object::release(void)
{
}

void Object::update(void)
{
	this->animation();
	this->updateRect();
}

void Object::render(HDC hdc)
{
	_vImages[_imgCurrent]->frameRender(hdc, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
}

void Object::animation()
{
	_frameInfo.cnt++;

	if (_frameInfo.cnt > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;

		bool checkFrame = _vImages[_imgCurrent]->getMaxFrameX() < _frameInfo.x;
		if (checkFrame) _frameInfo.x = 0;
	}
}

void Object::updateRect(void)
{
	_rc = RectMakeCenter(_x, _y, _vImages[_imgCurrent]->getFrameWidth(), _vImages[_imgCurrent]->getFrameHeight());
}

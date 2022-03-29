#include "Stdafx.h"
#include "Object.h"

Object::Object() : 
	_imgCurrent(0),
	_x(CENTER_X),
	_y(CENTER_Y),
	_rc({0,0,0,0}),
	_isLeft(false)
{
}

Object::~Object()
{
}

HRESULT Object::init()
{
	for (int i = 0; i < ColliderInfo::DIRECTION::DIR_CNT; i++)
	{
		_isCollision[i] = false;
	}

	COLLISIONMANAGER->addObject(this);

	return S_OK;
}

void Object::release()
{
	viImages iter = _vImages.begin();
	for (; iter != _vImages.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
}

void Object::update()
{
	_rc = RectMakeCenter(_x, _y, _vImages[_imgCurrent]->getFrameWidth(), _vImages[_imgCurrent]->getFrameHeight());
	this->animation();
}

void Object::render(HDC hdc)
{
	CAMERAMANAGER->frameRender(hdc, _vImages[_imgCurrent], _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);

	if (_isDebug)
	{
		CAMERAMANAGER->printPoint(hdc, _rc.left, _rc.top, _x, _y, "x: %d, y: %d");
	}
}

void Object::move()
{
	if (_isLeft)
	{
		Object::setFrameY(1);
	}
	else
	{
		Object::setFrameY(0);
	}
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
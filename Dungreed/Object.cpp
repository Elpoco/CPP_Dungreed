#include "Stdafx.h"
#include "Object.h"

Object::Object() : 
	_imgCurrent(0),
	_x(CENTER_X),
	_y(CENTER_Y),
	_rc({0,0,0,0}),
	_isCollision(false)
{
}

HRESULT Object::init()
{
	COLLISIONMANAGER->addObject(this);

	return S_OK;
}

void Object::release()
{
}

void Object::update()
{
	this->animation();
	this->move();
}

void Object::render(HDC hdc)
{
	_vImages[_imgCurrent]->frameRender(hdc, CAMERAMANAGER->getRelX(_rc.left), CAMERAMANAGER->getRelY(_rc.top), _frameInfo.x, _frameInfo.y);
	//CAMERAMANAGER->addRender(this);

	if (_isDebug)
	{
		printPt(hdc, CAMERAMANAGER->getRelX(_rc.left), CAMERAMANAGER->getRelY(_rc.top), _x, _y, "x: %d, y: %d");
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

void Object::move()
{
	// юс╫ц
	if (!_isCollision)
	{
		_y+=5;
	}
	_rc = RectMakeCenter(_x, _y, _vImages[_imgCurrent]->getFrameWidth(), _vImages[_imgCurrent]->getFrameHeight());
}

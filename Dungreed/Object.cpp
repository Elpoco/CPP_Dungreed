#include "Stdafx.h"
#include "Object.h"

Object::Object() : 
	_imgCurrent(0),
	_imgWidth(0.0f),
	_imgHeight(0.0f),
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
	for (int i = 0; i < ColliderEnum::DIRECTION::DIR_CNT; i++)
		_isCollision[i] = false;

	return S_OK;
}

void Object::release()
{
	viImages iter = _vImages.begin();

	for (; iter != _vImages.end(); ++iter)
		SAFE_DELETE(*iter);
}

void Object::update()
{
	this->animation();
	this->updateRect();
}

void Object::render(HDC hdc)
{
	if (_isDebug)
	{
		CAMERAMANAGER->printRectangleCenter(hdc, _x, _y, _imgWidth, _imgHeight);
		CAMERAMANAGER->printPoint(hdc, _rc.GetLeft(), _rc.GetTop(), _x, _y, "x: %d, y: %d");
	}

	CAMERAMANAGER->frameRender(hdc, _vImages[_imgCurrent], _rc.GetLeft(), _rc.GetTop(), _frameInfo.x, _frameInfo.y);
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

	if (_isLeft) _frameInfo.y = 1;
	else _frameInfo.y = 0;
}

void Object::updateRect()
{
	_rc = RectFMakeCenter(
		_x,
		_y,
		_imgWidth,
		_imgHeight
	);
	this->updateProve();
}

void Object::updateProve()
{
	_prove[ColliderEnum::LEFT]	  = PointMake(_rc.GetLeft(), _y);
	_prove[ColliderEnum::RIGHT]   = PointMake(_rc.GetRight(), _y);
	_prove[ColliderEnum::TOP]	  = PointMake(_x, _rc.GetTop());
	_prove[ColliderEnum::BOTTOM]  = PointMake(_x, _rc.GetBottom());
	_prove[ColliderEnum::LBOTTOM] = PointMake(_rc.GetLeft(), _rc.GetBottom());
	_prove[ColliderEnum::RBOTTOM] = PointMake(_rc.GetRight(), _rc.GetBottom());
}

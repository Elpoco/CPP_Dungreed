#include "Stdafx.h"
#include "Effect.h"

Effect::Effect(string imgName, float x, float y, BYTE alpha)
	: _img(nullptr)
	, _imgName(imgName)
	, _alpha(alpha)
	, _degree(0.0f)
	, _rotateCenter({ 0,0 })
	, _isFollow(FALSE)
{
	_x = x;
	_y = y;

	this->init();
}

Effect::Effect(string imgName, float x, float y, int angle, POINT rotateCenter)
	: _img(nullptr)
	, _imgName(imgName)
	, _alpha(0)
	, _degree(angle)
	, _rotateCenter(rotateCenter)
	, _isFollow(FALSE)
{
	_x = x; 
	_y = y;
	
	this->init();
}

Effect::~Effect()
{
}

HRESULT Effect::init()
{
	Object::init();

	if (_rotateCenter.x == 0)_rotateCenter.x = _x;
	if (_rotateCenter.y == 0)_rotateCenter.y = _y;

	_img = FindImage(_imgName);

	_frameInfo.maxFrameX = _img->getMaxFrameX();
	_frameInfo.maxFrameY = _img->getMaxFrameY();
	
	if (_frameInfo.maxFrameX > 0 || _frameInfo.maxFrameY > 0)
	{
		_frameInfo.isFrame = true;
		_frameInfo.width = _img->getFrameWidth();
		_frameInfo.height = _img->getFrameHeight();
	}
	else
	{
		_frameInfo.width = _img->getWidth();
		_frameInfo.height = _img->getHeight();
	}
	_rc = RectMakeCenter(_x, _y, _frameInfo.width, _frameInfo.height);

	return S_OK;
}

void Effect::release()
{
	Object::release();
}

void Effect::update()
{
	Object::update();
	if (_frameInfo.isFrame) this->animation();
	else
	{
		if (_alpha < 255)
		{
			_alpha -= 3;
			if(_alpha < 10) this->deleteEffect();
		}
	}

	if (_isFollow) 
		_rc = RectMakeCenter(*_followX, *_followY, _frameInfo.width, _frameInfo.height);
	else _rc = RectMakeCenter(_x, _y, _frameInfo.width, _frameInfo.height);
}

void Effect::render(HDC hdc)
{
	Object::render(hdc);

	if (_degree)
	{
		if (_isFollow)
		{
			CAMERAMANAGER->frameRender(
				hdc,
				_img,
				_rc.left, 
				_rc.top,
				_frameInfo.x,
				_frameInfo.y, 
				*_followDegree,
				PointMake(*_followX, *_followY)
			);
		}
		else
		{
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y, _degree, _rotateCenter);
		}
	}
	else
	{
		if (_alpha)
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y, _alpha);
		else
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
	}
	
	if (_isDebug)
	{
		CAMERAMANAGER->printRectangle(hdc, _rc, Color::Purple);
	}
}

void Effect::animation()
{
	_frameInfo.cnt++;

	if (_frameInfo.cnt > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;

		if (_frameInfo.x > _frameInfo.maxFrameX)
		{
			this->deleteEffect();
		}
	}
}

void Effect::deleteEffect()
{
	_isLive = FALSE;
}

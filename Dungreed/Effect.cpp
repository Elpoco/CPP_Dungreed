#include "Stdafx.h"
#include "Effect.h"

Effect::Effect(string imgName, float x, float y, BYTE alpha)
	: _img(nullptr)
	, _gpImg(nullptr)
	, _callback(nullptr)
	, _imgName(imgName)
	, _alpha(alpha)
	, _angle(0.0f)
	, _rotateCenter({ 0,0 })
{
	_x = x;
	_y = y;

	this->init();
}

Effect::Effect(string imgName, float x, float y, int angle, POINT rotateCenter)
	: _img(nullptr)
	, _gpImg(nullptr)
	, _callback(nullptr)
	, _imgName(imgName)
	, _alpha(0)
	, _angle(angle)
	, _rotateCenter(rotateCenter)
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

	_gpImg = GPIMAGEMANAGER->findImage(_imgName);

	if (_gpImg)
	{
		_frameInfo.maxFrameX = _gpImg->getMaxFrameX();
		_frameInfo.maxFrameY = _gpImg->getMaxFrameY();
	}
	else
	{
		_img = IMAGEMANAGER->findImage(_imgName);
		_frameInfo.maxFrameX = _img->getMaxFrameX();
		_frameInfo.maxFrameY = _img->getMaxFrameY();
	}

	// 프레임 이미지인지 확인
	if (_frameInfo.maxFrameX > 0 && _frameInfo.maxFrameY > 0)
	{
		_frameInfo.isFrame = true;
		if (_gpImg)
		{
			_frameInfo.width = _gpImg->getFrameWidth();
			_frameInfo.height = _gpImg->getFrameHeight();
		}
		else
		{
			_frameInfo.width = _img->getFrameWidth();
			_frameInfo.height = _img->getFrameHeight();
		}
	}
	else
	{
		if (_gpImg)
		{
			_frameInfo.width = _gpImg->getWidth();
			_frameInfo.height = _gpImg->getHeight();
		}
		else
		{
			_frameInfo.width = _img->getWidth();
			_frameInfo.height = _img->getHeight();
		}
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

	_rc = RectMakeCenter(_x, _y, _frameInfo.width, _frameInfo.height);
}

void Effect::render(HDC hdc)
{
	Object::render(hdc);
	if (_gpImg)
	{
		if (_frameInfo.isFrame)
		{
			CAMERAMANAGER->frameRender(hdc, _gpImg, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y, _angle, _rotateCenter);
		}
		else
		{
			CAMERAMANAGER->render(hdc, _gpImg, _rc.left, _rc.top);
		}
	}
	else
	{
		if (_frameInfo.isFrame)
		{
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y, _alpha);
		}
		else
		{
			CAMERAMANAGER->render(hdc, _img, _rc.left, _rc.top);
		}
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

		bool checkFrame = _frameInfo.maxFrameX < _frameInfo.x;
		if (checkFrame) this->deleteEffect();
	}
}

void Effect::deleteEffect()
{
	if (_callback) _callback();
	_isLive = FALSE;
}

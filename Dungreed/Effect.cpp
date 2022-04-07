#include "Stdafx.h"
#include "Effect.h"

Effect::Effect() :
	_img(nullptr),
	_gpImg(nullptr)
{
}

Effect::~Effect()
{
}

Effect::Effect(string imgName, float x, float y, int angle, POINT rotateCenter)
{
	this->init(imgName, x, y);
}

HRESULT Effect::init()
{
	Object::init();

	return S_OK;
}

HRESULT Effect::init(string imgName, float x, float y, int angle, POINT rotateCenter)
{
	Object::init();

	_gpImg = GPIMAGEMANAGER->findImage(imgName);

	if (_gpImg != nullptr)
	{
		_frameInfo.maxFrameX = _gpImg->getMaxFrameX();
		_frameInfo.maxFrameY = _gpImg->getMaxFrameY();
	}
	else
	{
		_img = IMAGEMANAGER->findImage(imgName);
		_frameInfo.maxFrameX = _img->getMaxFrameX();
		_frameInfo.maxFrameY = _img->getMaxFrameY();
	}

	// 프레임 이미지인지 확인
	if (_frameInfo.maxFrameX > 0 && _frameInfo.maxFrameY > 0)
	{
		_frameInfo.isFrame = true;
	}

	_x = x;
	_y = y;

	_angle = angle;
	_rotateCenter = rotateCenter;

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

	if (_gpImg != nullptr)
	{
		if (_frameInfo.isFrame)
		{
			_rc = RectMakeCenter(_x, _y, _gpImg->getFrameWidth(), _gpImg->getFrameHeight());
		}
		else
		{
			_rc = RectMakeCenter(_x, _y, _gpImg->getWidth(), _gpImg->getHeight());
		}
	}
	else
	{
		if (_frameInfo.isFrame)
		{
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		}
		else
		{
			_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
		}
	}
}

void Effect::render(HDC hdc)
{
	Object::render(hdc);
	if (_gpImg != nullptr)
	{
		if (_frameInfo.isFrame)
		{
			CAMERAMANAGER->frameRender(hdc, _gpImg, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y, _angle, _rotateCenter);
		}
		else
		{
			_gpImg->render(hdc, _rc.left, _rc.top);
		}
	}
	else
	{
		if (_frameInfo.isFrame)
		{
			_img->frameRender(hdc, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
		}
		else
		{
			_img->render(hdc, _rc.left, _rc.top);
		}
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
		if (checkFrame) _isLive = FALSE;
	}
}

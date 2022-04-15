#include "Stdafx.h"
#include "UI.h"

UI::UI()
	: _img(nullptr)
	, _isFixed(FALSE)
	, _isShow(TRUE)
{
}

UI::UI(string imgName, int x, int y, BOOL fixed, BOOL show)
	: _isFixed(fixed)
	, _isShow(show)
{
	_img = IMAGEMANAGER->findImage(imgName);

	if (!_img)
	{
		_img = GPIMAGEMANAGER->findImage(imgName);
	}

	_x = x;
	_y = y;

	_frameInfo.maxFrameX = _img->getMaxFrameX();
	_frameInfo.maxFrameY = _img->getMaxFrameY();

	if (_frameInfo.maxFrameX > 1 || _frameInfo.maxFrameY > 1)
	{
		_width = _img->getFrameWidth();
		_height = _img->getFrameHeight();
		_frameInfo.isFrame = true;
	}
	else
	{
		_width = _img->getWidth();
		_height = _img->getHeight();
	}

	_rc = RectMakeCenter(_x, _y, _width, _height);
}

UI::~UI()
{
}

HRESULT UI::init()
{
	_sceneName = SCENEMANAGER->getCurrentSceneName();
	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
	if (_sceneName != SCENEMANAGER->getCurrentSceneName())
	{
		_isLive = FALSE;
		return;
	}

	if (!_isFixed && _img)
	{
		_rc = RectMakeCenter(_x, _y, _width, _height);
	}

	this->animation();
}

void UI::render(HDC hdc)
{
	if (!_isShow) return;

	if (_isFixed)
	{
		_img->frameRender(hdc, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
	}
}

void UI::setX(float x)
{
	_x = x;
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void UI::setY(float y)
{
	_y = y;
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void UI::animation()
{
	if (!_frameInfo.isFrame) return;

	_frameInfo.cnt++;
	if (_frameInfo.cnt > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;
		if (_frameInfo.x > _frameInfo.maxFrameX) _frameInfo.x = 0;
	}
}


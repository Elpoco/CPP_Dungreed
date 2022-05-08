#include "Stdafx.h"
#include "UI.h"

UI::UI()
	: _img(nullptr)
	, _isFixed(FALSE)
	, _isShow(TRUE)
	, _isFree(FALSE)
	, _showTime(0.0f)
{
}

UI::UI(string imgName, int x, int y, BOOL fixed, BOOL show, BOOL free)
	: _isFixed(fixed)
	, _isShow(show)
	, _isFree(free)
{
	_img = FindImage(imgName);

	_x = x;
	_y = y;

	_frameInfo.maxFrameX = _img->getMaxFrameX();
	_frameInfo.maxFrameY = _img->getMaxFrameY();

	if (_frameInfo.maxFrameX > 0 || _frameInfo.maxFrameY > 0)
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
	//if (!_isShow) return;

	if (_showTime != 0.0f)
	{
		if (_showStartTime + _showTime < TIMEMANAGER->getWorldTime())
		{
			_isShow = FALSE;
		}
	}

	if (_isFadeIn && _alpha < 255)
	{
		_alpha++;
	}

	if (!_isFree && _sceneName != SCENEMANAGER->getCurrentSceneName())
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
	if (!_img) return;
	if (_isFixed)
	{
		if (_alpha > 0) _img->frameAlphaRender(hdc, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y, _alpha);
		else _img->frameRender(hdc, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
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

void UI::setLeft(float left)
{
	_x = left + _width * 0.5f;
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void UI::setTop(float top)
{
	_y = top + _height * 0.5f;
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void UI::setRight(float right)
{
	_x = right - _width * 0.5f;
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void UI::setBottom(float bottom)
{
	_y = bottom - _height * 0.5f;
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

void UI::show(float x, float y)
{
	_isShow = TRUE;
	_x = x; 
	_y = y;
	_rc = RectMakeCenter(_x, _y, _width, _height);
}


#include "Stdafx.h"
#include "Button.h"

Button::Button(string imgName, int x, int y, BOOL fixed, CALLBACK_FUNC cb)
	: _isHoverImg(false)
	, _isOn(false)
	, _callback(cb)
{
	_img = FindImage(imgName);

	_x = x;
	_y = y;
	_isFixed = TRUE;

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

Button::~Button()
{
}

HRESULT Button::init()
{
	UI::init();

	return S_OK;
}

void Button::release()
{
	UI::release();
}

void Button::update()
{
	UI::update();
}

void Button::render(HDC hdc)
{
	if (!_isShow) return;

	_img->frameRender(hdc, _rc.left, _rc.top, 0, _isOn);
}

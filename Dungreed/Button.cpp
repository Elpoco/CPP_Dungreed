#include "Stdafx.h"
#include "Button.h"

Button::Button(string imgName, int x, int y, BOOL fixed, CALLBACK_FUNC cb, string imgNameOn)
	: UI(imgName, x, y, fixed)
	, _isHoverImg(false)
	, _isOn(false)
	, _callback(cb)
{
	if (imgNameOn != "")
	{
		_imgOn = IMAGEMANAGER->findImage(imgNameOn);

		if (!_imgOn)
		{
			_imgOn = GPIMAGEMANAGER->findImage(imgNameOn);
		}
	}

	if (_imgOn) _isHoverImg = TRUE;
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

	if (_isHoverImg && _isOn)
	{
		if (_isFixed)
		{
			_imgOn->render(hdc, _rc.left, _rc.top);
		}
		else
		{
			CAMERAMANAGER->render(hdc, _imgOn, _rc.left, _rc.top);
		}
	}
	else
	{
		UI::render(hdc);
	}
}

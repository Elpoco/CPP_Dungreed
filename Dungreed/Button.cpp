#include "Stdafx.h"
#include "Button.h"

Button::Button(string imgName, int x, int y, BOOL fixed, CALLBACK_FUNC cb)
	: UI(imgName, x, y, fixed)
	, _isHoverImg(false)
	, _isOn(false)
	, _callback(cb)
{
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

void Button::setText(char* text)
{
	// setText는 위치를 정해주고 해야함
	OBJECTMANAGER->addImageFont(_x, _y, text);
}

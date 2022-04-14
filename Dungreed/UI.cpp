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
	_width = _img->getWidth();
	_height = _img->getHeight();
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
}

void UI::render(HDC hdc)
{
	if (!_isShow) return;

	if (_isFixed)
	{
		_img->render(hdc, _rc.left, _rc.top);
	}
	else
	{
		CAMERAMANAGER->render(hdc, _img, _rc.left, _rc.top);
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


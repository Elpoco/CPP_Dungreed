#include "Stdafx.h"
#include "UI.h"

UI::UI(string imgName, int x, int y, bool fixed)
	: _isFixed(fixed)
{
	_sceneName = SCENEMANAGER->getCurrentSceneName();

	_img = IMAGEMANAGER->findImage(imgName);

	if (!_img)
	{
		_img = GPIMAGEMANAGER->findImage(imgName);
	}

	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
}

UI::~UI()
{
}

HRESULT UI::init()
{
	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
	if (!_isFixed)
	{
		_rc = RectMakeCenter(_x, _y, _img->getWidth(), _img->getHeight());
	}
}

void UI::render(HDC hdc)
{
	if (_isFixed)
	{
		_img->render(hdc, _rc.left, _rc.top);
	}
	else
	{
		CAMERAMANAGER->render(hdc, _img, _rc.left, _rc.top);
	}
}

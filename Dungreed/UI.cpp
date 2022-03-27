#include "Stdafx.h"
#include "UI.h"

UI::UI() :
	_x(0.f),
	_y(0.f),
	_rc({ 0,0,0,0 })
{
}

UI::~UI()
{
}

HRESULT UI::init()
{
	return S_OK;
}

HRESULT UI::init(string imageName, RECT rc)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = rc;

	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
}

void UI::render()
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

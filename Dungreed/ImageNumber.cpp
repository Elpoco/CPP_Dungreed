#include "Stdafx.h"
#include "ImageNumber.h"

ImageNumber::ImageNumber(float x, float y, int num, BOOL fixed)
{
	_x = x;
	_y = y;
	_isFixed = fixed;
}

ImageNumber::~ImageNumber()
{
}

HRESULT ImageNumber::init()
{
	UI::init();

	_img = IMAGEMANAGER->findImage(ImageName::UI::Font::damage);

	return S_OK;
}

void ImageNumber::release()
{
	UI::release();
}

void ImageNumber::update()
{
}

void ImageNumber::render(HDC hdc)
{
	if (_isFixed)
	{

	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _img, _x, _y, 0, 0);
	}
}

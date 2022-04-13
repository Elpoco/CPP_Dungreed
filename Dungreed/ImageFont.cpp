#include "Stdafx.h"
#include "ImageFont.h"

ImageFont::ImageFont(float x, float y, int num, BOOL fixed)
	: _num(num)
{
	_x = x;
	_y = y;
	_isFixed = fixed;
}

ImageFont::~ImageFont()
{
}

HRESULT ImageFont::init()
{
	UI::init();

	return S_OK;
}

void ImageFont::release()
{
	UI::release();
}

void ImageFont::update()
{
}

void ImageFont::render(HDC hdc)
{
	if (_isFixed)
	{
		_img->frameRender(hdc, _x, _y, _num, 0);
	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _num, 0);
	}
}

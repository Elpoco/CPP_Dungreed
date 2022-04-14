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

	string tmp = to_string(_num);
	_arrLen = tmp.length();
	_arrNum = new int[_arrLen];

	for (int i = _arrLen -1; i >= 0; i--)
	{
		_arrNum[i] = _num % 10;
		_num /= 10;
	}
	// 골드 먹는거 숫자 자리 작업중..

	return S_OK;
}

void ImageFont::release()
{
	UI::release();
	SAFE_DELETE_ARRAY(_arrNum);
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

#include "Stdafx.h"
#include "ImageFont.h"

using namespace ImageFontEnum;

ImageFont::ImageFont(float x, float y, int num, FONT_TYPE type)
	: _num(num)
	, _type(type)
	, _alpha(0)
{
	_x = x;
	_y = y;
	_isFixed = TRUE;
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

	this->settingImage(_type);

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
	for (int i = 0; i < _arrLen; i++)
	{
		switch (_type)
		{
		case ImageFontEnum::FONT_TYPE::DAMAGE:
			CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _num, 0, _alpha);
			break;
		case ImageFontEnum::FONT_TYPE::GOLD:
			CAMERAMANAGER->frameRender(hdc, _img, _x + i * _imgWidth, _y, _arrNum[i], 0, _alpha);
			if (i == _arrLen - 1)
			{
				CAMERAMANAGER->frameRender(hdc, _img, _x + (i+1) * _imgWidth, _y, 10, 0, _alpha);
			}
			break;
		case ImageFontEnum::FONT_TYPE::NORMAL:
		default:

			if (_isFixed)
			{
				_img->frameRender(hdc, _x, _y, _num, 0);
			}
			else
			{
				CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _num, 0);
			}
			break;
		}
	}
}

void ImageFont::settingImage(FONT_TYPE type)
{
	switch (type)
	{
	case ImageFontEnum::FONT_TYPE::DAMAGE:
		_img = FindImage(ImageName::UI::Font::damage);
		break;
	case ImageFontEnum::FONT_TYPE::GOLD:
		_img = FindImage(ImageName::UI::Font::gold);
		break;
	case ImageFontEnum::FONT_TYPE::NORMAL:
	default:
		_img = FindImage(ImageName::UI::Font::damage);
		break;
	}
	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();
}

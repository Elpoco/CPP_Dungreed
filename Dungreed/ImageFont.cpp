#include "Stdafx.h"
#include "ImageFont.h"

using namespace ImageFontEnum;

ImageFont::ImageFont(float x, float y, int num, FONT_TYPE type)
	: _num(num)
	, _type(type)
	, _alpha(255)
	, _str("")
	, _size(ImageFontEnum::FONT_SIZE::MIDDLE)
{
	_x = x;
	_y = y;
	_isFixed = TRUE;
}

ImageFont::ImageFont(float x, float y, char* str, ImageFontEnum::FONT_SIZE size)
	: _alpha(255)
	, _type(FONT_TYPE::NORMAL)
	, _size(size)
{
	_x = x;
	_y = y;
	_str = str;
	_isFixed = TRUE;
}

ImageFont::~ImageFont()
{
}

HRESULT ImageFont::init()
{
	UI::init();

	settingImage(_type);

	if (_str == "") initNumber();
	else initString();
	

	_rc = RectMakeCenter(_x, _y, _imgWidth * _arrLen, _imgHeight);

	return S_OK;
}

void ImageFont::release()
{
	UI::release();
	SAFE_DELETE_ARRAY(_arrNum);
}

void ImageFont::update()
{
	UI::update();
}

void ImageFont::render(HDC hdc)
{
	if (!_isShow) return;
	for (int i = 0; i < _arrLen; i++)
	{
		switch (_type)
		{
		case ImageFontEnum::FONT_TYPE::DAMAGE:
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left + i * _imgWidth, _rc.top, _arrNum[i], 0, _alpha);
			break;

		case ImageFontEnum::FONT_TYPE::GOLD:
			CAMERAMANAGER->frameRender(hdc, _img, _rc.left + i * (_imgWidth - 3), _rc.top, _arrNum[i], 0, _alpha);
			if (i == _arrLen - 1)
			{
				CAMERAMANAGER->frameRender(hdc, FindImage(ImageName::UI::Font::G), _rc.left + 5 + (i + 1) * (_imgWidth - 3), _rc.top, 0, 0, _alpha);
			}
			break;

		case ImageFontEnum::FONT_TYPE::NORMAL:
		default:
			if (_isFixed)
			{
				if (_arrNum[i] >= '0' && _arrNum[i] <= '9')
				{
					_img->frameRender(hdc, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - '0', FONT_KIND::NUM);
				}
				else if (_arrNum[i] >= 'a' && _arrNum[i] <= 'z')
				{
					_img->frameRender(hdc, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - 'a', FONT_KIND::ENG_SM);
				}
				else if (_arrNum[i] >= 'A' && _arrNum[i] <= 'Z')
				{
					_img->frameRender(hdc, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - 'A', FONT_KIND::ENG);
				}
				else if (_arrNum[i] >= '!' && _arrNum[i] <= '/')
				{
					_img->frameRender(hdc, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - '!', FONT_KIND::SPC_CHAR);
				}
				else
				{
					_img->frameRender(hdc, _rc.left + i * _imgWidth, _rc.top, _arrNum[i], FONT_KIND::NUM);
				}
			}
			else
			{
				if (_arrNum[i] >= '0' && _arrNum[i] <= '9')
				{
					CAMERAMANAGER->frameRender(hdc, _img, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - '0', FONT_KIND::NUM);
				}
				else if (_arrNum[i] >= 'a' && _arrNum[i] <= 'z')
				{
					CAMERAMANAGER->frameRender(hdc, _img, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - 'a', FONT_KIND::ENG_SM);
				}
				else if (_arrNum[i] >= 'A' && _arrNum[i] <= 'Z')
				{
					CAMERAMANAGER->frameRender(hdc, _img, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - 'A', FONT_KIND::ENG);
				}
				else if (_arrNum[i] >= '!' && _arrNum[i] <= '/')
				{
					CAMERAMANAGER->frameRender(hdc, _img, _rc.left + i * _imgWidth, _rc.top, _arrNum[i] - '!', FONT_KIND::SPC_CHAR);
				}
				else
				{
					CAMERAMANAGER->frameRender(hdc, _img, _rc.left + i * _imgWidth, _rc.top, _arrNum[i], FONT_KIND::NUM);
				}
			}
			break;
		}
	}
}

void ImageFont::initNumber()
{
	string tmp = to_string(_num);
	_arrLen = tmp.length();
	_arrNum = new int[_arrLen];

	for (int i = _arrLen - 1; i >= 0; --i)
	{
		_arrNum[i] = _num % 10;
		_num *= 0.1f;
	}
	_rc = RectMakeCenter(_x, _y, _imgWidth * _arrLen, _imgHeight);

	_width = _imgWidth * _arrLen;
	_height = _imgHeight;
}

void ImageFont::initString()
{
	string tmp = _str;
	_arrLen = tmp.length();
	_arrNum = new int[_arrLen];

	for (int i = 0; i < _arrLen; i++)
	{
		_arrNum[i] = _str[i];
	}
	_rc = RectMakeCenter(_x, _y, _imgWidth * _arrLen, _imgHeight);

	_width = _imgWidth * _arrLen;
	_height = _imgHeight;
}

void ImageFont::settingImage(FONT_TYPE type)
{
	if (type == FONT_TYPE::DAMAGE)
	{
		_img = FindImage(ImageName::UI::Font::Damage);
	}
	else if (type == FONT_TYPE::GOLD)
	{
		_img = FindImage(ImageName::UI::Font::Gold);
	}
	else
	{
		if (_size == FONT_SIZE::SMALL) 
			_img = FindImage(ImageName::UI::Font::Normal_s);
		else if (_size == FONT_SIZE::MIDDLE)
			_img = FindImage(ImageName::UI::Font::Normal);
	}

	_imgWidth = _img->getFrameWidth();
	_imgHeight = _img->getFrameHeight();
}

void ImageFont::setNumber(int num)
{
	_num = num;
	initNumber();
}

void ImageFont::setString(char* str)
{
	_str = str;
	initString();
}

#include "Stdafx.h"
#include "DynamicFont.h"

using namespace DynamicFontSet;

DynamicFont::DynamicFont(float x, float y, int num, int dir, ImageFontEnum::FONT_TYPE type)
	: ImageFont(x, y, num)
	, _down(0.0f)
	, _dir(dir)
{
	_isFixed = FALSE;
	_type = type;
}

DynamicFont::~DynamicFont()
{
}

HRESULT DynamicFont::init()
{
	ImageFont::init();

	_initTime = TIMEMANAGER->getWorldTime();

	_x += RND->getInt(30) - 15;
	_y += RND->getInt(30) - 15;

	return S_OK;
}

void DynamicFont::release()
{
	ImageFont::release();
}

void DynamicFont::update()
{
	ImageFont::update();
	this->move();
}

void DynamicFont::render(HDC hdc)
{
	ImageFont::render(hdc);
}

void DynamicFont::move()
{
	if (_alpha - 2 >= 0)
	{
		_alpha -= 2;
	}
	else
	{
		Object::deleteObject();
		return;
	}

	if (_dir == L) _x += 0.5f;
	else _x -= 0.5f;

	_y -= 1.3 + _down;
	_down -= 0.02f;

	_rc = RectMakeCenter(_x, _y, _imgWidth * _arrLen, _imgHeight);
}

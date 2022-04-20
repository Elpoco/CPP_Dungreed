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
	if (_alpha + 2 < 255)
	{
		_alpha += 2;
	}
	else
	{
		Object::deleteObject();
		return;
	}

	if (_dir == L) ++_x;
	else --_x;

	_y -= 1.3 + _down;
	_down -= 0.02f;
}

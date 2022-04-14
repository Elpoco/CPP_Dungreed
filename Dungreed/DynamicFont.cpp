#include "Stdafx.h"
#include "DynamicFont.h"

using namespace DynamicFontSet;

DynamicFont::DynamicFont(float x, float y, int num, int dir)
	: ImageFont(x, y, num, FALSE)
	, _alpha(0)
	, _down(0.0f)
	, _dir(dir)
{
}

DynamicFont::~DynamicFont()
{
}

HRESULT DynamicFont::init()
{
	ImageFont::init();
	_img = FindImage(ImageName::UI::Font::damage);

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

	if (_alpha + 2 < 255)
	{
		_alpha += 2;
	}
	else Object::deleteObject();

	if (_dir == L) _x++;
	else _x--;

	_y -= 1.3 + _down;
	_down -= 0.02f;
}

void DynamicFont::render(HDC hdc)
{
	CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _num, 0, _alpha);
}

void DynamicFont::move()
{
}

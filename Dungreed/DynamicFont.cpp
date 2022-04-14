#include "Stdafx.h"
#include "DynamicFont.h"

using namespace DynamicFontSet;

DynamicFont::DynamicFont(float x, float y, int num, int dir, int type)
	: ImageFont(x, y, num, FALSE)
	, _alpha(0)
	, _down(0.0f)
	, _dir(dir)
	, _type(type)
{
}

DynamicFont::~DynamicFont()
{
}

HRESULT DynamicFont::init()
{
	ImageFont::init();
	_img = FindImage(ImageName::UI::Font::damage);
	_imgGold = FindImage(ImageName::UI::Font::gold);

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
	if (_type)
	{
		CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _num, 0, _alpha);
	}
	else
	{
		for (int i = 0; i < _arrLen; i++)
		{
			CAMERAMANAGER->frameRender(hdc, _imgGold, _x + i*20, _y, _arrNum[i], 0, _alpha);

		}
	}
}

void DynamicFont::move()
{
}

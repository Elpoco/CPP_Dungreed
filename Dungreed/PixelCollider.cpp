#include "Stdafx.h"
#include "PixelCollider.h"

#include "Unit.h"

HRESULT PixelCollider::init(Unit* unit)
{
	_unit = unit;

	return S_OK;
}

void PixelCollider::release(void)
{
}

void PixelCollider::update(void)
{
	this->setProve();

	for (int i = _prove[BOTTOM].y - 5; i < _prove[BOTTOM].y + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelTest")->getMemDC(), _prove[BOTTOM].x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) ||
			(r == 0 && g == 255 && b == 255))
		{
			//_unit->setCollision(true);
			//_unit->setY(i - (_unit->getRect().GetBottom() - _unit->getRect().GetTop()) / 2);
			break;
		}
		else {
			//_unit->setCollision(false);
		}
	}
}

void PixelCollider::render(HDC hdc)
{
	for (int i = 0; i < DIR_CNT; i++)
	{
		PrintRectangle(hdc, _prove[i].x, _prove[i].y, 10, 10);
	}
}

void PixelCollider::setProve(void)
{
	//RectF rc = _unit->getRect();
	//_prove[LEFT] = { rc.left, (long)_unit->getY() };
	//_prove[TOP] = { (long)_unit->getX(), rc.top };
	//_prove[RIGHT] = { rc.right, (long)_unit->getY() };
	//_prove[BOTTOM] = { (long)_unit->getX(), rc.bottom };
}

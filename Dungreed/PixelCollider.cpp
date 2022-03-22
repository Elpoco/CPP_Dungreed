#include "Stdafx.h"
#include "PixelCollider.h"

HRESULT PixelCollider::init(RECT * rc, float* x, float* y, bool* isJump)
{
	_colliderInfo.rc = rc;
	_colliderInfo.x = x;
	_colliderInfo.y = y;
	_colliderInfo.isJump = isJump;

	return S_OK;
}

void PixelCollider::release(void)
{
}

void PixelCollider::update(void)
{
	_proveY = (*_colliderInfo.rc).bottom;

	for (int i = _proveY-10; i < _proveY; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelTest")->getMemDC(), *_colliderInfo.x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		
		if ((r == 255 && g == 0 && b == 0) ||
			(r == 0 && g == 255 && b == 255))
		{
			*_colliderInfo.isJump = false;
			*_colliderInfo.y = i - ((*_colliderInfo.rc).bottom - (*_colliderInfo.rc).top)/2 ;
			break;
		}
	}
}

void PixelCollider::render(HDC hdc)
{
	Rectangle(hdc, *_colliderInfo.x, _proveY, *_colliderInfo.x + 10, _proveY + 10);
}

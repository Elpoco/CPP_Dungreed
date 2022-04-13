#include "Stdafx.h"
#include "DropItem.h"

DropItem::DropItem(float x, float y)
	: _isCollision(false)
	, _dropSpeed(0.0f)
{
	_x = x;
	_y = y;
}

DropItem::~DropItem()
{
}

HRESULT DropItem::init()
{
	Object::init();

	_img = IMAGEMANAGER->findImage(ImageName::Item::Gold::coin);
	_frameInfo.maxFrameX = _img->getMaxFrameX();
	_frameInfo.maxFrameY = _img->getMaxFrameY();
	_frameInfo.width = _img->getFrameWidth();
	_frameInfo.height = _img->getFrameHeight();

	_rc = RectMakeCenter(_x, _y, _frameInfo.width, _frameInfo.height);

	return S_OK;
}

void DropItem::release()
{
	Object::release();
}

void DropItem::update()
{
	Object::update();
	this->move();
	this->animation();
	_rc = RectMakeCenter(_x, _y, _frameInfo.width, _frameInfo.height);
}

void DropItem::render(HDC hdc)
{
	Object::render(hdc);
	CAMERAMANAGER->frameRender(hdc, _img, _x, _y, _frameInfo.x, _frameInfo.y);
}

void DropItem::move()
{
	if (!_isCollision)
	{
		_y += _dropSpeed;
		_dropSpeed += 0.05f;
	}
}

void DropItem::animation()
{
	_frameInfo.cnt++;
	if (_frameInfo.cnt > _frameInfo.maxFrameX)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;
		if (_frameInfo.x > _frameInfo.maxFrameX) _frameInfo.x = 0;
	}
}

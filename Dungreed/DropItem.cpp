#include "Stdafx.h"
#include "DropItem.h"

DropItem::DropItem(Code::Item code, float x, float y)
	: _itemCode(code)
	, _isStop(false)
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

	this->findCodeImage();

	_img = IMAGEMANAGER->findImage(_imgName);
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
	CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
}

void DropItem::collisionObject()
{
	SOUNDMANAGER->play(SoundName::Item::collecting, _sound);
	Object::deleteObject();
}

void DropItem::pushObject(DIRECTION dir, float distance)
{
	switch (dir)
	{
	case ColliderEnum::LEFT:
		_x = distance + _frameInfo.width / 2;
		break;
	case ColliderEnum::TOP:
		_y = distance + _frameInfo.height / 2;
		break;
	case ColliderEnum::RIGHT:
		_x = distance - _frameInfo.width / 2;
		break;
	case ColliderEnum::BOTTOM:
		_y = distance - _frameInfo.height / 2;
		break;
	default:
		break;
	}
}

void DropItem::move()
{
	if (!_isStop)
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

void DropItem::findCodeImage()
{
	switch (_itemCode)
	{
	case Code::Item::COIN:
		_imgName = ImageName::Item::Gold::coin;
		break;
	case Code::Item::BULLION:
		_imgName = ImageName::Item::Gold::bullion;
		break;
	default:
		break;
	}
}

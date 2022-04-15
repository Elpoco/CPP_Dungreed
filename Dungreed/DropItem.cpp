#include "Stdafx.h"
#include "DropItem.h"

DropItem::DropItem(Code::ITEM code, float x, float y)
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

	_img = ITEMMANAGER->findCodeImage(_itemCode);

	_frameInfo.maxFrameX = _img->getMaxFrameX();
	_frameInfo.maxFrameY = _img->getMaxFrameY();
	_frameInfo.width = _img->getFrameWidth();
	_frameInfo.height = _img->getFrameHeight();

	if (_frameInfo.maxFrameX > 1)
	{
		_frameInfo.isFrame = true;
	}

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

void DropItem::collisionObject(int dir)
{
	if (_itemCode <= Code::ITEM::BULLION)
	{
		if(_itemCode == Code::ITEM::BULLION)
			OBJECTMANAGER->addDynamicImageFont(_x, _rc.top, 100, dir, ImageFontEnum::FONT_TYPE::GOLD);
		else
			OBJECTMANAGER->addDynamicImageFont(_x, _rc.top, 10, dir, ImageFontEnum::FONT_TYPE::GOLD);
		
		SOUNDMANAGER->play(SoundName::Item::getCoin, _sound);
	}
	else
	{
		SOUNDMANAGER->play(SoundName::Item::getItem, _sound);
	}
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
	if (!_frameInfo.isFrame) return;

	_frameInfo.cnt++;
	if (_frameInfo.cnt > _frameInfo.maxFrameX)
	{
		_frameInfo.cnt = 0;
		_frameInfo.x++;
		if (_frameInfo.x > _frameInfo.maxFrameX) _frameInfo.x = 0;
	}
}

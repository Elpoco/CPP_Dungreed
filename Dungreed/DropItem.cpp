#include "Stdafx.h"
#include "DropItem.h"

DropItem::DropItem(Code::ITEM code, float x, float y, BOOL scatter)
	: _itemCode(code)
	, _isStop(FALSE)
	, _dropSpeed(0)
	, _gravity(0)
	, _scatterX(0)
{
	_x = x;
	_y = y;
	_dropSpeed = RND->getFromFloatTo(0.05f, 0.08f);
	_gravity = RND->getFromFloatTo(1.7f, 2.4f) * -1;

	if (scatter)
	{
		_scatterX = RND->getFloat(3.0f) - 1.5f;
	}
}

DropItem::~DropItem()
{
}

HRESULT DropItem::init()
{
	Object::init();

	_img = ITEMMANAGER->findImage(_itemCode);

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

void DropItem::collisionObject()
{
	Object::deleteObject();
}

void DropItem::pushObject(DIR dir, float distance)
{
	switch (dir)
	{
	case Direction::LEFT:
		_x = distance + _frameInfo.width * 0.5f;
		_scatterX *= -1;
		break;
	case Direction::TOP:
		_y = distance + _frameInfo.height * 0.5f;
		break;
	case Direction::RIGHT:
		_x = distance - _frameInfo.width * 0.5f;
		_scatterX *= -1;
		break;
	case Direction::BOTTOM:
		_y = distance - _frameInfo.height * 0.5f;
		break;
	default:
		break;
	}
}

void DropItem::move()
{
	if (!_isStop)
	{
		_x += _scatterX;
		_y += _gravity;
		_gravity += _dropSpeed;
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

void DropItem::pickUpPlayer(R_L dir)
{
	if (_itemCode >= Code::ITEM::COIN)
	{
		if (_itemCode == Code::ITEM::BULLION)
			OBJECTMANAGER->addDynamicImageFont(_x + RND->getInt(10) - 5, _rc.top + RND->getInt(10) - 5, 100, dir, ImageFontEnum::FONT_TYPE::GOLD);
		else
			OBJECTMANAGER->addDynamicImageFont(_x + RND->getInt(10) - 5, _rc.top + RND->getInt(10) - 5, 10, dir, ImageFontEnum::FONT_TYPE::GOLD);

		SOUNDMANAGER->play(SoundName::Item::getCoin, _sound);
	}
	else
	{
		SOUNDMANAGER->play(SoundName::Item::getItem, _sound);
		UIMANAGER->showDropItemInfo(DBMANAGER->getInfo(_itemCode));
	}
}

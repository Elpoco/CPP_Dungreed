#include "Stdafx.h"
#include "Item.h"

Item::Item(Code::ITEM itemCode)
	: _angle(0)
	, _lastAttack(0.0f)
{
	_info = DBMANAGER->getInfo(itemCode);
}

Item::~Item()
{
}

HRESULT Item::init()
{

	_img = ITEMMANAGER->findCodeImage(_info.code)[0];
	_imgInven = ITEMMANAGER->findCodeImage(_info.code)[1];
	_frameInfo.width = _img->getFrameWidth();
	_frameInfo.height = _img->getFrameHeight();

	return S_OK;
}

void Item::release()
{
}

void Item::update()
{
	if (_isEquip)
	{
		if (!UIMANAGER->onInventory())
		{
			_angle = GetAngleDeg(
				CAMERAMANAGER->calRelX(_ptHand->x), 
				CAMERAMANAGER->calRelY(_ptHand->y),
				_ptMouse.x,
				_ptMouse.y
			);
		}

		_rc = RectMake(
			_ptHand->x, 
			_ptHand->y - _frameInfo.height / 2,
			_frameInfo.width, 
			_frameInfo.height
		);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _imgInven->getWidth(), _imgInven->getHeight());
	}
}

void Item::render(HDC hdc)
{
	if (_isEquip)
	{
		CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, 0, _frameInfo.y, _angle, *_ptHand);
	}
	else
	{
		if (!UIMANAGER->onInventory()) return;
		_imgInven->render(hdc, _rc.left, _rc.top);
	}
}

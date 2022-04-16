#include "Stdafx.h"
#include "Item.h"

Item::Item(Code::ITEM itemCode)
	: _degree(0)
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
			_degree = GetAngleDeg(
				ITEMMANAGER->getPlayerBody().x,
				ITEMMANAGER->getPlayerBody().y,
				CAMERAMANAGER->calAbsX(_ptMouse.x),
				CAMERAMANAGER->calAbsX(_ptMouse.y)
			);
		}

		_rc = RectMake(
			ITEMMANAGER->getPlayerHand().x,
			ITEMMANAGER->getPlayerHand().y - _frameInfo.height / 2,
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
		CAMERAMANAGER->frameRender(
			hdc,
			_img,
			_rc.left, 
			_rc.top, 
			0,
			_frameInfo.y,
			_degree,
			ITEMMANAGER->getPlayerHand()
		);
	}
	else
	{
		if (!UIMANAGER->onInventory()) return;
		_imgInven->render(hdc, _rc.left, _rc.top);
	}
}

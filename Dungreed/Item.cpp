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
	_img = ITEMMANAGER->findImage(_info.code);

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
		if (!UIMANAGER->onInventory()) updateDegree();
		
		_rc = RectMake(
			ITEMMANAGER->getPlayerHand().x,
			ITEMMANAGER->getPlayerHand().y - _frameInfo.height / 2,
			_frameInfo.width, 
			_frameInfo.height
		);
	}
}

void Item::render(HDC hdc)
{
	if (_isEquip && OBJECTMANAGER->getPlayer()->isRender())
	{
		CAMERAMANAGER->frameRender(
			hdc,
			_img,
			_rc.left, 
			_rc.top, 
			_frameInfo.x,
			_frameInfo.y,
			_degree,
			ITEMMANAGER->getPlayerHand()
		);
	}
}

void Item::updateDegree()
{
	_degree = GetAngleDeg(
		ITEMMANAGER->getPlayerBody().x,
		ITEMMANAGER->getPlayerBody().y,
		CAMERAMANAGER->calAbsX(_ptMouse.x),
		CAMERAMANAGER->calAbsY(_ptMouse.y)
	);
}

#include "Stdafx.h"
#include "Item.h"

Item::Item(Code::ITEM itemCode)
	: _degree(0)
	, _lastAttack(0.0f)
	, _isHover(FALSE)
	, _handle(0.0f)
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

	_handle = _frameInfo.height - 10;

	return S_OK;
}

void Item::release()
{
}

void Item::update()
{
	if (_isEquip)
	{
		if (!UIMANAGER->isUI()) updateDegree();
		
		_rc = RectMake(
			ITEMMANAGER->getPlayerHand().x,
			ITEMMANAGER->getPlayerHand().y - _handle,
			_frameInfo.width, 
			_frameInfo.height
		);
	}
	if (_isHover)
	{
		UIMANAGER->hideItemInfo();
		_isHover = FALSE;
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

	if (_isHover)
	{
		UIMANAGER->showItemInfo(_info);
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

void Item::itemHover()
{
	_isHover = TRUE;
}

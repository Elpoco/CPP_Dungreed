#include "Stdafx.h"
#include "NPC.h"

#include "UI.h"
#include "ItemShop.h"
#include "FoodShop.h"
#include "Ability.h"

NPC::NPC(Code::NPC code, float x, float y, Code::MAP mapCode)
	: _isOpen(FALSE)
	, _npcCode(code)
	, _mapCode(mapCode)
{
	_x = x;
	_y = y;

	switch (code)
	{
	default:
	case Code::NPC::SHOP:
		_uiNPC = new ItemShop;
		_img = FindImage(ImageName::NPC::Merchant);
		break;
	case Code::NPC::DUNGEON_SHOP:
		_uiNPC = new ItemShop(code);
		_img = FindImage(ImageName::NPC::Giant);
		break;
	case Code::NPC::BLACKSMITH:
		_img = FindImage(ImageName::NPC::BlackSmith);
		break;
	case Code::NPC::COMMANDER:
		//_uiNPC = new Ability;
		_img = FindImage(ImageName::NPC::Commander);
		break;
	case Code::NPC::INN:
		_uiNPC = new FoodShop;
		_img = FindImage(ImageName::NPC::Inn);
		break;
	}
}

NPC::~NPC()
{
}

HRESULT NPC::init()
{
	if (_uiNPC)
	{
		_uiNPC->hide();
		OBJECTMANAGER->addUI(_uiNPC);
	}
	initAnimation();

	return S_OK;
}

void NPC::release()
{
}

void NPC::update()
{
	_isRender = FALSE;
	if (MAPMANAGER->getCurMapCode() != _mapCode) return;
	_isRender = TRUE;

	updateAnimation();

	if (_isOpen && !UIMANAGER->isUI()) closeNpc();
}

void NPC::render(HDC hdc)
{
	if (MAPMANAGER->getCurMapCode() != _mapCode) return;
	CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
}

void NPC::initAnimation()
{
	_frameInfo.maxFrameX = _img->getMaxFrameX();

	int width = _img->getFrameWidth();
	int height = _img->getFrameHeight();
	_rc = RectMakeCenter(_x, _y - height * 0.5f, width, height);
	_frameInfo.tick = 15;
}

void NPC::updateAnimation()
{
	if (MAPMANAGER->getCurMapCode() != _mapCode) return;
	if (!_img) return;

	if (_frameInfo.cnt++ > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		if (++_frameInfo.x > _frameInfo.maxFrameX) _frameInfo.x = 0;
	}
}

void NPC::collisionObject()
{
	if (MAPMANAGER->getCurMapCode() != _mapCode) return;

	if (_uiNPC)
	{
		if(!_isOpen) UIMANAGER->showKeyboard(KEY::F, _x, _rc.top);

		if(IsOnceKeyDown(KEY::F) && !UIMANAGER->isUI()) openNpc();
	}
}

void NPC::openNpc()
{
	if (MAPMANAGER->getCurMapCode() != _mapCode) return;

	_uiNPC->show();
	UIMANAGER->onUI();
	_isOpen = TRUE;
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::NORMAL);
}

void NPC::closeNpc()
{
	if (MAPMANAGER->getCurMapCode() != _mapCode) return;

	_isOpen = FALSE;
	UIMANAGER->offUI();
	_uiNPC->hide();
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::TARGET);
}

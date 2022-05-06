#include "Stdafx.h"
#include "Item.h"

#include "Skill.h"

Item::Item(Code::ITEM itemCode)
	: _degree(0)
	, _lastAttack(0.0f)
	, _handleX(0.0f)
{
	_itemInfo = DBMANAGER->getInfo(itemCode);
}

Item::~Item()
{
}

HRESULT Item::init()
{
	_img = ITEMMANAGER->findImage(_itemInfo.code);

	_frameInfo.width = _img->getFrameWidth();
	_frameInfo.height = _img->getFrameHeight();
	_frameInfo.maxFrameX = _img->getMaxFrameX();

	_handleY = _frameInfo.height - 5;

	return S_OK;
}

void Item::release()
{
}

void Item::update()
{
	if (_frameInfo.cnt++ > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		if (++_frameInfo.x > _frameInfo.maxFrameX) _frameInfo.x = 0;

	}

	if (_isEquip)
	{
		if (!UIMANAGER->isUI()) updateDegree();
		
		_rc = RectMake(
			PLAYERMANAGER->getPlayerHand().x - _handleX,
			PLAYERMANAGER->getPlayerHand().y - _handleY,
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
			PLAYERMANAGER->getPlayerHand()
		);
	}

}

void Item::skill()
{
	if (_skill && _skill->isUsing())
	{
		_skill->run(PLAYERMANAGER->getPlayerHand().x, PLAYERMANAGER->getPlayerHand().y, _angle);
	}
}

void Item::updateDegree()
{
	_degree = GetAngleDeg(PLAYERMANAGER->getPlayerBody(), CAMERAMANAGER->calAbsPt(_ptMouse));
	_angle = GetAngle(PLAYERMANAGER->getPlayerBody(), CAMERAMANAGER->calAbsPt(_ptMouse));
}

void Item::itemHover()
{
	UIMANAGER->showItemInfo(_itemInfo);
}

string Item::getSkillIconName()
{
	return _skill->getIconName();
}

float Item::getSkillCooltime()
{
	return _skill->getCooltime();
}

float Item::getSkillRunTime()
{
	return _skill->getRunTime();
}

BOOL Item::isSkillUing()
{
	return _skill->isUsing();
}

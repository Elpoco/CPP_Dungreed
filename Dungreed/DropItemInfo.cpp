#include "Stdafx.h"
#include "DropItemInfo.h"

DropItemInfo::DropItemInfo()
	: _itemInfoX(0.0f)
	, _itemInfoY(0.0f)
{
}

DropItemInfo::~DropItemInfo()
{
}

HRESULT DropItemInfo::init()
{
	_imgInfo = FindImage(ImageName::info);
	_rcInfo = RectMakeCenter(CENTER_X, WINSIZE_Y - 50, _imgInfo->getWidth(), _imgInfo->getHeight());

	return S_OK;
}

void DropItemInfo::release()
{
}

void DropItemInfo::update()
{
	if (!_isShow) return;

}

void DropItemInfo::render(HDC hdc)
{
	if (!_isShow) return;

	_imgInfo->alphaRender(hdc, _rcInfo.left, _rcInfo.top, 200);
	_imgItem->frameRender(hdc, _rcItem.left, _rcItem.top, 0, 0);
	FONTMANAGER->drawString(hdc, _rcInfo.left + 200, _rcInfo.top + _imgInfo->getHeight() * 0.5f - 15, 30, 0, "¾ÆÀÌÅÛ È¹µæ", ColorSet::WHITE, DIR::CENTER);
	FONTMANAGER->drawString(hdc, _rcInfo.left + 200, _rcInfo.top + _imgInfo->getHeight() * 0.5f + 20, 30, FW_BOLD, _itemInfo.name.c_str(), _itemColor, DIR::CENTER);
}

void DropItemInfo::setInfo(ITEM_INFO info)
{
	_itemInfo = info;
	_imgItem = ITEMMANAGER->findImage(_itemInfo.code);
	_rcItem = RectMakeCenter(_rcInfo.left + 50, _rcInfo.top + _imgInfo->getHeight() * 0.5f, _imgItem->getFrameWidth(), _imgItem->getFrameHeight());

	_itemColor = ColorSet::WHITE;
	switch (_itemInfo.grade)
	{
	case Code::ITEM_GRADE::UNCOMMON:
		_itemColor = ColorSet::UNCOMMON;
		break;
	case Code::ITEM_GRADE::RARE:
		_itemColor = ColorSet::RARE;
		break;
	case Code::ITEM_GRADE::LEGEND:
		_itemColor = ColorSet::LEGEND;
		break;
	default:
		break;
	}
}

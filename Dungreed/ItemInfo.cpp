#include "Stdafx.h"
#include "ItemInfo.h"

ItemInfo::ItemInfo() 
	: _itemInfoX(0.0f)
	, _itemInfoY(0.0f)
	, _line(0)
{
}

ItemInfo::~ItemInfo()
{
}

HRESULT ItemInfo::init()
{
	_imgInfo = FindImage(ImageName::UI::Item::ItemInfo);

	return S_OK;
}

void ItemInfo::release()
{
}

void ItemInfo::update()
{
	if (!_isShow) return;

	_itemInfoX = _ptMouse.x;
	_itemInfoY = _ptMouse.y;
	if (_ptMouse.x + _imgInfo->getWidth() > WINSIZE_X) _itemInfoX = _ptMouse.x - _imgInfo->getWidth();
	if (_ptMouse.y + _imgInfo->getHeight() > WINSIZE_Y) _itemInfoY = _ptMouse.y - _imgInfo->getHeight();

	_rcItem = RectMakeCenter(_itemInfoX + 56, _itemInfoY + 101, _imgItem->getFrameWidth(), _imgItem->getFrameHeight());
}

void ItemInfo::render(HDC hdc)
{
	if (!_isShow) return;
	_imgInfo->render(hdc, _itemInfoX, _itemInfoY, 0, 0, _imgInfo->getWidth(), 140);
	for (int i = 0; i < _line; i++)
	{
		_imgInfo->render(hdc, _itemInfoX, _itemInfoY + 140 + i * 20, 0, 140, _imgInfo->getWidth(), 20);
	}
	_imgInfo->render(hdc, _itemInfoX, _itemInfoY + 140 + _line * 20, 0, 140, _imgInfo->getWidth(), _imgInfo->getHeight() - 140);

	// 아이템 이름
	FONTMANAGER->drawString(hdc, _itemInfoX + _imgInfo->getWidth() * 0.5f, _itemInfoY + 38, 30, FW_BOLD, _itemInfo.name.c_str(), _itemColor, DIR::CENTER);
	// 아이템 이미지
	_imgItem->frameRender(hdc, _rcItem.left, _rcItem.top, 0, 0);

	SIZE size;
	if (_itemInfo.type == Code::ITEM_KIND::WEAPON)
	{
		// 아이템 능력치
		string dmg = to_string(_itemInfo.minDmg) + " ~ " + to_string(_itemInfo.maxDmg);
		if (_itemInfo.minDmg == _itemInfo.maxDmg) dmg = to_string(_itemInfo.minDmg);

		if (_itemInfo.minDmg > 0)
		{
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 105, _itemInfoY + 70, 20, 0, "공격력 : ", ColorSet::WHITE);
			FONTMANAGER->drawString(hdc, _itemInfoX + 105 + size.cx, _itemInfoY + 70, 20, 0, dmg.c_str(), ColorSet::YELLOW);
		}

		if (_itemInfo.atkSpeed > 0)
		{
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 105, _itemInfoY + 90, 20, 0, "초당 공격 횟수 : ", ColorSet::WHITE);
			FONTMANAGER->drawString(hdc, _itemInfoX + 105 + size.cx, _itemInfoY + 90, 20, 0, to_string(_itemInfo.atkSpeed).substr(0, 4).c_str(), ColorSet::YELLOW);
		}

		if (_itemInfo.bulletCnt > 0)
		{
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 105, _itemInfoY + 110, 20, 0, "장탄 수 : ", ColorSet::WHITE);
			FONTMANAGER->drawString(hdc, _itemInfoX + 105 + size.cx, _itemInfoY + 110, 20, 0, to_string(_itemInfo.bulletCnt).c_str(), ColorSet::YELLOW);
		}

		if (_itemInfo.ability != "")
		{
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 25, _itemInfoY + 140, 20, 0, "▶ ", ColorSet::WHITE);
			FONTMANAGER->drawText(hdc, { _itemInfo.ability.c_str(), 305, 45, _itemInfoX + 25 + size.cx, _itemInfoY + 140 }, 20, 0, ColorSet::GREEN);
		}
	}
	else
	{
		int infoLine = 0;
		DWORD color = ColorSet::GREEN;
		if (_itemInfo.power != 0)
		{
			color = _itemInfo.power > 0 ? ColorSet::GREEN : ColorSet::RED;
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 105, _itemInfoY + 70, 20, 0, "위력 : ", ColorSet::WHITE);
			FONTMANAGER->drawString(hdc, _itemInfoX + 105 + size.cx, _itemInfoY + 70, 20, 0, to_string(_itemInfo.power).c_str(), color);
			infoLine++;
		}

		if (_itemInfo.def != 0)
		{
			color = _itemInfo.def > 0 ? ColorSet::GREEN : ColorSet::RED;
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 105, _itemInfoY + 70 + infoLine * 20 , 20, 0, "방어력 : ", ColorSet::WHITE);
			FONTMANAGER->drawString(hdc, _itemInfoX + 105 + size.cx, _itemInfoY + 70 + infoLine * 20, 20, 0, to_string(_itemInfo.def).c_str(), color);
			infoLine++;
		}

		if (_itemInfo.hp != 0)
		{
			color = _itemInfo.hp > 0 ? ColorSet::GREEN : ColorSet::RED;
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 105, _itemInfoY + 70 + infoLine * 20, 20, 0, "최대 체력 : ", ColorSet::WHITE);
			FONTMANAGER->drawString(hdc, _itemInfoX + 105 + size.cx, _itemInfoY + 70 + infoLine * 20, 20, 0, to_string(_itemInfo.hp).c_str(), color);
		}

		if (_itemInfo.accDsc != "")
		{
			// 악세 설명
			FONTMANAGER->drawText(hdc, { _itemInfo.accDsc.c_str(), 225, 45, _itemInfoX + 105, _itemInfoY + 70 }, 20, 0, ColorSet::GREEN);
		}
	}

	// 아이템 설명
	FONTMANAGER->drawText(hdc, { _itemInfo.description.c_str(), 305, 45,_itemInfoX + 25, _itemInfoY + 140 + _line * 20 }, 20, 0, ColorSet::ITEM_DSC);

	_isShow = FALSE;
}

void ItemInfo::setInfo(ITEM_INFO info)
{
	_line = 0;
	_itemInfo = info;
	_imgItem = ITEMMANAGER->findImage(_itemInfo.code);
	if (_itemInfo.ability != "") _line++;

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

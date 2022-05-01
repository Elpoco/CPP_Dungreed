#include "Stdafx.h"
#include "UIManager.h"

#include "UI.h"
#include "Cursor.h"
#include "Inventory.h"
#include "PlayerHpBar.h"
#include "MiniMap.h"

UIManager::UIManager()
	: _isUI(FALSE)
	, _isShowItemInfo(FALSE)
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	_cursor = new Cursor;
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::CURSOR, _cursor);
	ShowCursor(false);

	initKeyboard();
	initReload();
	initItemInfo();

	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	updateKeyboard();
	updateReload();

	if (IsOnceKeyDown(KEY::INVENTORY)) toggleInventory();
	if (IsOnceKeyDown(KEY::ESC))
	{
		if (_inventory->isOpen())
		{
			toggleInventory();
		}
		_isUI = FALSE;
	}
}

void UIManager::render(HDC hdc)
{
	renderItemInfo(hdc);
}

void UIManager::setCursorType(UIEnum::CURSOR_TYPE cursorType)
{
	switch (cursorType)
	{
	case UIEnum::NONE:
		ShowCursor(true);
		break;
	case UIEnum::NORMAL:
		ShowCursor(false);
		break;
	case UIEnum::TARGET:
		ShowCursor(false);
		break;
	default:
		break;
	}
	_cursor->setCursor(cursorType);
}

void UIManager::initInventory()
{
	_inventory = new Inventory;
	OBJECTMANAGER->addUI(_inventory);
	ITEMMANAGER->setInventory(_inventory);
}

void UIManager::toggleInventory()
{
	if (!_inventory) return;

	if (_isUI)
	{
		_inventory->close();
		_isUI = FALSE;
	}
	else
	{
		_inventory->open();
		_isUI = TRUE;
	}
}

void UIManager::initPlayerHpBar(int* maxHp, int* curHp)
{
	OBJECTMANAGER->addUI(new PlayerHpBar(maxHp, curHp));
}

void UIManager::initMiniMap()
{
	_miniMap = new MiniMap;
	OBJECTMANAGER->addUI(_miniMap);
}

void UIManager::updateMiniMap()
{
	_miniMap->settingMiniMap();
}

void UIManager::enterDungeon()
{
	_miniMap->setDungeon(TRUE);
}

void UIManager::initKeyboard()
{
	UI* ui;

	ui = new UI(ImageName::UI::Keyboard::F, 0, 0, FALSE, FALSE, TRUE);
	_mKey.insert(make_pair(KEY::F, ui));
	OBJECTMANAGER->addUI(ui);
	ui = new UI(ImageName::UI::Keyboard::ESC, 0, 0, FALSE, FALSE, TRUE);
	_mKey.insert(make_pair(KEY::ESC, ui));
	OBJECTMANAGER->addUI(ui);
}

void UIManager::showKeyboard(KEY key, float x, float top)
{
	auto pair = _mKey.find(key);
	if (!pair->second.key->isShow())
	{
		pair->second.isShow = TRUE;
		pair->second.key->show(x, top - pair->second.key->getHeight() * 0.5f);
	}
}

void UIManager::updateKeyboard()
{
	for (auto pair : _mKey)
	{
		if (pair.second.isShow)
		{
			pair.second.isShow = FALSE;
			pair.second.key->hide();
		}
	}
}

void UIManager::initReload()
{
	_isShowReload = FALSE;

	_uiReloadBar = new UI(ImageName::UI::Item::reloadBar, 0,0, FALSE, FALSE, TRUE);
	_uiReloadBase = new UI(ImageName::UI::Item::reloadBase, 0, 0, FALSE, FALSE, TRUE);

	OBJECTMANAGER->addUI(_uiReloadBar);
	OBJECTMANAGER->addUI(_uiReloadBase);
}

void UIManager::updateReload()
{
	if (!_isShowReload) return;

	_reloadX = OBJECTMANAGER->getPlayer()->getX();
	_reloadY = OBJECTMANAGER->getPlayer()->getY() - 45;
	_uiReloadBase->setX(_reloadX);
	_uiReloadBase->setY(_reloadY);
	_uiReloadBar->setX(_reloadX - 32 + 63 * ((TIMEMANAGER->getWorldTime() - _reloadStartTime) / _reloadTick));
	_uiReloadBar->setY(_reloadY);

	if (_reloadTick <= TIMEMANAGER->getWorldTime() - _reloadStartTime)
	{
		_isShowReload = FALSE;
		_uiReloadBase->hide();
		_uiReloadBar->hide();
		OBJECTMANAGER->addEffect(ImageName::UI::Item::reloadEffect, _reloadX, _reloadY);
	}
}

void UIManager::showReloadBar(float reloadTick)
{
	_reloadTick = reloadTick;
	_reloadStartTime = TIMEMANAGER->getWorldTime();
	_isShowReload = TRUE;
	_uiReloadBase->show();
	_uiReloadBar->show();
}

// ==============
// # 아이템 정보 #
// ==============

void UIManager::initItemInfo()
{
	_uiItemInfo = new UI(ImageName::UI::Item::ItemInfo);
	_uiItemInfo->setFree();
	_uiItemInfo->hide();

	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _uiItemInfo);
}

void UIManager::showItemInfo(ITEM_INFO itemInfo)
{
	_isShowItemInfo = TRUE;
	_itemInfo = itemInfo;
	_itemInfoX = _ptMouse.x - _uiItemInfo->getWidth();
	_itemInfoY = _ptMouse.y - _uiItemInfo->getHeight();

	if (_ptMouse.y < CENTER_Y) _itemInfoY = _ptMouse.y;
	if (_ptMouse.x < CENTER_X) _itemInfoX = _ptMouse.x;

	_uiItemInfo->setX(_itemInfoX + _uiItemInfo->getWidth() * 0.5f);
	_uiItemInfo->setY(_itemInfoY + _uiItemInfo->getHeight() * 0.5f);
	_uiItemInfo->show();
}

void UIManager::hideItemInfo()
{
	_isShowItemInfo = FALSE;
	_uiItemInfo->hide();
}

void UIManager::renderItemInfo(HDC hdc)
{
	if (_isShowItemInfo)
	{
		DWORD itemColor = ColorSet::WHITE;
		switch (_itemInfo.grade)
		{
		case Code::ITEM_GRADE::UNCOMMON:
			itemColor = ColorSet::UNCOMMON;
			break;
		case Code::ITEM_GRADE::RARE:
			itemColor = ColorSet::RARE;
			break;
		case Code::ITEM_GRADE::LEGEND:
			itemColor = ColorSet::LEGEND;
			break;
		default:
			break;
		}

		FONTMANAGER->drawString(hdc, _itemInfoX + _uiItemInfo->getWidth() * 0.5f, _itemInfoY + 38, 30, FW_BOLD, _itemInfo.name.c_str(), itemColor, DIR::CENTER);

		_imgItem = ITEMMANAGER->findImage(_itemInfo.code);
		_rcItem = RectMakeCenter(_itemInfoX + 56, _itemInfoY + 101, _imgItem->getFrameWidth(), _imgItem->getFrameHeight());
		_imgItem->frameRender(hdc, _rcItem.left, _rcItem.top, 0, 0);

		// 아이템 능력치
		SIZE size;
		string dmg = to_string(_itemInfo.minDmg) + " ~ " + to_string(_itemInfo.maxDmg);
		if (_itemInfo.minDmg == _itemInfo.maxDmg) dmg = to_string(_itemInfo.minDmg);

		if (_itemInfo.minDmg > 0)
		{
			size = FONTMANAGER->drawString(hdc, _itemInfoX + 105, _itemInfoY + 70, 20, 0, "공격력 : ", ColorSet::WHITE);
			FONTMANAGER->drawString(hdc, _itemInfoX + 105 + size.cx, _itemInfoY + 70, 20, 0, dmg.c_str(), ColorSet::YELLOW);
		}

		if (_itemInfo.accDsc != "")
		{
			// 악세 설명
			FONTMANAGER->drawText(hdc, { _itemInfo.accDsc.c_str(), 130, 45, _itemInfoX + 105, _itemInfoY + 70 }, 20, 0, ColorSet::GREEN);
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

		// 아이템 설명
		FONTMANAGER->drawText(hdc, { _itemInfo.description.c_str(), 260, 45,_itemInfoX + 25, _itemInfoY + 140 }, 20, 0, ColorSet::ITEM_DSC);
	}
}


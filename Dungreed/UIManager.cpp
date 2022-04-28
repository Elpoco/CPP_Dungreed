#include "Stdafx.h"
#include "UIManager.h"

#include "UI.h"
#include "Cursor.h"
#include "Inventory.h"
#include "PlayerHpBar.h"
#include "MiniMap.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	_cursor = new Cursor;
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _cursor);
	ShowCursor(false);

	initKeyboard();
	initReload();

	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	updateKeyboard();
	updateReload();
}

void UIManager::render(HDC hdc)
{
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

BOOL UIManager::onInventory()
{
	return _inventory->isOpen();
}

void UIManager::toggleInventory()
{
	_inventory->toggleInventory();
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
}

void UIManager::showKeyboard(KEY key, float x, float top)
{
	auto pair = _mKey.find(key);
	if (!pair->second.key->isShow())
	{
		pair->second.isShow = TRUE;
		pair->second.key->show(x, top);
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
	//_imgReloadEffect = FindImage(ImageName::UI::Item::reloadEffect);
}

void UIManager::updateReload()
{
	if (!_isShowReload) return;

	_reloadX = OBJECTMANAGER->getPlayer()->getX();
	_reloadY = OBJECTMANAGER->getPlayer()->getY() - 45;
	_uiReloadBase->setX(_reloadX);
	_uiReloadBase->setY(_reloadY);
	_uiReloadBar->setX(_reloadX - 32 + 63 * (TIMEMANAGER->getWorldTime() - _reloadStartTime));
	_uiReloadBar->setY(_reloadY);

	if (_reloadTime <= TIMEMANAGER->getWorldTime() - _reloadStartTime)
	{
		_isShowReload = FALSE;
		_uiReloadBase->hide();
		_uiReloadBar->hide();
		OBJECTMANAGER->addEffect(ImageName::UI::Item::reloadEffect, _reloadX, _reloadY);
	}
}

void UIManager::showReloadBar(float reloadTime)
{
	_reloadTime = reloadTime;
	_reloadStartTime = TIMEMANAGER->getWorldTime();
	_isShowReload = TRUE;
	_uiReloadBase->show();
	_uiReloadBar->show();
}


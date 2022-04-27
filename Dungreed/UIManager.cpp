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

	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	updateKeyboard();
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

void UIManager::reloadUI(float reloadTime)
{
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


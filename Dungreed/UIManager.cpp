#include "Stdafx.h"
#include "UIManager.h"

#include "UI.h"
#include "Cursor.h"
#include "Inventory.h"
#include "PlayerHpBar.h"

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

	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
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


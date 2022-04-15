#include "Stdafx.h"
#include "UIManager.h"

#include "UI.h"
#include "Cursor.h"
#include "Inventory.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	_cursor = new Cursor;
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::UI_FRONT, _cursor);
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

BOOL UIManager::onInventory()
{
	return _inventory->isOpen();
}


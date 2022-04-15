#include "Stdafx.h"
#include "UIManager.h"

#include "Cursor.h"

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

void UIManager::setCursor(UIEnum::CURSOR_TYPE cursorType)
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

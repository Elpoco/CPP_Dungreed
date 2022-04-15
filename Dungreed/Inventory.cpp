#include "Stdafx.h"
#include "Inventory.h"

#include "Item.h"
#include "Button.h"

using namespace InventorySet;

Inventory::Inventory()
	: _isOpen(FALSE)
	, _clickCell(-1)
{
}

Inventory::~Inventory()
{
}

HRESULT Inventory::init()
{
	settingUI();

	for (int i = 0; i < CELL_CNT; i++)
	{
		if (i > 10)
		{
			_arrItems[i] = NULL;
			continue;
		}
		_arrItems[i] = ITEMMANAGER->getItem(Code::ITEM::SHOT_SWORD);
		OBJECTMANAGER->addObject(ObjectEnum::TYPE::ITEM_FRONT, _arrItems[i]);
	}

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (IsOnceKeyDown(KEY::INVENTORY))
	{
		toggleInventory();
	}

	if (_isOpen) this->onClick();
	if (_isOpen) this->sortItem();
	if (_clickCell > -1) this->dragItem();
}

void Inventory::render(HDC hdc)
{
	if (!_isOpen) return;
}

void Inventory::settingUI()
{
	UI* invenBase = new UI(ImageName::UI::Inventory::base);
	invenBase->setX(WINSIZE_X - invenBase->getWidth() / 2);
	invenBase->setY(CENTER_Y);

	_vUI.push_back(invenBase);
	OBJECTMANAGER->addUI(invenBase);

	Button* btnClose = new Button(ImageName::UI::Inventory::btn);
	btnClose->setX(invenBase->getRect().left - btnClose->getWidth() / 2);
	btnClose->setY(CENTER_Y - 220);
	_rcClose = btnClose->getRect();

	_vUI.push_back(btnClose);
	OBJECTMANAGER->addButton(btnClose);

	for (int i = 0; i < CELL_CNT; i++)
	{
		Button* btn = new Button(ImageName::UI::Inventory::Cell);
		int x = i % 5;
		int y = i / 5;

		_ptCell[i].x = 61 + invenBase->getRect().left + x * 65;
		_ptCell[i].y = 25 + CENTER_Y + y * 65;

		btn->setX(_ptCell[i].x);
		btn->setY(_ptCell[i].y);

		_rcCell[i] = btn->getRect();

		_vUI.push_back(btn);
		OBJECTMANAGER->addButton(btn);
	}

	for (auto ui : _vUI)
	{
		ui->hide();
	}
}

void Inventory::toggleInventory()
{
	_isOpen = !_isOpen;
	if (_isOpen)
	{
		UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::NORMAL);
		SOUNDMANAGER->play(SoundName::invenOpen, _sound);
		for (auto ui : _vUI)
		{
			ui->show();
		}
	}
	else
	{
		UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::TARGET);
		_clickCell = -1;
		for (auto ui : _vUI)
		{
			ui->hide();
		}
	}
}

void Inventory::onClick()
{
	if (!IsOnceKeyDown(KEY::CLICK_L)) return;

	if (MouseInRect(_rcClose)) toggleInventory();

	for (int i = 0; i < CELL_CNT; i++)
	{
		if (MouseInRect(_rcCell[i]))
		{
			//if (_arrItems[i])
			//{
			//	_arrItems[i] = _arrItems[_clickCell];
			//}
			_clickCell = i;
			return;
		}
	}
}

void Inventory::sortItem()
{
	for (int i = 0; i < CELL_CNT; i++)
	{
		if (!_arrItems[i]) continue;
		if (_clickCell == i) continue;

		_arrItems[i]->setX(_ptCell[i].x);
		_arrItems[i]->setY(_ptCell[i].y);
	}
}

void Inventory::dragItem()
{
	if (!_arrItems[_clickCell])
	{
		_clickCell = -1;
		return;
	}
	_arrItems[_clickCell]->setX(_ptMouse.x);
	_arrItems[_clickCell]->setY(_ptMouse.y);
}

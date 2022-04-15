#include "Stdafx.h"
#include "Inventory.h"

#include "Item.h"
#include "Button.h"

using namespace InventorySet;

Inventory::Inventory()
	: _isOpen(FALSE)
{
}

Inventory::~Inventory()
{
}

HRESULT Inventory::init()
{
	settingUI();

	for (int i=0; i<CELL_CNT; i++)
	{
		//_vItems[i] = new Item();
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

	if (IsOnceKeyUp(KEY::CLICK_L))
	{
		if (MouseInRect(_rcClose) && _isOpen)
		{
			toggleInventory();
		}
	}
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
		int x = i % 5;
		int y = i / 5;
		Button* btn = new Button(ImageName::UI::Inventory::Cell);
		btn->setX(61 + invenBase->getRect().left + x * 65);
		btn->setY(25 + CENTER_Y + y * 65);
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
		UIMANAGER->setCursor(UIEnum::CURSOR_TYPE::NORMAL);
		SOUNDMANAGER->play(SoundName::invenOpen, _sound);
		for (auto ui : _vUI)
		{
			ui->show();
		}
	}
	else
	{
		UIMANAGER->setCursor(UIEnum::CURSOR_TYPE::TARGET);
		for (auto ui : _vUI)
		{
			ui->hide();
		}
	}
}

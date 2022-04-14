#include "Stdafx.h"
#include "Inventory.h"

#include "Item.h"
#include "Button.h"

void closeInven();

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

		if (_isOpen)
		{
			_invenBase->show();
		}
		else
		{
			_invenBase->hide();
		}
	}
}

void Inventory::render(HDC hdc)
{
	if (!_isOpen) return;
	_invenBase->render(hdc);
}

void Inventory::settingUI()
{
	_invenBase = new UI(ImageName::UI::Inventory::base);
	_invenBase->setX(WINSIZE_X - _invenBase->getWidth() / 2);
	_invenBase->setY(CENTER_Y);

	_btnClose = new Button(ImageName::UI::Inventory::btn);
	_btnClose->setX(_invenBase->getRect().left - _btnClose->getWidth() / 2);
	_btnClose->setY(CENTER_Y);
	_btnClose->setCallback(closeInven);
	_btnClose->hide();
	_vUI.push_back(_btnClose);
	OBJECTMANAGER->addButton(_btnClose);

	for (int i = 0; i < 5; i++)
	{
		Button* btn = new Button(ImageName::UI::Inventory::Cell);
		btn->setX(60 + _invenBase->getRect().left + i * 66);
		btn->setY(25 + CENTER_Y);
		btn->hide();
		_vUI.push_back(btn);
		OBJECTMANAGER->addButton(btn);
	}

}

void Inventory::toggleInventory()
{
	_isOpen = !_isOpen;
	if (_isOpen)
	{
		for (auto ui : _vUI)
		{
			ui->show();
		}
	}
	else
	{
		for (auto ui : _vUI)
		{
			ui->hide();
		}
	}
}

void closeInven()
{
	//Inventory::_isOpen = false;
}

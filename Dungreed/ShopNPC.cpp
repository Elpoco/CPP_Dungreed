#include "Stdafx.h"
#include "ShopNPC.h"

#include "UI.h"

using namespace ShopNPCSet;

ShopNPC::ShopNPC(float x, float y)
	: _itemCnt(MAX_ITEM_CNT)
{
	_x = x;
	_y = y;
}

ShopNPC::~ShopNPC()
{
}

HRESULT ShopNPC::init()
{
	NPC::init();
	initAnimation();
	initUI();

	return S_OK;
}

void ShopNPC::release()
{
	NPC::release();
}

void ShopNPC::update()
{
	NPC::update();

	if (_isOpen)
	{
		hoverImg();
	}
}

void ShopNPC::render(HDC hdc)
{
	NPC::render(hdc);
}

void ShopNPC::initAnimation()
{
	_img = FindImage(ImageName::NPC::Merchant);
	_frameInfo.maxFrameX = _img->getMaxFrameX();

	int width = _img->getFrameWidth();
	int height = _img->getFrameHeight();
	_rc = RectMakeCenter(_x, _y - height * 0.5f, width, height);
}

void ShopNPC::initUI()
{
	_uiBase = new UI(ImageName::UI::NPC::ShopBase);
	_uiBase->setX(_uiBase->getWidth() * 0.5f);
	_uiBase->setY(CENTER_Y);
	OBJECTMANAGER->addUI(_uiBase);
	_vUI.push_back(_uiBase);

	ImageBase* tmpImg = FindImage(ImageName::UI::NPC::ShopItem);
	int imgHeight = tmpImg->getHeight();
	int top = _uiBase->getRect().top + 95 + imgHeight * 0.5f;
	int imgPos = imgHeight + 3;

	for (int i = 0; i < MAX_ITEM_CNT; i++)
	{
		UI* itemSlot = new UI(ImageName::UI::NPC::ShopItem);
		itemSlot->setX(_uiBase->getWidth() * 0.5f - 3);
		itemSlot->setY(top + i * imgPos);
		OBJECTMANAGER->addUI(itemSlot);
		_arrUI[i] = itemSlot;
		_arrUI[i]->hide();
		_arrRcUI[i] = itemSlot->getRect();
	}

	_uiSelect = new UI(ImageName::UI::NPC::ShopItem_Selected);
	_uiSelect->hide();
	OBJECTMANAGER->addUI(_uiSelect);

	for (auto ui : _vUI)
	{
		ui->hide();
	}
}

void ShopNPC::hoverImg()
{
	_uiSelect->hide();
	for (int i = 0; i < _itemCnt; i++)
	{
		if (MouseInRect(_arrRcUI[i]))
		{
			_uiSelect->setX(_arrUI[i]->getX());
			_uiSelect->setY(_arrUI[i]->getY());
			_uiSelect->show();
			break;
		}
	}
}

void ShopNPC::openNpc()
{
	NPC::openNpc(); 
	UIMANAGER->toggleInventory();

	for (int i = 0; i < _itemCnt; i++)
	{
		_arrUI[i]->show();
	}
}

void ShopNPC::closeNpc()
{
	NPC::closeNpc();

	for (int i = 0; i < MAX_ITEM_CNT; i++)
	{
		_arrUI[i]->hide();
	}
}

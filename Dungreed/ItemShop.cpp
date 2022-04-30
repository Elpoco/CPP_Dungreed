#include "Stdafx.h"
#include "ItemShop.h"

#include "Item.h"

using namespace ItemShopSet;

ItemShop::ItemShop()
	: _itemCnt(MAX_ITEM_CNT)
{
}

ItemShop::ItemShop(ImageBase** img)
	: _itemCnt(MAX_ITEM_CNT)
{
	*img = FindImage(ImageName::NPC::Merchant);
}

ItemShop::~ItemShop()
{
}

HRESULT ItemShop::init()
{
	UI::init();

	//initAnimation();
	initUI();

	for (int i = 0; i < MAX_ITEM_CNT; i++)
	{
		Code::ITEM code = RND->getRndEnum(Code::ITEM::SHOT_SWORD, Code::ITEM::WEAPON_CNT);
		_vItems.push_back(ITEMMANAGER->getItem(code));
	}

	return S_OK;
}

void ItemShop::release()
{
	UI::release();
}

void ItemShop::update()
{
	UI::update();
	if (!_isShow) return;

	hoverImg();

	if (UIMANAGER->isClick()) clickItem();
}

void ItemShop::render(HDC hdc)
{
	UI::render(hdc);
	if (!_isShow) return;

	_uiBase->render(hdc);
	renderItemSlot(hdc);
}

void ItemShop::show()
{
	_isShow = TRUE;
	UIMANAGER->toggleInventory();
}

void ItemShop::initAnimation()
{
	_img = FindImage(ImageName::NPC::Merchant);
	_frameInfo.maxFrameX = _img->getMaxFrameX();

	int width = _img->getFrameWidth();
	int height = _img->getFrameHeight();
	_rc = RectMakeCenter(_x, _y - height * 0.5f, width, height);
}

void ItemShop::initUI()
{
	_img = FindImage(ImageName::UI::NPC::ShopBase);
	_uiBase = new UI(ImageName::UI::NPC::ShopBase);
	_uiBase->setX(_uiBase->getWidth() * 0.5f);
	_uiBase->setY(CENTER_Y);
	
	ImageBase* tmpImg = FindImage(ImageName::UI::NPC::ShopItem);
	int imgHeight = tmpImg->getHeight();
	int top = _uiBase->getRect().top + 95 + imgHeight * 0.5f;
	int imgPos = imgHeight + 3;
	
	for (int i = 0; i < MAX_ITEM_CNT; i++)
	{
		UI* itemSlot = new UI(ImageName::UI::NPC::ShopItem);
		itemSlot->setX(_uiBase->getWidth() * 0.5f - 3);
		itemSlot->setY(top + i * imgPos);
		_arrUI[i] = itemSlot;
		_rcSlots[i] = itemSlot->getRect();
	}
	
	_uiSelect = new UI(ImageName::UI::NPC::ShopItem_Selected);
	_uiSelect->hide();
}

void ItemShop::renderItemSlot(HDC hdc)
{
	for (int i = 0; i < _itemCnt; i++)
	{
		_arrUI[i]->render(hdc);
	}

	_uiSelect->render(hdc);

	ImageBase* img;
	ITEM_INFO info;
	for (int i = 0; i < _itemCnt; i++)
	{
		// 아이템 이미지
		img = _vItems[i]->getImage();
		img->frameRender(
			hdc,
			_rcSlots[i].left - img->getFrameWidth() * 0.5f + 33,
			_arrUI[i]->getY() - img->getFrameHeight() * 0.5f,
			0, 
			0
		);

		// 아이템 정보
		info = _vItems[i]->getInfo();
		DWORD itemColor = ColorSet::WHITE;
		switch (info.grade)
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

		FONTMANAGER->drawString(hdc, _rcSlots[i].left + 75, _rcSlots[i].top + 5, 26, FW_BOLD, info.name.c_str(), itemColor);
		FONTMANAGER->drawNumber(hdc, _rcSlots[i].right - 45, _rcSlots[i].bottom - 28, 19, FW_BOLD, to_string(info.price).c_str(), ColorSet::WHITE, DIR::RIGHT);
	}
}

void ItemShop::hoverImg()
{
	_uiSelect->hide();
	for (int i = 0; i < _itemCnt; i++)
	{
		if (MouseInRect(_rcSlots[i]))
		{
			_uiSelect->setX(_arrUI[i]->getX());
			_uiSelect->setY(_arrUI[i]->getY());
			_uiSelect->show();
			_vItems[i]->itemHover();
			break;
		}
	}
}

void ItemShop::clickItem()
{
	for (int i = 0; i < _itemCnt; i++)
	{
		if (MouseInRect(_rcSlots[i]))
		{
			if (_vItems[i])
			{
				if (PLAYERMANAGER->getCoin() < _vItems[i]->getInfo().price) return;
				if (ITEMMANAGER->giveItem(_vItems[i]))
				{
					_vItems.erase(_vItems.begin() + i);
					_itemCnt--;
				}
			}
			break;
		}
	}
}
